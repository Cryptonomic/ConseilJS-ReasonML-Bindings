open ConseiljsType;
[@bs.module "conseiljs"] external tezosContractIntrospector: tezosContractIntrospector = "TezosContractIntrospector";
[@bs.module "conseiljs"] external conseilQueryBuilder: conseilQueryBuilder = "ConseilQueryBuilder";
[@bs.module "conseiljs"] external tezosConseilClient: tezosConseilClient = "TezosConseilClient";
[@bs.module "conseiljs"] external tezosLanguageUtil: tezosLanguageUtil = "TezosLanguageUtil";
[@bs.module "conseiljs"] external tezosMessageUtils: tezosMessageUtils = "TezosMessageUtils";
[@bs.module "conseiljs"] external tezosNodeReader: tezosNodeReader = "TezosNodeReader";
[@bs.module "conseiljs"] external tezosNodeWriter: tezosNodeWriter = "TezosNodeWriter";
[@bs.module "conseiljs"] external tezosProtocolHelper: tezosProtocolHelper = "TezosProtocolHelper";
[@bs.module "conseiljs"] external tezosWalletUtil: tezosWalletUtil = "TezosWalletUtil";
[@bs.module "conseiljs"] external tezosFileWallet: tezosFileWallet = "TezosFileWallet";
[@bs.module "conseiljs"] external conseilDataClient: conseilDataClient = "ConseilDataClient";
[@bs.module "conseiljs"] external conseilMetadataClient: conseilMetadataClient = "ConseilMetadataClient";

module TezosContractIntrospector = {
  let generateEntryPointsFromParams = (params: string) => tezosContractIntrospector##generateEntryPointsFromParams(params);
  let generateEntryPointsFromCode = (contractCode: string) => tezosContractIntrospector##generateEntryPointsFromCode(contractCode);
  let generateEntryPointsFromAddress = (conseilServer: conseilServerInfo, network: string, contractAddress: string) => 
    tezosContractIntrospector##generateEntryPointsFromAddress(conseilServer, network, contractAddress);
};

module ConseilQueryBuilder = {
  let blankQuery = () => conseilQueryBuilder##blankQuery();
  let addPredicate = (query: conseilQuery, field: string, operation: conseilOperator, values: array(string), invert: bool ) =>
    conseilQueryBuilder##addPredicate(query, field, operation |> operatorToString, values, invert);
  let addField = (query: conseilQuery, field: string) => conseilQueryBuilder##addFields(query, field);
  let rec addFields = (query: conseilQuery, fields: list(string)) => 
    switch fields {
    | [] => query
    | [field, ...tail] =>  {
        let query = addField(query, field);
        addFields(query, tail);
      }
    };
  let addOrdering = (query: conseilQuery, field: string, direction: conseilSortDirection) =>
    conseilQueryBuilder##addOrdering(query, field, direction |> sortDirectionToString);
  let setLimit = (query: conseilQuery, limit: int) => conseilQueryBuilder##setLimit(query, limit);
  let setOutputType = (query: conseilQuery, outputType: conseilOutput) =>
    conseilQueryBuilder##setOutputType(query, outputType |> outputToString);
  let addAggregationFunction = (query: conseilQuery, field: string, func: conseilFunction) =>
    conseilQueryBuilder##addAggregationFunction(query, field,  func |> functionToString);
};

