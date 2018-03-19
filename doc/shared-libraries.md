Shared Libraries
================

## Dealtokenconsensus

The purpose of this library is to make the verification functionality that is critical to Dealtoken's consensus available to other applications, e.g. to language bindings.

### API

The interface is defined in the C header `Dealtokenconsensus.h` located in  `src/script/Dealtokenconsensus.h`.

#### Version

`Dealtokenconsensus_version` returns an `unsigned int` with the API version *(currently at an experimental `0`)*.

#### Script Validation

`Dealtokenconsensus_verify_script` returns an `int` with the status of the verification. It will be `1` if the input script correctly spends the previous output `scriptPubKey`.

##### Parameters
- `const unsigned char *scriptPubKey` - The previous output script that encumbers spending.
- `unsigned int scriptPubKeyLen` - The number of bytes for the `scriptPubKey`.
- `const unsigned char *txTo` - The transaction with the input that is spending the previous output.
- `unsigned int txToLen` - The number of bytes for the `txTo`.
- `unsigned int nIn` - The index of the input in `txTo` that spends the `scriptPubKey`.
- `unsigned int flags` - The script validation flags *(see below)*.
- `Dealtokenconsensus_error* err` - Will have the error/success code for the operation *(see below)*.

##### Script Flags
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_NONE`
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_P2SH` - Evaluate P2SH ([BIP16](https://github.com/Dealtoken/bips/blob/master/bip-0016.mediawiki)) subscripts
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_DERSIG` - Enforce strict DER ([BIP66](https://github.com/Dealtoken/bips/blob/master/bip-0066.mediawiki)) compliance
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY` - Enforce NULLDUMMY ([BIP147](https://github.com/Dealtoken/bips/blob/master/bip-0147.mediawiki))
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY` - Enable CHECKLOCKTIMEVERIFY ([BIP65](https://github.com/Dealtoken/bips/blob/master/bip-0065.mediawiki))
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY` - Enable CHECKSEQUENCEVERIFY ([BIP112](https://github.com/Dealtoken/bips/blob/master/bip-0112.mediawiki))
- `Dealtokenconsensus_SCRIPT_FLAGS_VERIFY_WITNESS` - Enable WITNESS ([BIP141](https://github.com/Dealtoken/bips/blob/master/bip-0141.mediawiki))

##### Errors
- `Dealtokenconsensus_ERR_OK` - No errors with input parameters *(see the return value of `Dealtokenconsensus_verify_script` for the verification status)*
- `Dealtokenconsensus_ERR_TX_INDEX` - An invalid index for `txTo`
- `Dealtokenconsensus_ERR_TX_SIZE_MISMATCH` - `txToLen` did not match with the size of `txTo`
- `Dealtokenconsensus_ERR_DESERIALIZE` - An error deserializing `txTo`
- `Dealtokenconsensus_ERR_AMOUNT_REQUIRED` - Input amount is required if WITNESS is used

### Example Implementations
- [NDealtoken](https://github.com/NicolasDorier/NDealtoken/blob/master/NDealtoken/Script.cs#L814) (.NET Bindings)
- [node-libDealtokenconsensus](https://github.com/bitpay/node-libDealtokenconsensus) (Node.js Bindings)
- [java-libDealtokenconsensus](https://github.com/dexX7/java-libDealtokenconsensus) (Java Bindings)
- [Dealtokenconsensus-php](https://github.com/Bit-Wasp/Dealtokenconsensus-php) (PHP Bindings)
