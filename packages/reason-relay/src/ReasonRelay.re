let toOpt = Js.Nullable.toOption;
type jsObj('a) = Js.t({..} as 'a);

type any;

type queryNode;
type fragmentNode;
type mutationNode;
type subscriptionNode;

type dataId;

external _dataIdToString: dataId => string = "%identity";
let dataIdToString = dataId => _dataIdToString(dataId);

external _makeDataId: string => dataId = "%identity";
let makeDataId = string => _makeDataId(string);

/**
 * Various helpers.
 */

// We occasionally have to remove undefined keys from objects, something I haven't figured out how to do with pure BuckleScript
let cleanObjectFromUndefined = [%bs.raw
  {|
  function cleanObj(obj) {
    var newObj = {};

    Object.keys(obj).forEach(function(key) {
      if (typeof obj[key] !== 'undefined') {
        newObj[key] = obj[key];
      }
    });

    return newObj;
  }
|}
];

// Since BS compiles unit to 0, we have to convert that to an empty object when dealing with variables in order for Relay to be happy
let cleanVariables = [%bs.raw
  {|
  function cleanVariables(variables) {
    if (typeof variables !== "object" || variables == null) {
      return {};
    }

    return variables;
  }
|}
];

module ReactSuspenseConfig = {
  type t = {
    .
    "timeOutMs": float,
    "busyDelayMs": option(float),
    "busyMinDurationMs": option(float),
  };

  let make = (~timeOutMs, ~busyDelayMs=?, ~busyMinDurationMs=?, ()) => {
    "timeOutMs": timeOutMs,
    "busyDelayMs": busyDelayMs,
    "busyMinDurationMs": busyMinDurationMs,
  };
};

[@bs.module "react"]
external unstable_withSuspenseConfig:
  (
    unit => unit,
    {
      .
      "timeOutMs": float,
      "busyDelayMs": option(float),
      "busyMinDurationMs": option(float),
    }
  ) =>
  unit =
  "unstable_withSuspenseConfig";

[@bs.module "relay-runtime"] external storeRootId: dataId = "ROOT_ID";
[@bs.module "relay-runtime"] external storeRootType: string = "ROOT_TYPE";

module RecordProxy = {
  type t;
  type arguments('a) = jsObj('a);

  [@bs.send] external _copyFieldsFrom: (t, t) => unit = "copyFieldsFrom";
  let copyFieldsFrom = (t, ~sourceRecord: t) =>
    _copyFieldsFrom(t, sourceRecord);

  [@bs.send] external _getDataID: t => dataId = "getDataID";
  let getDataId = t => _getDataID(t);