module TezosConseilClient = {
  let getTezosEntityData = (serverInfo: conseilServerInfo, network: string, entity: string, query: conseilQuery) =>
    tezosConseilClient##getTezosEntityData(serverInfo, network, entity, query);
  let getBlock = (serverInfo: conseilServerInfo, network: string, hash: string) => tezosConseilClient##getBlock(serverInfo, network, hash);
  let getBlockHead = (serverInfo: conseilServerInfo, network: string) => tezosConseilClient##getBlockHead(serverInfo, network);
  let getBlockByLevel = (serverInfo: conseilServerInfo, network: string, level: int) =>
    tezosConseilClient##getBlockByLevel(serverInfo, network, level);
  let getAccount = (serverInfo: conseilServerInfo, network: string, id: string) =>
    tezosConseilClient##getAccount(serverInfo, network, id);
  let getOperationGroup = (serverInfo: conseilServerInfo, network: string, id: string) =>
    tezosConseilClient##getOperationGroup(serverInfo, network, id);
  let getBlocks = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getBlocks(serverInfo, network, query);
  let getAccounts = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getAccounts(serverInfo, network, query);
  let getOperationGroups = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getOperationGroups(serverInfo, network, query);
  let getOperations = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getOperations(serverInfo, network, query);
  let getFeeStatistics = (serverInfo: conseilServerInfo, network: string, operationType: operationKindType) =>
    tezosConseilClient##getFeeStatistics(serverInfo, network, operationType |> operationKindTypeToString);
  let getProposals = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getProposals(serverInfo, network, query);
  let getBakers = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getBakers(serverInfo, network, query);
  let getBallots = (serverInfo: conseilServerInfo, network: string, query: conseilQuery) =>
    tezosConseilClient##getBallots(serverInfo, network, query);
  let awaitOperationConfirmation = (serverInfo: conseilServerInfo, network: string, hash: string, duration: int) =>
    tezosConseilClient##awaitOperationConfirmation(serverInfo, network, hash, duration);
  let awaitOperationForkConfirmation = (serverInfo: conseilServerInfo, network: string, hash: string, duration: int, depth: int) =>
    tezosConseilClient##awaitOperationForkConfirmation(serverInfo, network, hash, duration, depth);
  [@bs.val] [@bs.scope ("Conseiljs", "TezosConseilClient")] external getEntityQueryForIdByNumber : int => entityQuery = "getEntityQueryForId";
  [@bs.val] [@bs.scope ("Conseiljs", "TezosConseilClient")] external getEntityQueryForIdByString : string => entityQuery = "getEntityQueryForId";
  let getEntityQueryForId = (id: string) => {
    let isNumber = switch (int_of_string(id)) {
      | exception _ => false
      | _ => true
    };
    switch isNumber {
    | true => getEntityQueryForIdByNumber(int_of_string(id))
    | false => getEntityQueryForIdByString(id)
    };
  };
};

module TezosLanguageUtil = {
  let hexToMicheline = (hex: string) => tezosLanguageUtil##hexToMicheline(hex);
  let translateMichelsonToMicheline = (code: string) => tezosLanguageUtil##translateMichelsonToMicheline(code);
  let translateMichelsonToHex = (code: string) => tezosLanguageUtil##translateMichelsonToHex(code);
  let translateMichelineToHex = (code: string) => tezosLanguageUtil##translateMichelineToHex(code);
  let preProcessMichelsonScript = (code: string) => tezosLanguageUtil##preProcessMichelsonScript(code);
  let normalizeMichelineWhiteSpace = (fragment: string) => tezosLanguageUtil##normalizeMichelineWhiteSpace(fragment);
};

