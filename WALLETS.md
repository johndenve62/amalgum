# Amalgum wallets (local regtest)

**Network:** regtest on this box (`/workspace/amalgum-data`)  
**No private keys in this file.** Keys live only in `wallet.dat` / backup copies under the datadir.

## Labeled receiving addresses

| Label | Purpose | Address (regtest) |
|-------|---------|-------------------|
| `treasury-75` | Ation reserve sleeve (maps to 75% policy intent) | `mryV5gWFUDG5KsLDicPb6j5iHYFw9vbeCV` |
| `ops-hot` | Hot / ops spending sleeve | `moMqRrvp6MfERv92GLgFUZKRA6yBJLpoNX` |
| `mining-rewards` | Mining payouts | `mxHgDRYMtippmMPfZujPPh5MKtRtyZA4W8` |

Demo transfer: **12.50 Ation** sent to `treasury-75`  
txid: `48458a416d55e3bcfeab621f6fb99311de48524972227b3ed1d44e87609f1c38`

These are **regtest** addresses (test prefixes). Mainnet Amalgum addresses will look different once you run `-main` with the hard genesis.

## Create another labeled address

```bash
CLI="/workspace/scarce-doge-fork/src/amalgum-cli -datadir=/workspace/amalgum-data -conf=/workspace/amalgum-data/amalgum.conf"

$CLI getnewaddress "treasury-75"      # more addresses under same account/label
$CLI getnewaddress "ops-hot"
$CLI getnewaddress "mining-rewards"

$CLI getaddressesbyaccount "treasury-75"
$CLI listaccounts
```

(Dogecoin 1.14-style **accounts** are used as labels here.)

## Send

```bash
$CLI sendtoaddress "<address>" 1.00 "comment"
# or credit an account locally (same wallet):
$CLI move "" "treasury-75" 1.00
```

## Backup `wallet.dat` (contains keys — keep private)

```bash
$CLI backupwallet "/workspace/amalgum-data/regtest/backups/wallet-backup-YYYYMMDD.dat"
```

Existing backups on this box:

- `/workspace/amalgum-data/regtest/backups/wallet-backup-regtest.dat`
- `/workspace/amalgum-data/regtest/backups/wallet-backup-after-treasury.dat`

Also copy `regtest/wallet.dat` offline when you care about funds.  
**Do not commit backups or dumpprivkey output into git or the public zip.**

## Related

- Reserve allocation intent: [`RESERVE_POLICY.md`](./RESERVE_POLICY.md) (75% Ation / 25% BTC+DOGE+ETH off-chain)
- Node how-to: [`LAUNCH_STATUS.md`](./LAUNCH_STATUS.md)
