# Amalgum (Ation)

**Amalgum** is a scarce, Dogecoin-codebase fork. The coin unit is **Ation**.

This tree is a **scaffold**, not a launched mainnet. Genesis is not mined yet; do not treat binaries as production-ready.

## What it is

- Own UTXO chain (Scrypt PoW), forked from [Dogecoin Core](https://github.com/dogecoin/dogecoin)
- **Max supply: 1,000,000 Ation** (finite — subsidy becomes 0 after emission)
- **2 decimal places** (`COIN = 100`) so amounts stay coarse (not 8-decimal dust)
- **~60 second** Digishield-style blocks from genesis
- **No AuxPoW / Litecoin merge-mining** — independent chain
- Distinct magic bytes, ports, and address versions from Dogecoin

## Scarcity rules (subsidy)

| Heights | Reward / block | Era total |
|--------:|---------------:|----------:|
| 0–99,999 | 5.00 Ation | 500,000 |
| 100,000–199,999 | 2.50 | 250,000 |
| 200,000–299,999 | 1.25 | 125,000 |
| 300,000–399,999 | 0.75 | 75,000 |
| 400,000–499,999 | 0.50 | 50,000 |
| ≥ 500,000 | **0** | 0 |

**Total minted via block subsidy = 1,000,000.00 Ation.**  
Dogecoin’s permanent **10,000 DOGE/block** inflation tail is **removed**.

## How it differs from Dogecoin

| | Dogecoin | Amalgum |
|--|----------|---------|
| Supply | Effectively uncapped (tail inflation) | Hard cap 1M Ation |
| Decimals | 8 | 2 |
| Merge-mining | AuxPoW (Litecoin) | Disabled |
| Digishield | After height 145000 | From genesis |
| P2P / RPC | 22556 / 22555 | **34556 / 34555** |
| Ticker | DOGE | **Ation** |

## Honest note: sell fees / “price pump”

There is **no on-chain sell tax** that raises the coin’s price when you sell.  
Exchanges settle trades off-chain; this node only sees transfers. Miner fees go to miners, not into a buyback. Scarcity can support a higher **unit** price only if people actually want the coin — it does not create demand or listings by itself.

## Build overview (daemon)

```bash
cd /workspace/scarce-doge-fork
./autogen.sh
./configure --without-gui
make -j$(nproc)
```

Deps (Ubuntu-style): `build-essential`, `libtool`, `autotools-dev`, `automake`, `pkg-config`, `libssl-dev`, `libevent-dev`, `libboost-all-dev`, Berkeley DB 5.x as upstream expects. See `doc/build-unix.md`.

Suggested names after configure: `amalgumd`, `amalgum-cli`, datadir `~/.amalgum`, conf `amalgum.conf`.

## Next hard step: mine genesis

Mainnet genesis nonce is still `0` and asserts are commented. Before any public network:

1. Edit timestamp/nonce/reward in `src/chainparams.cpp` if needed  
2. Add a temporary scrypt mining loop (see `FORK_PLAN.md`)  
3. Build, run once, hardcode hash / merkle / nonce, restore asserts  

## Docs

- Full fork checklist: [`FORK_PLAN.md`](./FORK_PLAN.md)  
- Param drafts (reference): `/workspace/scarce-doge-fork-params/`

## Reserve policy

Target mix: **75% Ation** + **25%** BTC/DOGE/ETH (equal thirds of that sleeve). See [`RESERVE_POLICY.md`](./RESERVE_POLICY.md). This is off-chain treasury policy, not consensus.
