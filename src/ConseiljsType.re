type parameter = Js.t({
  . _type: string,
  name: string,
  optional: bool,
  constituent: string
});

type entryPoint = Js.t({
  . name: string,
  parameters: array(parameter),
  structure: string
});

type conseilServerInfo = Js.t({
  . url: string,
  apiKey: string,
  network: string
});

type tezosContractIntrospector = {
  . [@bs.meth] "generateEntryPointsFromParams": string => array(entryPoint),
  [@bs.meth] "generateEntryPointsFromCode": string => array(entryPoint),
  [@bs.meth] "generateEntryPointsFromAddress": (conseilServerInfo, string, string) => Js.Promise.t(array(entryPoint))
};

type conseilOperator =  | BETWEEN  | EQ  | IN  | LIKE  | LT | BEFORE | GT  | AFTER  | STARTSWITH  | ENDSWITH | ISNULL;
let operatorToString = conseilOperator : string =>
  switch (conseilOperator) {
  | BETWEEN => "between"
  | EQ => "eq"
  | IN => "in"
  | LIKE => "like"
  | LT => "lt"
  | BEFORE => "before"
  | GT => "gt"
  | AFTER => "after"
  | STARTSWITH => "startsWith"
  | ENDSWITH => "endsWith"
  | ISNULL => "isnull"
  };


type conseilFunction = | AVG | COUNT | MAX | MIN | SUM;
let functionToString = conseilFunction: string => 
  switch (conseilFunction) {
    | AVG => "avg"
    | COUNT => "count"
    | MAX => "max"
    | MIN => "min"
    | SUM => "sum"
  };

type conseilSortDirection = | ASC | DESC;
let sortDirectionToString = conseilSortDirection: string => 
  switch (conseilSortDirection) {
    | ASC => "asc"
    | DESC => "desc"
  };

type conseilOutput = | CSV | JSON;
let outputToString = conseilOutput: string => 
  switch (conseilOutput) {
    | CSV => "csv"
    | JSON => "json"
  };

type conseilOrdering = Js.t({
  . field: string,
  direction: conseilSortDirection
});

type conseilPredicate = Js.t({
  . field: string,
  operation: conseilOperator,
  set: array(string),
  inverse: bool
});

type conseilAggregation = Js.t({
  . field: string,
  _function: conseilFunction
});

type conseilQuery = Js.t({
  . fields: array(string),
  predicates: array(conseilPredicate),
  orderBy: array(conseilOrdering),
  limit: int,
  aggregation: array(conseilAggregation),
  output: string
});

type conseilQueryBuilder = {
  . [@bs.meth] "blankQuery": unit => conseilQuery,
  [@bs.meth] "addPredicate": (conseilQuery, string, string, array(string), bool) => conseilQuery,
  [@bs.meth] "addFields": (conseilQuery, string) => conseilQuery,
  [@bs.meth] "addOrdering": (conseilQuery, string, string) => conseilQuery,
  [@bs.meth] "setLimit": (conseilQuery, int) => conseilQuery,
  [@bs.meth] "setOutputType": (conseilQuery, string) => conseilQuery,
  [@bs.meth] "addAggregationFunction": (conseilQuery, string, string) => conseilQuery
};

type tezosBlock = Js.t({
  . active_proposal: string,
  baker: string,
  chain_id: string,
  level: int,
  proto: int,
  predecessor: string,
  timestamp: int,
  validationPass: int,
  fitness: string,
  context: string,
  signature: string,
  protocol: string,
  hash: string,
  operations_hash: string,
  meta_cycle: int,
  meta_cycle_position: int,
  meta_period_index: int,
  period_kind: string
});

type tezosAccount = Js.t({
  . accountId: string,
  blockId: string,
  manager: string,
  spendable: bool,
  delegateSetable: bool,
  delegateValue: string,
  counter: int,
  script: string,
  balance: int
});

type tezosOperation = Js.t({
    . kind: string,
    source: string,
    amount: string,
    destination: string,
    manager_pubkey: string,
    balance: string,
    delegate: string,
    operationGroupHash: string,
    operationId: int,
    fee: string,
    storageLimit: string,
    gasLimit: string,
    blockHash: string,
    timestamp: int,
    blockLevel: int
});

type tezosOperationGroup = Js.t({
  . protocol: string,
  chainId: string,
  hash: string,
  branch: string,
  signature: string,
  blockId: string
});

