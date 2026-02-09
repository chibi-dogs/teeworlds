/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#include <gtest/gtest.h>

#include <base/hash_ctxt.h>
#include <base/system.h>

static void Expect(const SHA256_DIGEST& Actual, const char* pWanted)
{
	//std::array<char, SHA256_MAXSTRSIZE> aActual{};
	char aActual[SHA256_MAXSTRSIZE];
	sha256_str(Actual, aActual, sizeof(aActual));
	EXPECT_STREQ(aActual, pWanted);
}

static void ExpectNotEqual(const SHA256_DIGEST& Actual, const char* pWanted)
{
	//std::array<char, SHA256_MAXSTRSIZE> aActual{};
	char aActual[SHA256_MAXSTRSIZE];
	sha256_str(Actual, aActual, sizeof(aActual));
	EXPECT_STRNE(aActual, pWanted);
}

TEST(Hash, Sha256)
{
	// https://en.wikipedia.org/w/index.php?title=SHA-2&oldid=840187620#Test_vectors
	Expect(sha256("", 0), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
	SHA256_CTX ctxt;

	sha256_init(&ctxt);
	Expect(sha256_finish(&ctxt), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

	// printf 'The quick brown fox jumps over the lazy dog.' | sha256sum
	char QUICK_BROWN_FOX[] = "The quick brown fox jumps over the lazy dog.";
	Expect(sha256(QUICK_BROWN_FOX, str_length(QUICK_BROWN_FOX)), "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c");

	sha256_init(&ctxt);
	sha256_update(&ctxt, "The ", 4);
	sha256_update(&ctxt, "quick ", 6);
	sha256_update(&ctxt, "brown ", 6);
	sha256_update(&ctxt, "fox ", 4);
	sha256_update(&ctxt, "jumps ", 6);
	sha256_update(&ctxt, "over ", 5);
	sha256_update(&ctxt, "the ", 4);
	sha256_update(&ctxt, "lazy ", 5);
	sha256_update(&ctxt, "dog.", 4);
	Expect(sha256_finish(&ctxt), "ef537f25c895bfa782526529a9b63d97aa631564d5d789c2b765448c8635fb6c");
}

TEST(Hash, Sha256Eq)
{
	EXPECT_EQ(sha256("", 0), sha256("", 0));
}

TEST(Hash, SingleByte) {
	Expect(sha256("a", 1), "ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb");
}

TEST(Hash, InputSize10KB) {
	const std::string s(10 * 1024, 'x');
	Expect(sha256(s.c_str(), s.length()), "04f8f86af2cd14ffe9bbe8da1518ce9c980ae13fba87feb386b103544e9c4c6b");
}

TEST(Hash, InputSize100MB) {
	const std::string s(1024 * 1000 * 100, 'x');
	Expect(sha256(s.c_str(), s.length()),"826721880263dcc23004cb09bb7a70bb3f102219411c9e8125fcf5dae0379ed8");
}

TEST(Hash, BinaryData) {
	constexpr unsigned char data[] = {0x00, 0xFF, 0x00};
	constexpr auto length = sizeof(data)/sizeof(char);
	Expect(sha256(data, length), "2c8d07cd986f58eb210bd800133d6645c7340c59865377c8ea431cebca0b3113");
}


TEST(Hash, UpdateAfterFinish) {
	constexpr std::string input{"hello world"};
	constexpr auto expectedSha = "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9";
	SHA256_CTX ctxt;
	sha256_init(&ctxt);
	sha256_update(&ctxt, input.c_str(), input.length());
	const auto result1= sha256_finish(&ctxt);
	Expect(result1, expectedSha);
	// calling update again. this is just garbage and might not even be worth
	sha256_update(&ctxt, input.c_str(), input.length());
	const auto result2= sha256_finish(&ctxt);
	ExpectNotEqual(result2, expectedSha);
}

TEST(Hash, MultipleFinishes)
{
	constexpr std::string hello{"hello"};
	constexpr std::string world{"world"};

	SHA256_CTX ctxt;
	sha256_init(&ctxt);
	sha256_update(&ctxt, hello.c_str(), hello.length());
	sha256_update(&ctxt, world.c_str(), world.length());

	const auto result1 = sha256_finish(&ctxt);
	const auto result2 = sha256_finish(&ctxt);

	// Calling finish on a context invalidates it
	EXPECT_NE(result1, result2);
}


TEST(Hash, Sha256Neq) {
	EXPECT_NE(sha256("", 0), sha256("aaa", 3));
}

TEST(Hash, Sha256Copy)
{
	const auto digest1 = sha256("hello", 5);
	const SHA256_DIGEST digest2 = digest1;

	EXPECT_EQ(digest1, digest2);

	const auto digest3 = sha256("hello!", 6);
	EXPECT_NE(digest1, digest3);
}

TEST(Hash, Sha256StrFormat)
{
	const auto digest = sha256("test", 4);

	char buffer[SHA256_MAXSTRSIZE];
	sha256_str(digest, buffer, sizeof(buffer));

	const std::string_view str{buffer};

	// Exactly 64 hex characters
	EXPECT_EQ(str.length(), 64u);

	for(char c : str)
	{
		EXPECT_TRUE(
			(c >= '0' && c <= '9') ||
			(c >= 'a' && c <= 'f')
		) << "Invalid hex character: " << c;
	}
}

TEST(Hash, Sha256StrBufferSize)
{
	const auto digest = sha256("test", 4);

	// Intentionally too small
	char buffer[8];
	buffer[0] = '\0';

	sha256_str(digest, buffer, sizeof(buffer));

	// Must be null-terminated
	EXPECT_EQ(buffer[sizeof(buffer) - 1], '\0');
}
TEST(Hash, EmptyUpdates) {
	SHA256_CTX ctxt;
	sha256_init(&ctxt);
	sha256_update(&ctxt, "", 0);

	const auto result = sha256_finish(&ctxt);
	constexpr auto expected = "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

	Expect(result, expected);
}