module TezosMessageUtils = {
  let writeBoolean = (value: bool) => tezosMessageUtils##writeBoolean(value);
  let readBoolean = (hex: string) => tezosMessageUtils##readBoolean(hex);
  let writeInt = (value: int) => tezosMessageUtils##writeInt(value);
  let writeSignedInt = (value: int) => tezosMessageUtils##writeSignedInt(value);
  let readInt = (hex: string) => tezosMessageUtils##readInt(hex);
  let readSignedInt = (hex: string) => tezosMessageUtils##readSignedInt(hex);
  let findInt = (hex: string, offset: int, signed: bool) => tezosMessageUtils##findInt(hex, offset, signed);
  let readAddress = (hex: string) => tezosMessageUtils##readAddress(hex);
  let readAddressWithHint = (b: Buffer.t, hex: string) => tezosMessageUtils##readAddressWithHint(b, hex);
  let writeAddress = (address: string) => tezosMessageUtils##writeAddress(address);
  let readBranch = (hex: string) => tezosMessageUtils##readBranch(hex);
  let writeBranch = (branch: string) => tezosMessageUtils##writeBranch(branch);
  let readPublicKey = (hex: string) => tezosMessageUtils##readPublicKey(hex);
  let writePublicKey = (publicKey: string) => tezosMessageUtils##writePublicKey(publicKey);
  let readKeyWithHint = (b: Buffer.t, hint: string) => tezosMessageUtils##readKeyWithHint(b, hint);
  let writeKeyWithHint = (key: string, hint: string) => tezosMessageUtils##writeKeyWithHint(key, hint);
  let readSignatureWithHint = (b: Buffer.t, hint: string) => tezosMessageUtils##readSignatureWithHint(b, hint);
  let readBufferWithHint = (b: Buffer.t, hint: string) => tezosMessageUtils##readBufferWithHint(b, hint);
  let writeBufferWithHint = (b: string) => tezosMessageUtils##writeBufferWithHint(b);
  let computeOperationHash = (signedOpGroup: signedOperationGroup) => tezosMessageUtils##computeOperationHash(signedOpGroup);
  let computeKeyHash = (key: Buffer.t, prefix: string) => tezosMessageUtils##computeKeyHash(key, prefix);
};

module TezosNodeReader = {
  let getBlock = (server: string, hash: string) => tezosNodeReader##getBlock(server, hash);
  let getBlockHead = (server: string) => tezosNodeReader##getBlockHead(server);
  let getAccountForBlock = (server: string, blockHash: string, accountHash: string) =>
    tezosNodeReader##getAccountForBlock(server, blockHash, accountHash);
  let getCounterForAccount = (server: string, accountHash: string) => tezosNodeReader##getCounterForAccount(server, accountHash);
  let getSpendableBalanceForAccount = (server: string, accountHash: string, chainid: string) =>
    tezosNodeReader##getSpendableBalanceForAccount(server, accountHash, chainid);
  let getAccountManagerForBlock = (server: string, blockHash: string, accountHash: string) =>
    tezosNodeReader##getAccountManagerForBlock(server, blockHash, accountHash);
  let isImplicitAndEmpty = (server: string, accountHash: string) => tezosNodeReader##isImplicitAndEmpty(server, accountHash);
  let isManagerKeyRevealedForAccount = (server: string, accountHash: string) =>
    tezosNodeReader##isManagerKeyRevealedForAccount(server, accountHash);
  let getValueForBigMapKey = (server: string, index: int, key: string, block: string, chainid: string) =>
    tezosNodeReader##getValueForBigMapKey(server, index, key, block, chainid);
};