type operationKindType = | SeedNonceRevelation | Delegation | Transaction | AccountActivation | Origination | Reveal | Endorsement | Ballot;
let operationKindTypeToString = operationKindType : string =>
  switch (operationKindType) {
  | SeedNonceRevelation => "seed_nonce_revelation"
  | Delegation => "delegation"
  | Transaction => "transaction"
  | AccountActivation => "activate_account"
  | Origination => "origination"
  | Reveal => "reveal"
  | Endorsement => "endorsement"
  | Ballot => "ballot"
  };

type tezosBlockHead = Js.t({
  . active_proposal: string,
  baker: string,
  chain_id: string,
  consumed_gas: int,
  context: string,
  hash: string,
  level: int,
  meta_cycle: int,
  meta_cycle_position: int,
  meta_level: int,
  meta_level_position: int,
  meta_voting_period: int,
  meta_voting_period_position: int,
  operations_hash: string,
  period_kind: string,
  predecessor: string,
  proto: string,
  protocol: string,
  signature: string,
  timestamp: int
});

type entityQuery = Js.t({
  . entity: string,
  query: conseilQuery
});

type tezosConseilClient = {
  . [@bs.meth] "getTezosEntityData": (conseilServerInfo, string, string, conseilQuery) => Js.Promise.t(array(string)),
  [@bs.meth] "getBlock": (conseilServerInfo, string, string) => Js.Promise.t(tezosBlock),
  [@bs.meth] "getBlockHead": (conseilServerInfo, string) => Js.Promise.t(tezosBlockHead),
  [@bs.meth] "getBlockByLevel": (conseilServerInfo, string, int) => Js.Promise.t(array(tezosBlock)),
  [@bs.meth] "getAccount": (conseilServerInfo, string, string) => Js.Promise.t(tezosAccount),
  [@bs.meth] "getOperationGroup": (conseilServerInfo, string, string) => Js.Promise.t(tezosOperationGroup),
  [@bs.meth] "getBlocks": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosBlock)),
  [@bs.meth] "getAccounts": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosAccount)),
  [@bs.meth] "getOperationGroups": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosAccount)),
  [@bs.meth] "getOperations": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosOperation)),
  [@bs.meth] "getFeeStatistics": (conseilServerInfo, string, string) => Js.Promise.t(array(string)),
  [@bs.meth] "getProposals": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(string)),
  [@bs.meth] "getBakers": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosAccount)),
  [@bs.meth] "getBallots": (conseilServerInfo, string, conseilQuery) => Js.Promise.t(array(tezosAccount)),
  [@bs.meth] "awaitOperationConfirmation": (conseilServerInfo, string, string, int) => Js.Promise.t(array(tezosOperation)),
  [@bs.meth] "awaitOperationForkConfirmation": (conseilServerInfo, string, string, int, int) => Js.Promise.t(array(tezosOperation))
};

type codeEnvelope = Js.t({
  . code: string,
  consumed: int
});

type tezosLanguageUtil = {
  . [@bs.meth] "hexToMicheline": (string) => codeEnvelope,
  [@bs.meth] "translateMichelsonToMicheline": (string) => string,
  [@bs.meth] "translateMichelsonToHex": (string) => string,
  [@bs.meth] "translateMichelineToHex": (string) => string,
  [@bs.meth] "preProcessMichelsonScript": (string) => array(string),
  [@bs.meth] "normalizeMichelineWhiteSpace": (string) => string,
};

type intType = Js.t({
  . value: int,
  length: int
});

type signedOperationGroup = Js.t({
  . bytes: Buffer.t,
  signature: string
});

type tezosMessageUtils = {
  . [@bs.meth] "writeBoolean": (bool) => string,
  [@bs.meth] "readBoolean": (string) => bool,
  [@bs.meth] "writeInt": (int) => string,
  [@bs.meth] "writeSignedInt": (int) => string,
  [@bs.meth] "readInt": (string) => int,
  [@bs.meth] "readSignedInt": (string) => int,
  [@bs.meth] "findInt": (string, int, bool) => intType,
  [@bs.meth] "readAddress": (string) => string,
  [@bs.meth] "readAddressWithHint": (Buffer.t, string) => string,
  [@bs.meth] "writeAddress": (string) => string,
  [@bs.meth] "readBranch": (string) => string,
  [@bs.meth] "writeBranch": (string) => string,
  [@bs.meth] "readPublicKey": (string) => string,
  [@bs.meth] "writePublicKey": (string) => string,
  [@bs.meth] "readKeyWithHint": (Buffer.t, string) => string,
  [@bs.meth] "writeKeyWithHint": (string, string) => Buffer.t,
  [@bs.meth] "readSignatureWithHint": (Buffer.t, string) => string,
  [@bs.meth] "readBufferWithHint": (Buffer.t, string) => string,
  [@bs.meth] "writeBufferWithHint": (string) => Buffer.t,
  [@bs.meth] "computeOperationHash": (signedOperationGroup) => string,
  [@bs.meth] "computeKeyHash": (Buffer.t, string) => string
};

