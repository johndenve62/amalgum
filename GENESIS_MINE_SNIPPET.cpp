// Paste temporarily into CMainParams after CreateGenesisBlock — Amalgum
// Requires arith_uint256 / GetPoWHash available in this TU (chainparams already has dogecoin scrypt via block header).
//
// arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
// while (UintToArith256(genesis.GetPoWHash()) > hashTarget) {
//     ++genesis.nNonce;
// }
// printf("AMALGUM GENESIS hash=%s merkle=%s nonce=%u\n",
//     genesis.GetHash().ToString().c_str(),
//     genesis.hashMerkleRoot.ToString().c_str(),
//     genesis.nNonce);
