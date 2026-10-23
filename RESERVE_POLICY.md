# Amalgum reserve policy (off-chain)

**Amalgum (Ation)** consensus does **not** hold BTC, DOGE, or ETH. Those assets live on other networks. This document is the **intended treasury / reserve allocation** for whoever operates Amalgum’s reserves (foundation, multisig, or custodian). It is a policy layer on top of the chain, not a consensus rule.

## Target allocation (by market value)

| Sleeve | Target share | Notes |
|--------|-------------:|-------|
| **Amalgum (Ation)** | **75%** | Coin itself held in treasury / uncirculated / protocol-controlled wallets as you define |
| **External crypto basket** | **25%** | BTC + DOGE + ETH combined |
| — Bitcoin (BTC) | ~8.333% | One-third of the 25% sleeve |
| — Dogecoin (DOGE) | ~8.333% | One-third of the 25% sleeve |
| — Ethereum (ETH) | ~8.333% | One-third of the 25% sleeve |

**Total = 100%.**  
Rebalance when any sleeve drifts beyond a band you set (suggested starting band: ±2 percentage points of the 25% basket, and ±5 on the 75% Ation sleeve).

## What this is / is not

**Is:** a published target for how reserve assets should be split; a basis for periodic public attestations (addresses + amounts).

**Is not:**
- Enforced by `amalgumd` or block validation
- A guaranteed peg to BTC/DOGE/ETH
- A sell-tax or automatic “price goes up when you sell” mechanism
- Investment, legal, or securities advice

Holding Ation in the 75% sleeve does **not** create extrinsic backing by itself; the **25%** external basket is the part that can be independently verified on BTC/DOGE/ETH explorers.

## Custody (recommended shape)

1. **Multisig or institutional custody** for BTC, DOGE, and ETH (separate wallets per asset).
2. **Separate** Amalgum addresses for the 75% sleeve (cold + hot policy as you prefer).
3. **Never** put seed phrases in chat, code repos, or this markdown file.
4. Publish a **reserve address list** and update it when keys rotate.

## Transparency cadence (suggested)

| Cadence | Action |
|---------|--------|
| Weekly | Snapshot balances of published reserve addresses |
| Monthly | Short attestation: % mix vs targets, outstanding Ation supply note |
| On drift | Rebalance toward targets or explain why not |

Proof for the 25% sleeve = on-chain balances at published addresses. Proof for the 75% Ation sleeve = Amalgum addresses you publish (after the network exists).

## Relation to the scarce chain

- Max supply remains **1,000,000 Ation** with **2** decimals (see `AMALGUM_README.md`).
- Reserve policy does **not** change subsidy, ports, or consensus.
- If you later want on-chain buybacks funded by the 25% basket, that is an **operational** program (sell BTC/DOGE/ETH, buy Ation), not a Dogecoin-fork consensus feature.

## Open operator choices

- Exact legal entity / multisig signers
- Whether the 75% is locked, burned-eligible, or liquid treasury
- Rebalance bands and who may move funds
- Whether to use a third-party attestor