module TezosNodeWriter = {
  let signOperationGroup = (forgedOperation: string, keyStore: keyStore, derivationPath: string) =>
    tezosNodeWriter##signOperationGroup(forgedOperation, keyStore, derivationPath);
  let forgeOperations = (branch: string, operations: array(operation)) => tezosNodeWriter##forgeOperations(branch, operations);
  let forgeOperationsRemotely = (server: string, blockHead: tezosBlock, operations: array(operation)) =>
    tezosNodeWriter##forgeOperationsRemotely(server, blockHead, operations);
  let preapplyOperation = (server: string, branch: string, protocol: string, operations: array(operation), signedOpGroup: signedOperationGroup, chainid: string) =>
    tezosNodeWriter##preapplyOperation(server, branch, protocol, operations, signedOpGroup, chainid);
  let applyOperation = (server: string, branch: string, protocol: string, operations: array(operation), signedOpGroup: signedOperationGroup) =>
    tezosNodeWriter##applyOperation(server, branch, protocol, operations, signedOpGroup);
  let injectOperation = (server: string, signedOpGroup: signedOperationGroup) => tezosNodeWriter##injectOperation(server, signedOpGroup);
  let getQueueStatus = (server: string, keyStore: keyStore, path: string) =>
    tezosNodeWriter##getQueueStatus(server, keyStore, path);
  let sendOperation = (server: string, operations: array(operation), keyStore: keyStore, path: string) =>
    tezosNodeWriter##sendOperation(server, operations, keyStore, path);
  let appendRevealOperation = (server: string, keyStore: keyStore, accountHash: string, index: int, operations: array(operation)) =>
    tezosNodeWriter##appendRevealOperation(server, keyStore, accountHash, index, operations);
  let sendTransactionOperation = (server: string, keyStore: keyStore, _to: string, amount: int, fee: int, path: string) =>
    tezosNodeWriter##sendTransactionOperation(server, keyStore, _to, amount, fee, path);
  let sendDelegationOperation = (server: string, keyStore: keyStore, delegator: string, delegate: string, fee: int, path: string) =>
    tezosNodeWriter##sendDelegationOperation(server, keyStore, delegator, delegate, fee, path);
  let sendUndelegationOperation = (server: string, keyStore: keyStore, delegator: string, fee: int, path: string) =>
    tezosNodeWriter##sendUndelegationOperation(server, keyStore, delegator, fee, path);
  let sendContractOriginationOperation = (
      server: string, keyStore: keyStore, amount: int, delegate: string, spendable: bool, delegatable: bool,
      fee: int, path: string, storage_limit: int, gas_limit: int, code: string, storage: string, codeFormat: TezosType.tezosParameterFormat
    ) =>
    tezosNodeWriter##sendContractOriginationOperation(server, keyStore, amount, delegate, spendable, delegatable, fee, path,
      storage_limit, gas_limit, code, storage, codeFormat |> TezosType.tezosParameterFormatToString);
  let sendContractInvocationOperation = (
      server: string, keyStore: keyStore, _to: string, amount: int,
      fee: int, path: string, storage_limit: int, gas_limit: int, parameters: string, codeFormat: TezosType.tezosParameterFormat
    ) =>
    tezosNodeWriter##sendContractInvocationOperation(server, keyStore, _to, amount, fee, path,
      storage_limit, gas_limit, parameters, codeFormat |> TezosType.tezosParameterFormatToString);
  let sendContractPing = (server: string, keyStore: keyStore, _to: string, fee: int, path: string, storage_limit: int, gas_limit: int) =>
    tezosNodeWriter##sendContractPing(server, keyStore, _to, fee, path, storage_limit, gas_limit);
  let sendKeyRevealOperation = (server: string, keyStore: keyStore, fee: int, path: string) =>
    tezosNodeWriter##sendKeyRevealOperation(server, keyStore, fee, path);
  let sendIdentityActivationOperation = (server: string, keyStore: keyStore, code: string, path: string) =>
    tezosNodeWriter##sendIdentityActivationOperation(server, keyStore, code, path);
  let testContractInvocationOperation = (
    server: string, chainid: string, keyStore: keyStore, _to: string, amount: int, fee: int, path: string,
    storageLimit: int, gasLimit: int, entryPoint: string, parameters: string, parameterFormat: string
  ) =>
    tezosNodeWriter##testContractInvocationOperation(
      server, chainid, keyStore, _to, amount, fee, path, storageLimit, gasLimit, entryPoint, parameters, parameterFormat
    );
};

