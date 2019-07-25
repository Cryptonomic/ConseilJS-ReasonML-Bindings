type alphaOperationResult = Js.t({
  . status: string,
  originated_contracts: array(string),
  errors: array(string)
});

type alphaOperationContentsAndResult = Js.t({
  . kind: string,
  metadata: alphaOperationResult
});

type alphaOperationsWithMetadata = Js.t({
  . contents: array(alphaOperationContentsAndResult),
  signature: string,
  kind: string, //only if error
  id: string, //only if error
  contract: string //only if error
});

type operationResult = Js.t({
  . results: alphaOperationsWithMetadata,
  operationGroupID: string
});

type tezosParameterFormat = | Michelson | Micheline;
let tezosParameterFormatToString = tezosParameterFormat: string => 
  switch (tezosParameterFormat) {
    | Michelson => "michelson"
    | Micheline => "micheline"
  };