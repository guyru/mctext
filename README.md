# mctext

A simple text generator based on Markov Chains I built a long time ago.

## Building

```
./autogen.sh
./configure && make
```

## Usage

```
Usage: mctext [options] FILE
Reads a sample text from file and generate new text based on it using Markov chains.

Options:
  -h [ --help ]                   produce this help message
  --version                       prints version string
  -w [ --num-of-words ] arg (=40) how many words should be generated
  -s [ --steps ] arg (=2)         the number of steps used in the Markov chain.

With no FILE, or when FILE is -, read standard input.
```





