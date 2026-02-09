#ifndef TEEWORLDS_SHA256_H
#define TEEWORLDS_SHA256_H
#include "hash.h"
#include "hash_ctxt.h"
#include <span>
namespace cryptographic_hashing
{
    class Sha256
    {
    public:
        Sha256()

        {
            sha256_init(&ctxt_);
        }

        ~Sha256() = default;

        void Update(const std::span<const std::byte>& input)
        {
            if (!finished_)
            {
                sha256_update(&ctxt_, input.data(), input.size());
            } else
            {
                throw std::logic_error("Update called after Finish!");
            }

        }

        void Update(const std::string_view s)
        {
            Update(std::as_bytes(std::span(s.data(), s.size())));
        }
        void Update(const char* data, const std::size_t len)
        {
            Update(std::as_bytes(std::span(data, len)));
        }

        void Update(const std::vector<std::byte>& v)
        {
            Update(std::span(v));
        }
        [[nodiscard]] SHA256_DIGEST Finish()
        {
            if (finished_)
            {
                throw std::logic_error("Finish was already called on this context!");
            }
            finished_ = true;
            return sha256_finish(&ctxt_);
        };
    private:
        SHA256_CTX ctxt_;
        bool finished_{};
    };
};

#endif //TEEWORLDS_SHA256_H