  [@bs.send]
  external _getLinkedRecord:
    (t, string, option(arguments('a))) => Js.Nullable.t(t) =
    "getLinkedRecord";

  let getLinkedRecord = (t, ~name, ~arguments): option(t) =>
    _getLinkedRecord(t, name, arguments) |> toOpt;

  [@bs.send]
  external _getLinkedRecords:
    (t, string, option(arguments('a))) =>
    Js.Nullable.t(array(Js.Nullable.t(t))) =
    "getLinkedRecords";

  let getLinkedRecords = (t, ~name, ~arguments): option(array(option(t))) =>
    switch (_getLinkedRecords(t, name, arguments) |> toOpt) {
    | Some(records) => Some(records |> Array.map(v => v |> toOpt))
    | None => None
    };

  [@bs.send]
  external _getOrCreateLinkedRecord:
    (t, string, string, option(arguments('a))) => t =
    "getOrCreateLinkedRecord";

  let getOrCreateLinkedRecord = (t, ~name, ~typeName, ~arguments) =>
    _getOrCreateLinkedRecord(t, name, typeName, arguments);

  [@bs.send] external _getType: t => string = "getType";
  let getType = t => _getType(t);

  [@bs.send]
  external _getValue:
    (t, string, option(arguments('a))) => Js.Nullable.t('value) =
    "getValue";

  let _getValueArr = (t, ~name, ~arguments) =>
    switch (_getValue(t, name, arguments) |> toOpt) {
    | Some(arr) =>
      Some(arr |> Array.map(value => value |> Js.Nullable.toOption))
    | None => None
    };

  let getValueString = (t, ~name, ~arguments): option(string) =>
    _getValue(t, name, arguments) |> toOpt;

  let getValueStringArray =
      (t, ~name, ~arguments): option(array(option(string))) =>
    _getValueArr(~name, ~arguments, t);

  let getValueInt = (t, ~name, ~arguments): option(int) =>
    _getValue(t, name, arguments) |> toOpt;

  let getValueIntArray = (t, ~name, ~arguments): option(array(option(int))) =>
    _getValueArr(~name, ~arguments, t);

  let getValueFloat = (t, ~name, ~arguments): option(float) =>
    _getValue(t, name, arguments) |> toOpt;

  let getValueFloatArray =
      (t, ~name, ~arguments): option(array(option(float))) =>
    _getValueArr(~name, ~arguments, t);

  let getValueBool = (t, ~name, ~arguments): option(bool) =>
    _getValue(t, name, arguments) |> toOpt;

  let getValueBoolArray =
      (t, ~name, ~arguments): option(array(option(bool))) =>
    _getValueArr(~name, ~arguments, t);

  [@bs.send]
  external _setLinkedRecord: (t, t, string, option(arguments('a))) => t =
    "setLinkedRecord";
  let setLinkedRecord = (t, ~record, ~name, ~arguments) =>
    _setLinkedRecord(t, record, name, arguments);

  [@bs.send]
  external _setLinkedRecords:
    (t, array(option(t)), string, option(arguments('a))) => t =
    "setLinkedRecords";
  let setLinkedRecords = (t, ~records, ~name, ~arguments) =>
    _setLinkedRecords(t, records, name, arguments);

  [@bs.send]
  external _setValue: (t, 'value, string, option(arguments('a))) => t =
    "setValue";

  let setValueString = (t, ~value: string, ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueStringArray = (t, ~value: array(string), ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueInt = (t, ~value: int, ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueIntArray = (t, ~value: array(int), ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueFloat = (t, ~value: float, ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueFloatArray = (t, ~value: array(float), ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueBool = (t, ~value: bool, ~name, ~arguments) =>
    _setValue(t, value, name, arguments);

  let setValueBoolArray = (t, ~value: array(bool), ~name, ~arguments) =>
    _setValue(t, value, name, arguments);
};

module RecordSourceSelectorProxy = {
  type t;

  [@bs.send] external _create: (t, dataId, string) => RecordProxy.t = "create";
  let create = (t, ~dataId, ~typeName: string) =>
    _create(t, dataId, typeName);

  [@bs.send] external _delete: (t, dataId) => unit = "delete";
  let delete = (t, ~dataId) => _delete(t, dataId);

  [@bs.send]
  external _get: (t, dataId) => Js.Nullable.t(RecordProxy.t) = "get";
  let get = (t, ~dataId): option(RecordProxy.t) => _get(t, dataId) |> toOpt;

  [@bs.send] external getRoot: t => RecordProxy.t = "getRoot";

  [@bs.send]
  external _getRootField: (t, string) => Js.Nullable.t(RecordProxy.t) =
    "getRootField";
  let getRootField = (t, ~fieldName): option(RecordProxy.t) =>
    _getRootField(t, fieldName) |> toOpt;

  [@bs.send]
  external _getPluralRootField:
    (t, string) => Js.Nullable.t(array(Js.Nullable.t(RecordProxy.t))) =
    "getPluralRootField";

  let getPluralRootField =
      (t, ~fieldName): option(array(option(RecordProxy.t))) =>
    switch (_getPluralRootField(t, fieldName) |> toOpt) {
    | Some(arr) => Some(arr |> Array.map(v => v |> toOpt))
    | None => None
    };
};

module RecordSourceProxy = {
  type t;

  [@bs.send] external _create: (t, dataId, string) => RecordProxy.t = "create";
  let create = (t, ~dataId, ~typeName: string) =>
    _create(t, dataId, typeName);

  [@bs.send] external _delete: (t, dataId) => unit = "delete";
  let delete = (t, ~dataId) => _delete(t, dataId);

  [@bs.send]
  external _get: (t, dataId) => Js.Nullable.t(RecordProxy.t) = "get";
  let get = (t, ~dataId): option(RecordProxy.t) => _get(t, dataId) |> toOpt;

  [@bs.send] external getRoot: t => RecordProxy.t = "getRoot";
};

module ConnectionHandler = {
  type t;

  type filters('a) = jsObj('a);

  [@bs.module "relay-runtime"]
  external connectionHandler: t = "ConnectionHandler";

  [@bs.send]
  external _getConnection:
    (t, RecordProxy.t, string, option({..})) => Js.Nullable.t(RecordProxy.t) =
    "getConnection";

  let getConnection = (~record, ~key, ~filters) =>
    _getConnection(connectionHandler, record, key, filters)
    |> Js.Nullable.toOption;

  [@bs.send]
  external _createEdge:
    (t, RecordSourceSelectorProxy.t, RecordProxy.t, RecordProxy.t, string) =>
    RecordProxy.t =
    "createEdge";

  let createEdge = (~store, ~connection, ~node, ~edgeType) =>
    _createEdge(connectionHandler, store, connection, node, edgeType);

  [@bs.send]
  external _insertEdgeBefore:
    (t, RecordProxy.t, RecordProxy.t, option(string)) => unit =
    "insertEdgeBefore";

  let insertEdgeBefore = (~connection, ~newEdge, ~cursor) =>
    _insertEdgeBefore(connectionHandler, connection, newEdge, cursor);

  [@bs.send]
  external _insertEdgeAfter:
    (t, RecordProxy.t, RecordProxy.t, option(string)) => unit =
    "insertEdgeAfter";

  let insertEdgeAfter = (~connection, ~newEdge, ~cursor) =>
    _insertEdgeAfter(connectionHandler, connection, newEdge, cursor);

  [@bs.send]
  external _deleteNode: (t, RecordProxy.t, dataId) => unit = "deleteNode";

  let deleteNode = (~connection, ~nodeId) =>
    _deleteNode(connectionHandler, connection, nodeId);
};

/**
 * QUERY
 */
module Disposable = {
  type t;

  [@bs.send] external dispose: t => unit = "dispose";
};

module CacheConfig = {
  type t = {
    .
    "force": option(bool),
    "poll": option(int),
    "liveConfigId": option(string),
    "transactionId": option(string),
  };
  type config = {
    force: option(bool),
    poll: option(int),
    liveConfigId: option(string),
    transactionId: option(string),
  };

  let make = (~force, ~poll, ~liveConfigId, ~transactionId) => {
    "force": force,
    "poll": poll,
    "liveConfigId": liveConfigId,
    "transactionId": transactionId,
  };

  let getConfig = t => {
    force: t##force,
    poll: t##poll,
    liveConfigId: t##liveConfigId,
    transactionId: t##transactionId,
  };
};

/**
 * Misc
 */
module Observable = {
  type t;

  type _sink('t) = {
    .
    "next": 't => unit,
    "error": Js.Exn.t => unit,
    "completed": unit => unit,
    "closed": bool,
  };

  type sink('t) = {
    next: 't => unit,
    error: Js.Exn.t => unit,
    completed: unit => unit,
    closed: bool,
  };

  [@bs.module "relay-runtime"] [@bs.scope "Observable"]
  external create: (_sink('t) => option('a)) => t = "create";

  let make = sinkFn =>
    create(s => {
      sinkFn({
        next: s##next,
        error: s##error,
        completed: s##completed,
        closed: s##closed,
      });
      None;
    });
};

module Network = {
  type t;

  type operation = {
    .
    "text": string,
    "name": string,
    "operationKind": string,
  };

  type subscribeFn =
    {
      .
      "request": operation,
      "variables": Js.Json.t,
      "cacheConfig": CacheConfig.t,
    } =>
    Observable.t;

  type fetchFunctionPromise =
    (operation, Js.Json.t, CacheConfig.t) => Js.Promise.t(Js.Json.t);

  type fetchFunctionObservable =
    (operation, Js.Json.t, CacheConfig.t) => Observable.t;

  [@bs.module "relay-runtime"] [@bs.scope "Network"]
  external makeFromPromise: (fetchFunctionPromise, option(subscribeFn)) => t =
    "create";

  let makePromiseBased = (~fetchFunction, ~subscriptionFunction=?, ()) =>
    makeFromPromise(fetchFunction, subscriptionFunction);

  [@bs.module "relay-runtime"] [@bs.scope "Network"]
  external makeFromObservable:
    (fetchFunctionObservable, option(subscribeFn)) => t =
    "create";

  let makeObservableBased = (~observableFunction, ~subscriptionFunction=?, ()) =>
    makeFromObservable(observableFunction, subscriptionFunction);
};

module RecordSource = {
  type t;

  [@bs.module "relay-runtime"] [@bs.new]
  external make: unit => t = "RecordSource";
};

module Store = {
  type t;

  [@bs.module "relay-runtime"] [@bs.new]
  external _make:
    (RecordSource.t, {. "gcReleaseBufferSize": option(int)}) => t =
    "Store";

  let make = (~source, ~gcReleaseBufferSize=?, ()) =>
    _make(source, {"gcReleaseBufferSize": gcReleaseBufferSize});
};

module Environment = {
  type t;

  [@bs.module "relay-runtime"] [@bs.new]
  external _make:
    {
      .
      "network": Network.t,
      "store": Store.t,
      "UNSTABLE_DO_NOT_USE_getDataID": option(('a, string) => string),
    } =>
    t =
    "Environment";

  let make = (~network, ~store, ~getDataID=?, ()) =>
    _make({
      "network": network,
      "store": store,
      "UNSTABLE_DO_NOT_USE_getDataID":
        switch (getDataID) {
        | Some(getDataID) =>
          Some((nodeObj, typeName) => getDataID(~nodeObj, ~typeName))
        | None => None
        },
    });
};

module Context = {
  type t;

  type contextShape = {. "environment": Environment.t};

  [@bs.module "react-relay"]
  external context: React.Context.t(option(contextShape)) =
    "ReactRelayContext";
  let provider = React.Context.provider(context);

  module Provider = {
    [@react.component]
    let make = (~environment: Environment.t, ~children) =>
      React.createElement(
        provider,
        {"value": Some({"environment": environment}), "children": children},
      );
  };
};

exception EnvironmentNotFoundInContext;

let useEnvironmentFromContext = () => {
  let context = React.useContext(Context.context);

  switch (context) {
  | Some(ctx) => ctx##environment
  | None => raise(EnvironmentNotFoundInContext)
  };
};

type fetchPolicy =
  | StoreOnly
  | StoreOrNetwork
  | StoreAndNetwork
  | NetworkOnly;

let mapFetchPolicy = fetchPolicy =>
  switch (fetchPolicy) {
  | Some(StoreOnly) => Some("store-only")
  | Some(StoreOrNetwork) => Some("store-or-network")
  | Some(StoreAndNetwork) => Some("store-and-network")
  | Some(NetworkOnly) => Some("network-only")
  | None => None
  };

[@bs.module "relay-runtime"]
external fetchQuery:
  (Environment.t, queryNode, 'variables) => Js.Promise.t('response) =
  "fetchQuery";

[@bs.module "react-relay/hooks"]
external _useQuery:
  (
    queryNode,
    'variables,
    {
      .
      "fetchKey": option(string),
      "fetchPolicy": option(string),
      "networkCacheConfig": option(CacheConfig.t),
    }
  ) =>
  'queryResponse =
  "useLazyLoadQuery";

[@bs.module "react-relay/hooks"]
external _preloadQuery:
  (
    Environment.t,
    queryNode,
    'variables,
    {
      .
      "fetchKey": option(string),
      "fetchPolicy": option(string),
      "networkCacheConfig": option(CacheConfig.t),
    }
  ) =>
  'queryResponse =
  "preloadQuery";

[@bs.module "react-relay/hooks"]
external _usePreloadedQuery: (queryNode, 'token) => 'queryResponse =
  "usePreloadedQuery";

module type MakeUseQueryConfig = {
  type response;
  type variables;
  let query: queryNode;
};

module MakeUseQuery = (C: MakeUseQueryConfig) => {
  type response = C.response;
  type variables = C.variables;
  type preloadToken;

  let use:
    (
      ~variables: variables,
      ~fetchPolicy: fetchPolicy=?,
      ~fetchKey: string=?,
      ~networkCacheConfig: CacheConfig.t=?,
      unit
    ) =>
    response =
    (~variables, ~fetchPolicy=?, ~fetchKey=?, ~networkCacheConfig=?, ()) =>
      _useQuery(
        C.query,
        variables |> cleanVariables,
        {
          "fetchKey": fetchKey,
          "fetchPolicy": fetchPolicy |> mapFetchPolicy,
          "networkCacheConfig": networkCacheConfig,
        },
      );

  let preload:
    (
      ~environment: Environment.t,
      ~variables: variables,
      ~fetchPolicy: fetchPolicy=?,
      ~fetchKey: string=?,
      ~networkCacheConfig: CacheConfig.t=?,
      unit
    ) =>
    preloadToken =
    (
      ~environment,
      ~variables,
      ~fetchPolicy=?,
      ~fetchKey=?,
      ~networkCacheConfig=?,
      (),
    ) =>
      _preloadQuery(
        environment,
        C.query,
        variables |> cleanVariables,
        {
          "fetchKey": fetchKey,
          "fetchPolicy": fetchPolicy |> mapFetchPolicy,
          "networkCacheConfig": networkCacheConfig,
        },
      );

  let usePreloaded = (token: preloadToken) =>
    _usePreloadedQuery(C.query, token);

  let fetch =
      (~environment: Environment.t, ~variables: C.variables)
      : Js.Promise.t(C.response) =>
    fetchQuery(environment, C.query, variables);
};

/**
 * FRAGMENT
 */
[@bs.module "react-relay/hooks"]
external _useFragment: (fragmentNode, 'fragmentRef) => 'fragmentData =
  "useFragment";

module type MakeUseFragmentConfig = {
  type fragment;
  type fragmentRef;
  let fragmentSpec: fragmentNode;
};

module MakeUseFragment = (C: MakeUseFragmentConfig) => {
  let use = (fr: C.fragmentRef): C.fragment =>
    _useFragment(C.fragmentSpec, fr);
};

/** Refetchable */
type refetchFn('variables) =
  (
    ~variables: 'variables,
    ~fetchPolicy: fetchPolicy=?,
    ~onComplete: option(Js.Exn.t) => unit=?,
    unit
  ) =>
  unit;

type refetchFnRaw('variables) =
  (
    'variables,
    {
      .
      "fetchPolicy": option(string),
      "onComplete": option(Js.Nullable.t(Js.Exn.t) => unit),
    }
  ) =>
  unit;

let makeRefetchableFnOpts = (~fetchPolicy, ~onComplete) => {
  "fetchPolicy": fetchPolicy |> mapFetchPolicy,
  "onComplete":
    Some(
      maybeExn =>
        switch (onComplete, maybeExn |> Js.Nullable.toOption) {
        | (Some(onComplete), maybeExn) => onComplete(maybeExn)
        | _ => ()
        },
    ),
};

[@bs.module "react-relay/hooks"]
external _useRefetchableFragment:
  (fragmentNode, 'fragmentRef) => ('fragmentData, refetchFnRaw('variables)) =
  "useRefetchableFragment";

module type MakeUseRefetchableFragmentConfig = {
  type fragment;
  type fragmentRef;
  type variables;
  let fragmentSpec: fragmentNode;
};

module MakeUseRefetchableFragment = (C: MakeUseRefetchableFragmentConfig) => {
  let useRefetchable = (fr: C.fragmentRef) => {
    let (fragmentData, refetchFn) =
      _useRefetchableFragment(C.fragmentSpec, fr);
    (
      fragmentData,
      (~variables: C.variables, ~fetchPolicy=?, ~onComplete=?, ()) =>
        refetchFn(
          variables |> cleanVariables |> cleanObjectFromUndefined,
          makeRefetchableFnOpts(~fetchPolicy, ~onComplete),
        ),
    );
  };
};

/** Pagination */
module type MakeUsePaginationFragmentConfig = {
  type fragment;
  type variables;
  type fragmentRef;
  let fragmentSpec: fragmentNode;
};

type paginationLoadMoreFn =
  (~count: int, ~onComplete: option(option(Js.Exn.t) => unit)) =>
  Disposable.t;

type paginationBlockingFragmentReturn('fragmentData, 'variables) = {
  data: 'fragmentData,
  loadNext: paginationLoadMoreFn,
  loadPrevious: paginationLoadMoreFn,
  hasNext: bool,
  hasPrevious: bool,
  refetch: refetchFn('variables),
};

type paginationFragmentReturn('fragmentData, 'variables) = {
  data: 'fragmentData,
  loadNext: paginationLoadMoreFn,
  loadPrevious: paginationLoadMoreFn,
  hasNext: bool,
  hasPrevious: bool,
  isLoadingNext: bool,
  isLoadingPrevious: bool,
  refetch: refetchFn('variables),
};

[@bs.module "react-relay/hooks"]
external _usePaginationFragment:
  (fragmentNode, 'fragmentRef) =>
  {
    .
    "data": 'fragmentData,
    "loadNext": paginationLoadMoreFn,
    "loadPrevious": paginationLoadMoreFn,
    "hasNext": bool,
    "hasPrevious": bool,
    "isLoadingNext": bool,
    "isLoadingPrevious": bool,
    "refetch":
      [@bs.meth] (
        (
          'variables,
          {
            .
            "fetchPolicy": option(string),
            "onComplete": option(Js.Nullable.t(Js.Exn.t) => unit),
          }
        ) =>
        unit
      ),
  } =
  "usePaginationFragment";

[@bs.module "react-relay/hooks"]
external _useBlockingPaginationFragment:
  (fragmentNode, 'fragmentRef) =>
  {
    .
    "data": 'fragmentData,
    "loadNext": paginationLoadMoreFn,
    "loadPrevious": paginationLoadMoreFn,
    "hasNext": bool,
    "hasPrevious": bool,
    "isLoadingNext": bool,
    "isLoadingPrevious": bool,
    "refetch":
      [@bs.meth] (
        (
          'variables,
          {
            .
            "fetchPolicy": option(string),
            "onComplete": option(Js.Nullable.t(Js.Exn.t) => unit),
          }
        ) =>
        unit
      ),
  } =
  "useBlockingPaginationFragment";

module MakeUsePaginationFragment = (C: MakeUsePaginationFragmentConfig) => {
  let useBlockingPagination =
      (fr: C.fragmentRef)
      : paginationBlockingFragmentReturn(C.fragment, C.variables) => {
    let p = _useBlockingPaginationFragment(C.fragmentSpec, fr);
    {
      data: p##data,
      loadNext: p##loadNext,
      loadPrevious: p##loadPrevious,
      hasNext: p##hasNext,
      hasPrevious: p##hasPrevious,
      refetch: (~variables: C.variables, ~fetchPolicy=?, ~onComplete=?, ()) =>
        p##refetch(
          variables,
          makeRefetchableFnOpts(~onComplete, ~fetchPolicy),
        ),
    };
  };

  let usePagination =
      (fr: C.fragmentRef): paginationFragmentReturn(C.fragment, C.variables) => {
    let p = _usePaginationFragment(C.fragmentSpec, fr);
    {
      data: p##data,
      loadNext: p##loadNext,
      loadPrevious: p##loadPrevious,
      hasNext: p##hasNext,
      hasPrevious: p##hasPrevious,
      isLoadingNext: p##isLoadingNext,
      isLoadingPrevious: p##isLoadingPrevious,
      refetch: (~variables: C.variables, ~fetchPolicy=?, ~onComplete=?, ()) =>
        p##refetch(
          variables,
          makeRefetchableFnOpts(~onComplete, ~fetchPolicy),
        ),
    };
  };
};

/**
 * MUTATION
 */
module type MutationConfig = {
  type variables;
  type response;
  let node: mutationNode;
};

type updaterFn = RecordSourceSelectorProxy.t => unit;

type mutationConfig('variables, 'response) = {
  .
  "variables": 'variables,
  "optimisticResponse": option('response),
  "updater": option(updaterFn),
  "optimisticUpdater": option(updaterFn),
};

type mutationError = {. "message": string};

type mutationStateRaw('response) = {
  .
  "loading": bool,
  "data": Js.Nullable.t('response),
  "error": Js.Nullable.t(mutationError),
};

type mutateFn('variables, 'response) =
  mutationConfig('variables, 'response) => Js.Promise.t('response);

[@bs.module "relay-hooks"]
external _useMutation:
  mutationNode =>
  (mutateFn('variables, 'response), mutationStateRaw('response)) =
  "useMutation";

type mutationState('response) =
  | Idle
  | Loading
  | Error(array(mutationError))
  | Success(option('response));

type mutationResult('response) =
  | Success('response)
  | Error(Js.Promise.error);

type useMutationConfigType('variables) = {variables: 'variables};

type _commitMutationConfig('variables, 'response) = {
  .
  "mutation": mutationNode,
  "variables": 'variables,
  "onCompleted":
    option(
      (Js.Nullable.t('response), Js.Nullable.t(array(mutationError))) =>
      unit,
    ),
  "onError": option(Js.Nullable.t(mutationError) => unit),
  "optimisticResponse": option('response),
  "optimisticUpdater": option(RecordSourceSelectorProxy.t => unit),
  "updater": option(RecordSourceSelectorProxy.t => unit),
};

exception Mutation_failed(array(mutationError));

[@bs.module "relay-runtime"]
external _commitMutation:
  (Environment.t, _commitMutationConfig('variables, 'response)) => unit =
  "commitMutation";

module MakeUseMutation = (C: MutationConfig) => {
  let use = () => {
    let environment = useEnvironmentFromContext();
    let (mutationState: mutationState(C.response), setMutationState) =
      React.useState(() => Idle);

    let resetMutationState = () => setMutationState(_ => Idle);

    let makeMutation =
        (
          ~variables: C.variables,
          ~optimisticResponse=?,
          ~optimisticUpdater=?,
          ~updater=?,
          (),
        )
        : Js.Promise.t(mutationResult(C.response)) =>
      Js.Promise.make((~resolve, ~reject) => {
        setMutationState(_ => Loading);

        _commitMutation(
          environment,
          {
            "variables": variables |> cleanVariables,
            "mutation": C.node,
            "onCompleted":
              Some(
                (res, errors) =>
                  switch (res |> toOpt, errors |> toOpt) {
                  | (_, Some(errors)) =>
                    setMutationState(_ => Error(errors));
                    reject(. Mutation_failed(errors));
                  | (Some(res), None) =>
                    setMutationState(_ => Success(Some(res)));
                    resolve(. Success(res));
                  | (None, None) =>
                    setMutationState(_ => Error([||]));
                    reject(. Mutation_failed([||]));
                  },
              ),
            "onError":
              Some(
                error =>
                  switch (error |> toOpt) {
                  | Some(error) =>
                    setMutationState(_ => Error([|error|]));
                    reject(. Mutation_failed([|error|]));
                  | None =>
                    setMutationState(_ => Error([||]));
                    reject(. Mutation_failed([||]));
                  },
              ),
            "optimisticResponse": optimisticResponse,
            "optimisticUpdater": optimisticUpdater,
            "updater": updater,
          },
        );
      });
    (makeMutation, mutationState, resetMutationState);
  };
};

module MakeCommitMutation = (C: MutationConfig) => {
  let commitMutation =
      (
        ~environment: Environment.t,
        ~variables: C.variables,
        ~optimisticUpdater=?,
        ~optimisticResponse=?,
        ~updater=?,
        (),
      )
      : Js.Promise.t(C.response) =>
    Js.Promise.make((~resolve, ~reject) =>
      _commitMutation(
        environment,
        {
          "variables": variables |> cleanVariables,
          "mutation": C.node,
          "onCompleted":
            Some(
              (res, errors) =>
                switch (res |> toOpt, errors |> toOpt) {
                | (_, Some(errors)) => reject(. Mutation_failed(errors))
                | (Some(res), None) => resolve(. res)
                | (None, None) => reject(. Mutation_failed([||]))
                },
            ),
          "onError":
            Some(
              error =>
                switch (error |> toOpt) {
                | Some(error) => reject(. Mutation_failed([|error|]))
                | None => reject(. Mutation_failed([||]))
                },
            ),
          "optimisticResponse": optimisticResponse,
          "optimisticUpdater": optimisticUpdater,
          "updater": updater,
        },
      )
    );
};

[@bs.module "relay-runtime"]
external _commitLocalUpdate:
  (Environment.t, RecordSourceSelectorProxy.t => unit) => unit =
  "commitLocalUpdate";

let commitLocalUpdate = (~environment, ~updater) =>
  _commitLocalUpdate(environment, updater);

module type SubscriptionConfig = {
  type variables;
  type response;
  let node: subscriptionNode;
};

type _subscriptionConfig('response, 'variables) = {
  .
  "subscription": subscriptionNode,
  "variables": 'variables,
  "onCompleted": option(unit => unit),
  "onError": option(Js.Exn.t => unit),
  "onNext": option('response => unit),
  "updater": option(updaterFn),
};

[@bs.module "relay-runtime"]
external requestSubscription:
  (Environment.t, _subscriptionConfig('response, 'variables)) => Disposable.t =
  "requestSubscription";

module MakeUseSubscription = (C: SubscriptionConfig) => {
  let subscribe =
      (
        ~environment: Environment.t,
        ~variables: C.variables,
        ~onCompleted: option(unit => unit)=?,
        ~onError: option(Js.Exn.t => unit)=?,
        ~onNext: option(C.response => unit)=?,
        ~updater: option(updaterFn)=?,
        (),
      ) =>
    requestSubscription(
      environment,
      {
        "subscription": C.node,
        "variables": variables |> cleanVariables,
        "onCompleted": onCompleted,
        "onError": onError,
        "onNext": onNext,
        "updater": updater,
      },
    );
};