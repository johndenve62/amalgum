# Amalgum (Ation) — Dogecoin Fork Plan

**Name:** Amalgum  
**Ticker / currency unit:** Ation  
**Source clone:** `/workspace/scarce-doge-fork` (from `dogecoin/dogecoin`)  
**Status:** local **regtest launched** on this box; genesis hardcoded (easy nBits); **not a public mainnet**

---

## What’s done

- [x] Shallow clone of Dogecoin
- [x] `COIN = 100` (2 decimals), `CENT = 1`, `MAX_MONEY = 1_000_000 * COIN`
- [x] `CURRENCY_UNIT = "Ation"`
- [x] `FormatMoney` / fee rate strings use `%d.%02d`
- [x] Finite subsidy schedule totaling **exactly 1,000,000** Ation, then **0** (no 10k/block tail)
- [x] Digishield-from-genesis; **AuxPoW disabled** (single consensus era)
- [x] New magic `d1 c7 b1 de`, P2P **34556**, RPC **34555**
- [x] New base58 version bytes (63 / 125 / 191)
- [x] Datadir `.amalgum`, conf `amalgum.conf`, pid `amalgumd.pid`
- [x] `configure.ac` package names → `amalgumd` / `amalgum-cli` / `amalgum-qt` / `amalgum-tx`
- [x] Fee floors adjusted so `COIN=100` does not zero out relay fees
- [x] Dogecoin DNS seeds / historical checkpoints cleared
- [x] This plan + `AMALGUM_README.md`

## What’s left (manual)

1. **Mine mainnet (and testnet) genesis** — see command below  
2. Hardcode genesis `hash` / `merkle` / `nNonce`; restore `assert(...)`  
3. Re-tune dust/priority UX copy; rename remaining `"dogecoin"` strings in Qt/RPC help if shipping a GUI  
4. Add DNS seeds / peers; smoke-test **regtest** after genesis consistency  
5. Fix or skip upstream unit/QA tests that assume DOGE amounts and old genesis  
6. Legal, branding assets, explorers, miners, exchange ops — out of scope here  

**Not in scope:** on-chain sell/transfer tax that “pushes price up.”

---

## Final network summary

| Knob | Value |
|------|-------|
| Max supply | 1,000,000 Ation |
| Decimals | 2 (`COIN=100`) |
| Block time | ~60s Digishield |
| AuxPoW | Disabled |
| P2P magic | `d1 c7 b1 de` |
| P2P port | 34556 |
| RPC port | 34555 |
| Pubkey / script / secret | 63 / 125 / 191 |
| Datadir | `~/.amalgum` |

### Subsidy (exact 1M)

`5.00` → `2.50` → `1.25` → `0.75` → `0.50` over successive 100,000-block eras, then `0`.

---

## Exact next command (genesis mine — do not run for hours in automation)

Genesis currently uses `nTime=1700000000`, `nNonce=0`, `nBits=0x1e0ffff0`, reward `5 * COIN`. Asserts are disabled.

**In `src/chainparams.cpp` `CMainParams`**, temporarily after `genesis = CreateGenesisBlock(...)`:

```cpp
#include "arith_uint256.h"
#include "pow.h" // if needed for CheckProofOfWork / GetPoWHash

arith_uint256 hashTarget = arith_uint256().SetCompact(genesis.nBits);
while (UintToArith256(genesis.GetPoWHash()) > hashTarget) {
    ++genesis.nNonce;
}
LogPrintf("AMALGUM GENESIS hash=%s merkle=%s nonce=%u time=%u\n",
    genesis.GetHash().ToString(),
    genesis.hashMerkleRoot.ToString(),
    genesis.nNonce, genesis.nTime);
```

Then build and run once (regtest or a one-shot main-params print is fine):

```bash
cd /workspace/scarce-doge-fork
./autogen.sh && ./configure --without-gui && make -j$(nproc)
# After adding the loop + a LogPrintf path that runs at startup:
./src/amalgumd -printtoconsole  # stop after the GENESIS line prints
```

Copy printed `hash`, `merkle`, `nonce` back into `chainparams.cpp`, remove the loop, restore asserts. Repeat for testnet with its own time/nonce.

Scrypt genesis at `0x1e0ffff0` is usually minutes–hours on CPU — run locally when ready; **not** required for this scaffold.

---

## Key files touched

| File | Change |
|------|--------|
| `src/amount.h` / `amount.cpp` | COIN, MAX_MONEY, Ation, `%02d` |
| `src/utilmoneystr.cpp` | `%02d` FormatMoney |
| `src/dogecoin.cpp` | Finite subsidy |
| `src/chainparams.cpp` | Network identity, Digishield, no AuxPoW, genesis placeholders |
| `src/chainparamsbase.cpp` | RPC ports |
| `src/policy/policy.h`, `src/validation.h` | Fee floors for 2 decimals |
| `src/util.cpp` / `util.h` | `.amalgum`, conf/pid, thread prefix |
| `configure.ac` | Amalgum Core binary names |

Reference drafts: `/workspace/scarce-doge-fork-params/`


See also: [`LAUNCH_STATUS.md`](./LAUNCH_STATUS.md)
