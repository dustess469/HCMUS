# P2PKH Script
from bitcoin import *
from bitcoin.wallet import CBitcoinSecret, P2PKHBitcoinAddress
# Generate a random private key
private_key = CBitcoinSecret.from_secret_bytes(os.urandom(32))
# Derive the public key and Bitcoin address
public_key = private_key.pub
address = P2PKHBitcoinAddress.from_pubkey(public_key)
print("Private Key:", private_key)
print("Public Key:", public_key.hex())
print("Bitcoin Address:", address)