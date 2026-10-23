# Amalgum (Ation) — Public Launch Guide

## Honest status (read first)

- **There is a single Amalgum mainnet node, and it runs only on a private build/dev VM.** That VM is **not** a public P2P host, so no one on the internet can connect to it yet. **The coin is not live worldwide.**
- The mainnet genesis is final (`656f40174b6a252e60bce17a011b28a2a81fc4140df8004e1bcc850c4dd94131`). The early blocks were solo-mined to the owner address on that VM. If you replay or restart the chain on a public server, the same genesis and the same consensus rules apply.
- This is a **pre-release** build of Dogecoin Core 1.14 with changes. It has not had a security audit. Its binary and log names still say "dogecoin" in places.
- You need two or more public nodes, and an exchange or market, before Ation can have any real price. A low supply does **not** create value by itself.

## Network parameters

| Item | Value |
|---|---|
| P2P port | **34556** |
| RPC port | 34555 (keep it localhost-only) |
| Magic | `d1c7b1de` |
| Address prefix | `S…` (base58 63), P2SH 125, WIF 191 |
| Decimals | 2 (1 Ation = 100 base units) |
| Max supply | 1,000,000 Ation; subsidy 5 → 2.5 → 1.25 → 0.75 → 0.5 per 100k blocks, then 0 |
| PoW | Scrypt, Digishield; AuxPoW disabled |
| Coinbase maturity | 60 blocks |

## 1. Get a VPS

- Any Linux VPS works: Ubuntu 22.04/24.04, 2 vCPU, 2–4 GB RAM, and 20 GB disk or more. Providers include Hetzner, DigitalOcean, Vultr, and so on.
- Plan on **at least 2–3 VPSes in different regions** so the network survives one going down.

```bash
sudo apt update && sudo apt install -y build-essential libtool autotools-dev automake pkg-config \
  libssl-dev libevent-dev bsdmainutils libboost-all-dev libdb5.3++-dev unzip
sudo useradd -m -s /bin/bash amalgum
```

## 2. Install from the release zip

```bash
sha256sum -c Amalgum-Ation-fork.zip.SHA256
unzip Amalgum-Ation-fork.zip -d /opt/amalgum
# Prebuilt (x86_64 Linux): /opt/amalgum/bin/amalgumd, amalgum-cli
# Or rebuild: cd /opt/amalgum/scarce-doge-fork && ./autogen.sh && ./configure --without-gui --disable-tests --disable-bench && make -j$(nproc)
sudo install -m755 /opt/amalgum/bin/amalgumd /opt/amalgum/bin/amalgum-cli /usr/local/bin/
```

## 3. Example `amalgum.conf`

Path: `/home/amalgum/.amalgum/amalgum.conf`. Set it to `chmod 600`. **Never commit or share the RPC password.**

```ini
server=1
listen=1
txindex=1
port=34556
bind=0.0.0.0
rpcport=34555
rpcbind=127.0.0.1
rpcallowip=127.0.0.1
rpcuser=amalgum
rpcpassword=CHANGE_ME_LONG_RANDOM   # openssl rand -hex 32
maxconnections=64
# Peers: add every other public node you run
addnode=SEED1_IP:34556
addnode=SEED2_IP:34556
# seednode=SEED1_IP:34556   # connect, fetch addresses, then disconnect
```

## 4. Example systemd unit

`/etc/systemd/system/amalgumd.service`:

```ini
[Unit]
Description=Amalgum (Ation) node
After=network-online.target
Wants=network-online.target

[Service]
User=amalgum
Group=amalgum
Type=forking
ExecStart=/usr/local/bin/amalgumd -daemon -datadir=/home/amalgum/.amalgum -conf=/home/amalgum/.amalgum/amalgum.conf -pid=/home/amalgum/.amalgum/amalgumd.pid
ExecStop=/usr/local/bin/amalgum-cli -datadir=/home/amalgum/.amalgum stop
PIDFile=/home/amalgum/.amalgum/amalgumd.pid
Restart=on-failure
TimeoutStopSec=120

[Install]
WantedBy=multi-user.target
```

```bash
sudo systemctl daemon-reload && sudo systemctl enable --now amalgumd
amalgum-cli -datadir=/home/amalgum/.amalgum getblockchaininfo
```

## 5. Open port 34556 (P2P only)

```bash
sudo ufw allow 22/tcp
sudo ufw allow 34556/tcp
sudo ufw enable
# Do NOT open 34555 (RPC).
```

Also open 34556/tcp in the provider's cloud firewall or security group. To test from another machine, run `nc -vz VPS_IP 34556`.

## 6. Connect nodes (addnode / seednode)

- On every node, add `addnode=` lines that point to the others. You can also add a peer at runtime with `amalgum-cli addnode IP:34556 add`.
- Check with `amalgum-cli getpeerinfo` and `getconnectioncount`.
- The chain only becomes truly public once at least one public node has synced past the existing owner-mined blocks, or has restarted mining from genesis. Copying the current `blocks/` and `chainstate/` from the dev node preserves the existing owner coins. If you start fresh, they are lost.

## 7. Share the release

- Publish `Amalgum-Ation-fork.zip` along with its `.SHA256`, for example as a GitHub release. Post your seed node IPs or hostnames with it.
- The zip contains **no wallets, private keys, or RPC passwords**. Keep it that way.

## 8. Later steps (not done yet)

- **DNS seed.** Run a DNS seeder, such as `sipa/bitcoin-seeder` with port and magic adapted, at e.g. `seed.amalgum.example`. Add it to `vSeeds` in `src/chainparams.cpp` and ship a new release.
- **Hardcoded seeds.** Fill `chainparamsseeds.h` with stable node IPs.
- **Block explorer.** Run a node with `txindex=1` behind an explorer such as Iquidus/eiquidus or btc-rpc-explorer.
- **Checkpoints.** Add them in chainparams after the chain gains depth.
- **Rename cleanup.** Rename the binary and log banner, then do a full security review.
- **Pools or mining guide.** Optional.

## 9. Reserve policy reminder

See [`RESERVE_POLICY.md`](./RESERVE_POLICY.md). The 75% Ation / 25% BTC+DOGE+ETH treasury split is an **off-chain commitment**. Nothing in consensus enforces it, and there is **no sell tax** on-chain. Publish the treasury address (`treasury-75`), and publish reserve holdings openly if you want to be credible.

## 10. Owner key safety

- The owner wallet backup and the private key live only in `amalgum-mainnet-data/backups/` on the dev VM, with chmod 600. Move them to offline storage (encrypted USB or a password manager). **Never** put them on a VPS that you also use as a public seed node.
- Encrypt the wallet: `amalgum-cli encryptwallet "<strong passphrase>"`.
