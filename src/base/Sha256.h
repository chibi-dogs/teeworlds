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
                throw std::logic_error("not allowed!");
            }

        }
        void Update(const std::string& s)
        {
            Update(std::as_bytes(std::span(s.data(), s.size())));
        }
        [[nodiscard]] SHA256_DIGEST Finish()
        {
            finished_ = true;
            return sha256_finish(&ctxt_);
        };
    private:
        SHA256_CTX ctxt_;
        bool finished_{};
    };
};

#endif //TEEWORLDS_SHA256_H