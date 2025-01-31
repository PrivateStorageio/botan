/*
* EMSA1
* (C) 1999-2007 Jack Lloyd
*
* Botan is released under the Simplified BSD License (see license.txt)
*/

#ifndef BOTAN_EMSA1_H_
#define BOTAN_EMSA1_H_

#include <botan/internal/emsa.h>
#include <botan/hash.h>

namespace Botan {

/**
* EMSA1 from IEEE 1363
* Essentially, sign the hash directly
*/
class EMSA1 final : public EMSA
   {
   public:
      /**
      * @param hash the hash function to use
      */
      explicit EMSA1(std::unique_ptr<HashFunction> hash) : m_hash(std::move(hash)) {}

      std::unique_ptr<EMSA> new_object() override;

      std::string name() const override;

      bool requires_message_recovery() const override { return false; }

      AlgorithmIdentifier config_for_x509(const std::string& algo_name,
                                          const std::string& cert_hash_name) const override;
   private:
      size_t hash_output_length() const { return m_hash->output_length(); }

      void update(const uint8_t[], size_t) override;
      secure_vector<uint8_t> raw_data() override;

      secure_vector<uint8_t> encoding_of(const secure_vector<uint8_t>& msg,
                                         size_t output_bits,
                                         RandomNumberGenerator& rng) override;

      bool verify(const secure_vector<uint8_t>& coded,
                  const secure_vector<uint8_t>& raw,
                  size_t key_bits) override;

      std::unique_ptr<HashFunction> m_hash;
   };

}

#endif