module TezosProtocolHelper = {
  let verifyDestination = (server: string, address: string) => tezosProtocolHelper##verifyDestination(server, address);
  let setDelegate = (server: string, keyStore: keyStore, contract: string, delegate: string, fee: int, path: string) => 
    tezosProtocolHelper##setDelegate(server, keyStore, contract, delegate, fee, path);
  let unSetDelegate = (server: string, keyStore: keyStore, contract: string, fee: int, path: string) => 
    tezosProtocolHelper##unSetDelegate(server, keyStore, contract, fee, path);
  let withdrawDelegatedFunds = (server: string, keyStore: keyStore, contract: string, fee: int, amount: int, path: string) => 
    tezosProtocolHelper##withdrawDelegatedFunds(server, keyStore, contract, fee, amount, path);
  let sendDelegatedFunds = (server: string, keyStore: keyStore, contract: string, fee: int, amount: int, path: string, destination: string) => 
    tezosProtocolHelper##sendDelegatedFunds(server, keyStore, contract, fee, amount, path, destination);
  let depositDelegatedFunds = (server: string, keyStore: keyStore, contract: string, fee: int, amount: int, path: string) => 
    tezosProtocolHelper##depositDelegatedFunds(server, keyStore, contract, fee, amount, path);
  let deployManagerContract = (server: string, keyStore: keyStore, contract: string, fee: int, amount: int, path: string) => 
    tezosProtocolHelper##deployManagerContract(server, keyStore, contract, fee, amount, path);
}

module TezosWalletUtil = {
  let unlockFundraiserIdentity = (mnemonic: string, email: string, password: string, pkh: string) =>
    tezosWalletUtil##unlockFundraiserIdentity(mnemonic, email, password, pkh);
  let restoreIdentityWithSecretKey = (keyString: string) => tezosWalletUtil##restoreIdentityWithSecretKey(keyString);
  let generateMnemonic = (strength: int) => tezosWalletUtil##generateMnemonic(strength);
  let unlockIdentityWithMnemonic = (mnemonic: string, passphrase: string) => tezosWalletUtil##unlockIdentityWithMnemonic(mnemonic, passphrase);
  let getKeysFromMnemonicAndPassphrase = (mnemonic: string, passphrase: string, storeType: storeType, pkh: string) =>
    tezosWalletUtil##getKeysFromMnemonicAndPassphrase(mnemonic, passphrase, storeType |> storeTypeToInt, pkh);
};
module TezosFileWallet = {
  let saveWallet = (filename: string, wallet: wallet, passphrase: string) => tezosFileWallet##saveWallet(filename, wallet, passphrase);
  let loadWallet = (filename: string, passphrase: string) => tezosFileWallet##loadWallet(filename, passphrase);
  let createWallet = (filename: string, passphrase: string) => tezosFileWallet##createWallet(filename, passphrase);
};

module ConseilDataClient = {
  let executeEntityQuery = (serverInfo: conseilServerInfo, platform: string, network: string, entity: string, query: conseilQuery) =>
    conseilDataClient##executeEntityQuery(serverInfo, platform, network, entity, query);
};

module ConseilMetadataClient = {
  let executeMetadataQuery = (serverInfo: conseilServerInfo, route: string) =>
    conseilMetadataClient##executeMetadataQuery(serverInfo, route);
  let getPlatforms = (serverInfo: conseilServerInfo) => conseilMetadataClient##getPlatforms(serverInfo);
  let getNetworks = (serverInfo: conseilServerInfo, platform: string) => conseilMetadataClient##getNetworks(serverInfo, platform);
  let getEntities = (serverInfo: conseilServerInfo, platform: string, network: string) =>
    conseilMetadataClient##getEntities(serverInfo, platform, network);
  let getAttributes = (serverInfo: conseilServerInfo, platform: string, network: string, entity: string) =>
    conseilMetadataClient##getAttributes(serverInfo, platform, network, entity);
  let getAttributeValues = (serverInfo: conseilServerInfo, platform: string, network: string, entity: string, attribute: string) =>
    conseilMetadataClient##getAttributeValues(serverInfo, platform, network, entity, attribute);
  let getAttributeValuesForPrefix = (serverInfo: conseilServerInfo, platform: string, network: string, entity: string, attribute: string, prefix: string) =>
    conseilMetadataClient##getAttributeValuesForPrefix(serverInfo, platform, network, entity, attribute, prefix);
};
