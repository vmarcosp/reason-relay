/* @generated */

type enum_OnlineStatus = [
  | `Idle
  | `Offline
  | `Online
  | `FutureAddedValue(string)
];

let unwrap_enum_OnlineStatus: string => enum_OnlineStatus =
  fun
  | "Idle" => `Idle
  | "Offline" => `Offline
  | "Online" => `Online
  | v => `FutureAddedValue(v);

let wrap_enum_OnlineStatus: enum_OnlineStatus => string =
  fun
  | `Idle => "Idle"
  | `Offline => "Offline"
  | `Online => "Online"
  | `FutureAddedValue(v) => v;

module Types = {
  type response_setOnlineStatus_user = ReasonRelay.allFieldsMasked;
  type response_setOnlineStatus = {
    user: option(response_setOnlineStatus_user),
  };

  type response = {setOnlineStatus: option(response_setOnlineStatus)};
  type variables = {
    onlineStatus: [ | `Idle | `Offline | `Online | `FutureAddedValue(string)],
  };
};

module Internal = {
  type wrapResponseRaw;
  let wrapResponseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"setOnlineStatus":{"n":""},"setOnlineStatus_user":{"n":"","f":"TestMutation_user"}}} |json}
  ];
  let wrapResponseConverterMap = ();
  let convertWrapResponse = v =>
    v
    ->ReasonRelay._convertObj(
        wrapResponseConverter,
        wrapResponseConverterMap,
        Js.null,
      );

  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"setOnlineStatus":{"n":""},"setOnlineStatus_user":{"n":"","f":"TestMutation_user"}}} |json}
  ];
  let responseConverterMap = ();
  let convertResponse = v =>
    v
    ->ReasonRelay._convertObj(
        responseConverter,
        responseConverterMap,
        Js.undefined,
      );

  let variablesConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"onlineStatus":{"e":"enum_OnlineStatus"}}} |json}
  ];
  let variablesConverterMap = {"enum_OnlineStatus": wrap_enum_OnlineStatus};
  let convertVariables = v =>
    v
    ->ReasonRelay._convertObj(
        variablesConverter,
        variablesConverterMap,
        Js.undefined,
      );
};

module Utils = {
  open Types;
  let makeVariables = (~onlineStatus): variables => {
    onlineStatus: onlineStatus,
  };

  let make_response_setOnlineStatus_user = () => [@ocaml.warning "-27"] {};

  let make_response_setOnlineStatus = (~user=?, ()): response_setOnlineStatus => {
    user: user,
  };

  let makeOptimisticResponse = (~setOnlineStatus=?, ()): response => {
    setOnlineStatus: setOnlineStatus,
  };
};

type operationType = ReasonRelay.mutationNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "kind": "LocalArgument",
    "name": "onlineStatus",
    "type": "OnlineStatus!",
    "defaultValue": null
  }
],
v1 = [
  {
    "kind": "Variable",
    "name": "onlineStatus",
    "variableName": "onlineStatus"
  }
];
return {
  "kind": "Request",
  "fragment": {
    "kind": "Fragment",
    "name": "TestMutationWithOnlyFragmentSetOnlineStatusMutation",
    "type": "Mutation",
    "metadata": null,
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "setOnlineStatus",
        "storageKey": null,
        "args": (v1/*: any*/),
        "concreteType": "SetOnlineStatusPayload",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "user",
            "storageKey": null,
            "args": null,
            "concreteType": "User",
            "plural": false,
            "selections": [
              {
                "kind": "FragmentSpread",
                "name": "TestMutation_user",
                "args": null
              }
            ]
          }
        ]
      }
    ]
  },
  "operation": {
    "kind": "Operation",
    "name": "TestMutationWithOnlyFragmentSetOnlineStatusMutation",
    "argumentDefinitions": (v0/*: any*/),
    "selections": [
      {
        "kind": "LinkedField",
        "alias": null,
        "name": "setOnlineStatus",
        "storageKey": null,
        "args": (v1/*: any*/),
        "concreteType": "SetOnlineStatusPayload",
        "plural": false,
        "selections": [
          {
            "kind": "LinkedField",
            "alias": null,
            "name": "user",
            "storageKey": null,
            "args": null,
            "concreteType": "User",
            "plural": false,
            "selections": [
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "id",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "firstName",
                "args": null,
                "storageKey": null
              },
              {
                "kind": "ScalarField",
                "alias": null,
                "name": "onlineStatus",
                "args": null,
                "storageKey": null
              }
            ]
          }
        ]
      }
    ]
  },
  "params": {
    "operationKind": "mutation",
    "name": "TestMutationWithOnlyFragmentSetOnlineStatusMutation",
    "id": null,
    "text": "mutation TestMutationWithOnlyFragmentSetOnlineStatusMutation(\n  $onlineStatus: OnlineStatus!\n) {\n  setOnlineStatus(onlineStatus: $onlineStatus) {\n    user {\n      ...TestMutation_user\n      id\n    }\n  }\n}\n\nfragment TestMutation_user on User {\n  id\n  firstName\n  onlineStatus\n}\n",
    "metadata": {}
  }
};
})() |json}
];
