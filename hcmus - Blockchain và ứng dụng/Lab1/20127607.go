package main

import (
	"bytes"
	"crypto/sha256"
	"fmt"
	"time"
)

type Transaction struct {
	Data []byte
}

type Block struct {
	Timestamp     int64
	Transactions  []*Transaction
	PrevBlockHash []byte
	Hash          []byte
}

type Blockchain struct {
	blocks []*Block
}

// This function sets the hash for a block.
func (b *Block) SetHash() {
	timestamp := []byte(fmt.Sprintf("%x", b.Timestamp))
	headers := bytes.Join([][]byte{b.PrevBlockHash, b.HashTransactions(), timestamp}, []byte{})
	hash := sha256.Sum256(headers)

	b.Hash = hash[:]
}

// This function calculates the hash representation of the transactions in the block.
func (b *Block) HashTransactions() []byte {
	var txHashes [][]byte
	for _, tx := range b.Transactions {
		txHashes = append(txHashes, tx.Data) // Assuming the data itself is a hash for simplification.
	}
	txHash := sha256.Sum256(bytes.Join(txHashes, []byte{}))
	return txHash[:]
}

// Function to add a block to the blockchain.
func (bc *Blockchain) AddBlock(transactions []*Transaction) {
	prevBlock := bc.blocks[len(bc.blocks)-1]
	newBlock := &Block{time.Now().Unix(), transactions, prevBlock.Hash, []byte{}}
	newBlock.SetHash()
	bc.blocks = append(bc.blocks, newBlock)
}

func NewGenesisBlock() *Block {
	return &Block{time.Now().Unix(), []*Transaction{{[]byte("Genesis Block")}}, []byte{}, []byte{}}
}

func NewBlockchain() *Blockchain {
	return &Blockchain{[]*Block{NewGenesisBlock()}}
}

func main() {
	bc := NewBlockchain()

	// Add a new block with a single transaction
	tx1 := &Transaction{[]byte("This is transaction 1")}
	bc.AddBlock([]*Transaction{tx1})

	// Add another block with two transactions
	tx2 := &Transaction{[]byte("This is transaction 2")}
	bc.AddBlock([]*Transaction{tx2})

	tx3 := &Transaction{[]byte("This is transaction 3")}
	bc.AddBlock([]*Transaction{tx3})
	// Print details of the blockchain
	for _, block := range bc.blocks {
		fmt.Printf("Prev. Hash: %x\n", block.PrevBlockHash)
		fmt.Printf("Hash: %x\n", block.Hash)
		fmt.Printf("Timestamp: %d\n", block.Timestamp)
		for _, tx := range block.Transactions {
			fmt.Printf("Transaction Data: %s\n", tx.Data)
		}
		fmt.Println("-------------------------------")
	}
}
