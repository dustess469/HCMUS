from bitcoinutils.setup import setup
from bitcoinutils.utils import to_satoshis
from bitcoinutils.transactions import Transaction, TxInput, TxOutput
from bitcoinutils.keys import PrivateKey, P2shAddress
from bitcoinutils.constants import SIGHASH_ALL
from bitcoinutils.script import Script  

def task1():
    setup("testnet")
    
    # priv = PrivateKey(secret_exponent=7112002) 
    priv = PrivateKey("cMahea7zqjxrtgAbB7LSGbcQUr1uX1ojuat9jZodMgGtqPtt5sVj") 
    print("\nPrivate key WIF:", priv.to_wif(compressed=True))
    pub = priv.get_public_key() # 03a329509e0b39229bc8375b351078e23b5da91a6bbad6f394ece660fb3c5041d6
    print("Public key:", pub.to_hex(compressed=True))
    address = pub.get_address()
    print("Address: ", address.to_string())

    locked_txid = 'e727af23f5fff357ba36481100cabc18c172343493ec58077ca0cdbd4abda634'
    locked_vout = 0 

    input_tx = TxInput(locked_txid, locked_vout)

    output_value =  to_satoshis(0.00001)
    output_script = address.to_script_pub_key()
    output_tx = TxOutput(output_value, output_script)

    tx = Transaction([input_tx], [output_tx])

    sig = priv.sign_input(tx, 0, SIGHASH_ALL)
    tx.inputs[0].script_sig = Script([sig])

    signed_tx = tx.serialize()

    # print raw signed transaction ready to be broadcasted
    print("\nRaw signed transaction:\n" + signed_tx)

    # print the size of the final transaction
    print("\nSigned transaction size (in bytes):\n" + str(tx.get_size()))

    print("TX id: ", tx.get_txid())

def task2():
    setup('testnet')  # or 'mainnet' for main network

    # Create two private keys
    priv_key1 = PrivateKey(secret_exponent=20127090)
    priv_key2 = PrivateKey(secret_exponent=20128024)

    print("Private key 1: ", priv_key1.to_wif())
    print("Private key 2: ", priv_key2.to_wif())

    # Get public keys from private keys
    pub_key1 = priv_key1.get_public_key()
    pub_key2 = priv_key2.get_public_key()

    # Create a 2-of-2 multisig script
    multisig_script = Script(['OP_2', pub_key1.to_hex(), pub_key2.to_hex(), 'OP_2', 'OP_CHECKMULTISIG'])

    # Get the multisig address from the script
    # multisig_address = P2shAddress.from_script(multisig_script)
    multisig_address = P2shAddress.from_address("2N5hP2swwBLC5NJMsjMzeGPR7AFxRyN2WHg")

    print("Multisign address: ", multisig_address.to_string())

    tx_id_to_spend = '30c815141207f2ae2b6a5454d70509d92f34bcc52db022a616e770340de6952f'
    prev_tx_output_index = 0

    tx_in = TxInput(tx_id_to_spend, prev_tx_output_index)
    tx_out = TxOutput(to_satoshis(0.0008), pub_key1.get_address().to_script_pub_key())

    tx = Transaction([tx_in], [tx_out])

    sig1 = priv_key1.sign_input(tx, 0, pub_key1.get_address().to_script_pub_key())
    sig2 = priv_key2.sign_input(tx, 0, pub_key2.get_address().to_script_pub_key())

    tx_in.script_sig = Script([sig1, sig2])

    print("\nRaw signed transaction:\n" + tx.serialize())

def main():
    task2()

if __name__ == "__main__":
    main()