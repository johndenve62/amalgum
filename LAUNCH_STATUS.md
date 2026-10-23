# Amalgum local launch status

**Honest scope:** This is a **local single-node regtest** on this box.  
It is **not** a public mainnet. There are **no seed nodes**, **no external miners**, and **no exchange**. Easy PoW was used so genesis could be mined on CPU in seconds.

| Item | Value |
|------|-------|
| Name / ticker | Amalgum / Ation |
| Mode running now | **regtest** |
| Datadir | `/workspace/amalgum-data` (chain data under `…/regtest/`) |
| Config | `/workspace/amalgum-data/amalgum.conf` |
| Daemon binary | `/workspace/scarce-doge-fork/src/amalgumd` → symlink to `dogecoind` |
| CLI binary | `/workspace/scarce-doge-fork/src/amalgum-cli` → symlink to `dogecoin-cli` |
| RPC | `127.0.0.1:18443` credentials in local `amalgum.conf` (not published) |
| P2P (unused; listen=0) | 18444 |

## Genesis (hardcoded + asserts restored)

### Main (public-oriented)

| Field | Value |
|-------|-------|
| nBits | **`0x1e0ffff0`** (Dogecoin-typical scrypt difficulty) |
| powLimit | `0x00000fffffffffffffffffffffffffffffffffffffffffffffffffffffffffff` |
| time | `1700000000` |
| nonce | `21248` |
| hash | `656f40174b6a252e60bce17a011b28a2a81fc4140df8004e1bcc850c4dd94131` |
| merkle | `540c8e076ccc7809064a970c2fed39edc39ba6a61d0afd2082aad5b1bf86b147` |
| mined in | ~5.0s CPU on this box |

**Honesty:** This is a real Dogecoin-class genesis difficulty, suitable as a **starting point** for a public chain. It does **not** by itself make a live public network (still no seeds, peers, or miners beyond this box). Regtest keeps easy `0x207fffff` so local demos stay fast.

### Regtest (local node — unchanged / easy)

| Field | Value |
|-------|-------|
| nBits | `0x207fffff` (easy) |
| hash | `86231433c783a0fd5a7cb11cc10568e7022686871953af14f047fa5f96ae4440` |
| merkle | `540c8e076ccc7809064a970c2fed39edc39ba6a61d0afd2082aad5b1bf86b147` |

See also `genesis_main_hard.json` / `genesis_values.json`.

## Scarcity (unchanged)

Max **1,000,000 Ation**, **2 decimals**, subsidy schedule then **0**. No on-chain sell-fee price pump.

## Start / stop

```bash
# Start (regtest via conf)
/workspace/scarce-doge-fork/src/amalgumd \
  -datadir=/workspace/amalgum-data \
  -conf=/workspace/amalgum-data/amalgum.conf \
  -daemon

# RPC
/workspace/scarce-doge-fork/src/amalgum-cli \
  -datadir=/workspace/amalgum-data \
  -conf=/workspace/amalgum-data/amalgum.conf \
  getblockchaininfo

# Mine more blocks (regtest)
ADDR=$(/workspace/scarce-doge-fork/src/amalgum-cli -datadir=/workspace/amalgum-data -conf=/workspace/amalgum-data/amalgum.conf getnewaddress)
/workspace/scarce-doge-fork/src/amalgum-cli -datadir=/workspace/amalgum-data -conf=/workspace/amalgum-data/amalgum.conf generatetoaddress 1 "$ADDR"

# Stop
/workspace/scarce-doge-fork/src/amalgum-cli -datadir=/workspace/amalgum-data -conf=/workspace/amalgum-data/amalgum.conf stop
```

## Leftovers / blockers

- Makefile still builds targets named **`dogecoind` / `dogecoin-cli`** (configure rename incomplete in `Makefile.am`); use `amalgumd` / `amalgum-cli` symlinks.
- Log banner still says **“Dogecoin version …”**.
- Easy `nBits` is intentional for local launch — **raise difficulty and re-mine genesis** before any public network.
- No DNS seeds / peers configured.
- Coinbase maturity is 60 blocks on this chain config; immature rewards show balance `0` until then.

## Build note

```bash
cd /workspace/scarce-doge-fork
./autogen.sh && ./configure --without-gui --disable-tests --disable-bench && make -j$(nproc)
```


## Wallets

See [`WALLETS.md`](./WALLETS.md) for labeled regtest addresses (no keys).