type contractDelegate = Js.t({
  . setable: bool,
  value: string
});

type contract = Js.t({
  . manager: string,
  balance: string,
  spendable: bool,
  delegate: contractDelegate,
  script: string,
  counter: string
});

type managerKey = Js.t({
  . manager: string,
  key: string
});

type tezosNodeReader = {
  . [@bs.meth] "getBlock": (string, string) => Js.Promise.t(tezosBlock),
  [@bs.meth] "getBlockHead": (string) => Js.Promise.t(tezosBlock),
  [@bs.meth] "getAccountForBlock": (string, string, string) => Js.Promise.t(contract),
  [@bs.meth] "getCounterForAccount": (string, string) => Js.Promise.t(int),
  [@bs.meth] "getSpendableBalanceForAccount": (string, string, string) => Js.Promise.t(int),
  [@bs.meth] "getAccountManagerForBlock": (string, string, string) => Js.Promise.t(managerKey),
  [@bs.meth] "isImplicitAndEmpty": (string, string) => Js.Promise.t(bool),
  [@bs.meth] "isManagerKeyRevealedForAccount": (string, string) => Js.Promise.t(bool),
  [@bs.meth] "getValueForBigMapKey": (string, int, string, string, string) => Js.Promise.t(bool)
};

type storeType = | Mnemonic | Fundraiser | Hardware;
let storeTypeToInt = storeType: int => 
  switch (storeType) {
    | Mnemonic => 0
    | Fundraiser => 1
    | Hardware => 2
  };

type keyStore = Js.t({
  . publicKey: string,
  privateKey: string,
  publicKeyHash: string,
  seed: string,
  storeType: storeType
});

type operation = Js.t({
  . kind: string,
  source: string,
  fee: string,
  counter: string,
  gas_limit: string,
  storage_limit: string,
  manager_pubkey: string,
  balance: string,
  spendable: bool,
  delegatable: bool,
  delegate: string,
  script: string,
  parameters: string
});

type testContractOperation = Js.t({
  . gas: int,
  storageCost: int  
});

type tezosNodeWriter = {
  . [@bs.meth] "signOperationGroup": (string, keyStore, string) => Js.Promise.t(signedOperationGroup),
  [@bs.meth] "forgeOperations": (string, array(operation)) => string,
  [@bs.meth] "forgeOperationsRemotely": (string, tezosBlock, array(operation)) => Js.Promise.t(string),
  [@bs.meth] "preapplyOperation": (string, string, string, array(operation), signedOperationGroup, string) => Js.Promise.t(TezosType.alphaOperationsWithMetadata),
  [@bs.meth] "applyOperation": (string, string, string, array(operation), signedOperationGroup) => Js.Promise.t(TezosType.alphaOperationsWithMetadata),
  [@bs.meth] "injectOperation": (string, signedOperationGroup) => Js.Promise.t(string),
  [@bs.meth] "sendOperation": (string, array(operation), keyStore, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "getQueueStatus": (string, keyStore, string) => int,
  [@bs.meth] "appendRevealOperation": (string, keyStore, string, int, array(operation)) => Js.Promise.t(array(operation)),
  [@bs.meth] "sendTransactionOperation": (string, keyStore, string, int, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendDelegationOperation": (string, keyStore, string, string, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendUndelegationOperation": (string, keyStore, string, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendContractOriginationOperation": (string, keyStore, int, string, bool, bool, int, string, int, int, string, string, string) =>
    Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendContractInvocationOperation": (string, keyStore, string, int, int, string, int, int, string, string) =>
    Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendContractPing": (string, keyStore, string, int, string, int, int) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendKeyRevealOperation": (string, keyStore, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendIdentityActivationOperation": (string, keyStore, string, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "testContractInvocationOperation": (string, string, keyStore, string, int, int, string, int, int, string, string, string) =>
    Js.Promise.t(testContractOperation),
};

type tezosProtocolHelper = {
  . [@bs.meth] "verifyDestination": (string, string) => Js.Promise.t(bool),
  [@bs.meth] "setDelegate": (string, keyStore, string, string, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "unSetDelegate": (string, keyStore, string, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "withdrawDelegatedFunds": (string, keyStore, string, int, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "sendDelegatedFunds": (string, keyStore, string, int, int, string, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "depositDelegatedFunds": (string, keyStore, string, int, int, string) => Js.Promise.t(TezosType.operationResult),
  [@bs.meth] "deployManagerContract": (string, keyStore, string, int, int, string) => Js.Promise.t(TezosType.operationResult),
};

type tezosWalletUtil = {
  . [@bs.meth] "unlockFundraiserIdentity": (string, string, string, string) => Js.Promise.t(keyStore),
  [@bs.meth] "restoreIdentityWithSecretKey": (string) => Js.Promise.t(keyStore),
  [@bs.meth] "generateMnemonic": (int) => string,
  [@bs.meth] "unlockIdentityWithMnemonic": (string, string) => Js.Promise.t(keyStore),
  [@bs.meth] "getKeysFromMnemonicAndPassphrase": (string, string, int, string) => Js.Promise.t(keyStore)
};

type wallet = Js.t({
  .identities: array(keyStore)
});

type tezosFileWallet = {
  . [@bs.meth] "saveWallet": (string, wallet, string) => Js.Promise.t(wallet),
  [@bs.meth] "loadWallet": (string, string) => Js.Promise.t(wallet),
  [@bs.meth] "createWallet": (string, string) => Js.Promise.t(wallet)
};

type executeQuery = Js.t({
  . hash: string
});

type conseilDataClient = {
  . [@bs.meth] "executeEntityQuery": (conseilServerInfo, string, string, string, conseilQuery) => Js.Promise.t(array(executeQuery))
};

type platformDefinition = Js.t({
  . name: string,
  displayName: string
});

type networkDefinition = Js.t({
  . name: string,
  displayName: string,
  platform: string,
  network: string
});

type entityDefinition = Js.t({
  . name: string,
  displayName: string,
  displayNamePlural: string,
  count: int,
  network: string
});

type attributeReference = Js.t({
  . entity: string,
  key: string
});

type attrbuteDataType =  | STRING  | INT  | DECIMAL  | BOOLEAN  | ACCOUNT_ADDRESS | HASH | DATETIME  | CURRENCY;
let attrbuteDataTypeToString = attrbuteDataType : string =>
  switch (attrbuteDataType) {
  | STRING => "String"
  | INT => "Int"
  | DECIMAL => "Decimal"
  | BOOLEAN => "Boolean"
  | ACCOUNT_ADDRESS => "AccountAddress"
  | HASH => "Hash"
  | DATETIME => "DateTime"
  | CURRENCY => "Currency"
  };
type attrbuteKeyType =  | PRIMARYKEY  | UNIQUEKEY  | NONKEY;
let attrbuteKeyTypeToString = attrbuteKeyType : string =>
  switch (attrbuteKeyType) {
  | PRIMARYKEY => "PrimaryKey"
  | UNIQUEKEY => "UniqueKey"
  | NONKEY => "NonKey"
  };

type attributeDefinition = Js.t({
  . name: string,
  displayName: string,
  dataType: attrbuteDataType,
  cardinality: int,
  keyType: attrbuteKeyType,
  entity: string,
  dataFormat: string,
  visible: bool,
  scale: int,
  description: string,
  placeholder: string,
  reference: attributeReference,
  displayOrder: int,
  displayPriority: int,
  currencySymbol: string,
  currencySymbolCode: int
});

type conseilMetadataClient = {
  . [@bs.meth] "executeMetadataQuery": (conseilServerInfo, string) => Js.Promise.t(array(string)),
  [@bs.meth] "getPlatforms": (conseilServerInfo) => Js.Promise.t(array(platformDefinition)),
  [@bs.meth] "getNetworks": (conseilServerInfo, string) => Js.Promise.t(array(networkDefinition)),
  [@bs.meth] "getEntities": (conseilServerInfo, string, string) => Js.Promise.t(array(entityDefinition)),
  [@bs.meth] "getAttributes": (conseilServerInfo, string, string, string) => Js.Promise.t(array(attributeDefinition)),
  [@bs.meth] "getAttributeValues": (conseilServerInfo, string, string, string, string) => Js.Promise.t(array(string)),
  [@bs.meth] "getAttributeValuesForPrefix": (conseilServerInfo, string, string, string, string, string) => Js.Promise.t(array(string)),
};
