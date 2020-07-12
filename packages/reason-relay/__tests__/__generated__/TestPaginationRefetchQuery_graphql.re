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
  type response = {
    getFragmentRef_TestPagination_query:
      unit => TestPagination_query_graphql.t,
  };
  type refetchVariables = {
    groupId: option(string),
    onlineStatuses:
      option(
        array([ | `Idle | `Offline | `Online | `FutureAddedValue(string)]),
      ),
    count: option(int),
    cursor: option(string),
  };
  let makeRefetchVariables =
      (~groupId=?, ~onlineStatuses=?, ~count=?, ~cursor=?, ())
      : refetchVariables => {
    groupId,
    onlineStatuses,
    count,
    cursor,
  };
  type variables = {
    groupId: string,
    onlineStatuses:
      option(
        array([ | `Idle | `Offline | `Online | `FutureAddedValue(string)]),
      ),
    count: option(int),
    cursor: option(string),
  };
};

module Internal = {
  type responseRaw;
  let responseConverter: Js.Dict.t(Js.Dict.t(Js.Dict.t(string))) = [%raw
    {json| {"__root":{"":{"f":"TestPagination_query"}}} |json}
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
    {json| {"__root":{"onlineStatuses":{"n":"","e":"enum_OnlineStatus"},"count":{"n":""},"cursor":{"n":""}}} |json}
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

type preloadToken;

module Utils = {
  open Types;
  let makeVariables =
      (~groupId, ~onlineStatuses=?, ~count=?, ~cursor=?, ()): variables => {
    groupId,
    onlineStatuses,
    count,
    cursor,
  };
};

type operationType = ReasonRelay.queryNode;

let node: operationType = [%raw
  {json| (function(){
var v0 = [
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "groupId",
    "type": "ID!"
  },
  {
    "defaultValue": null,
    "kind": "LocalArgument",
    "name": "onlineStatuses",
    "type": "[OnlineStatus!]"
  },
  {
    "defaultValue": 2,
    "kind": "LocalArgument",
    "name": "count",
    "type": "Int"
  },
  {
    "defaultValue": "",
    "kind": "LocalArgument",
    "name": "cursor",
    "type": "String"
  }
],
v1 = {
  "kind": "Variable",
  "name": "groupId",
  "variableName": "groupId"
},
v2 = {
  "kind": "Variable",
  "name": "onlineStatuses",
  "variableName": "onlineStatuses"
},
v3 = [
  {
    "kind": "Variable",
    "name": "after",
    "variableName": "cursor"
  },
  {
    "kind": "Variable",
    "name": "first",
    "variableName": "count"
  },
  (v1/*: any*/),
  (v2/*: any*/)
],
v4 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "id",
  "storageKey": null
},
v5 = {
  "alias": null,
  "args": null,
  "kind": "ScalarField",
  "name": "firstName",
  "storageKey": null
},
v6 = [
  {
    "kind": "Literal",
    "name": "first",
    "value": 1
  }
];
return {
  "fragment": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Fragment",
    "metadata": null,
    "name": "TestPaginationRefetchQuery",
    "selections": [
      {
        "args": [
          {
            "kind": "Variable",
            "name": "count",
            "variableName": "count"
          },
          {
            "kind": "Variable",
            "name": "cursor",
            "variableName": "cursor"
          },
          (v1/*: any*/),
          (v2/*: any*/)
        ],
        "kind": "FragmentSpread",
        "name": "TestPagination_query"
      }
    ],
    "type": "Query"
  },
  "kind": "Request",
  "operation": {
    "argumentDefinitions": (v0/*: any*/),
    "kind": "Operation",
    "name": "TestPaginationRefetchQuery",
    "selections": [
      {
        "alias": null,
        "args": (v3/*: any*/),
        "concreteType": "MemberConnection",
        "kind": "LinkedField",
        "name": "members",
        "plural": false,
        "selections": [
          {
            "alias": null,
            "args": null,
            "concreteType": "MemberEdge",
            "kind": "LinkedField",
            "name": "edges",
            "plural": true,
            "selections": [
              {
                "alias": null,
                "args": null,
                "concreteType": null,
                "kind": "LinkedField",
                "name": "node",
                "plural": false,
                "selections": [
                  {
                    "alias": null,
                    "args": null,
                    "kind": "ScalarField",
                    "name": "__typename",
                    "storageKey": null
                  },
                  (v4/*: any*/),
                  {
                    "kind": "InlineFragment",
                    "selections": [
                      (v5/*: any*/),
                      {
                        "alias": null,
                        "args": (v6/*: any*/),
                        "concreteType": "UserConnection",
                        "kind": "LinkedField",
                        "name": "friendsConnection",
                        "plural": false,
                        "selections": [
                          {
                            "alias": null,
                            "args": null,
                            "kind": "ScalarField",
                            "name": "totalCount",
                            "storageKey": null
                          }
                        ],
                        "storageKey": "friendsConnection(first:1)"
                      }
                    ],
                    "type": "User"
                  },
                  {
                    "kind": "InlineFragment",
                    "selections": [
                      {
                        "alias": null,
                        "args": null,
                        "kind": "ScalarField",
                        "name": "name",
                        "storageKey": null
                      },
                      {
                        "alias": null,
                        "args": (v6/*: any*/),
                        "concreteType": "UserConnection",
                        "kind": "LinkedField",
                        "name": "adminsConnection",
                        "plural": false,
                        "selections": [
                          {
                            "alias": null,
                            "args": null,
                            "concreteType": "UserEdge",
                            "kind": "LinkedField",
                            "name": "edges",
                            "plural": true,
                            "selections": [
                              {
                                "alias": null,
                                "args": null,
                                "concreteType": "User",
                                "kind": "LinkedField",
                                "name": "node",
                                "plural": false,
                                "selections": [
                                  (v4/*: any*/),
                                  (v5/*: any*/)
                                ],
                                "storageKey": null
                              }
                            ],
                            "storageKey": null
                          }
                        ],
                        "storageKey": "adminsConnection(first:1)"
                      }
                    ],
                    "type": "Group"
                  }
                ],
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "cursor",
                "storageKey": null
              }
            ],
            "storageKey": null
          },
          {
            "alias": null,
            "args": null,
            "concreteType": "PageInfo",
            "kind": "LinkedField",
            "name": "pageInfo",
            "plural": false,
            "selections": [
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "endCursor",
                "storageKey": null
              },
              {
                "alias": null,
                "args": null,
                "kind": "ScalarField",
                "name": "hasNextPage",
                "storageKey": null
              }
            ],
            "storageKey": null
          }
        ],
        "storageKey": null
      },
      {
        "alias": null,
        "args": (v3/*: any*/),
        "filters": [
          "groupId",
          "onlineStatuses"
        ],
        "handle": "connection",
        "key": "TestPagination_query_members",
        "kind": "LinkedHandle",
        "name": "members"
      }
    ]
  },
  "params": {
    "id": null,
    "metadata": {
      "derivedFrom": "TestPagination_query",
      "isRefetchableQuery": true
    },
    "name": "TestPaginationRefetchQuery",
    "operationKind": "query",
    "text": "query TestPaginationRefetchQuery(\n  $groupId: ID!\n  $onlineStatuses: [OnlineStatus!]\n  $count: Int = 2\n  $cursor: String = \"\"\n) {\n  ...TestPagination_query_2z6KWr\n}\n\nfragment TestPagination_query_2z6KWr on Query {\n  members(groupId: $groupId, onlineStatuses: $onlineStatuses, first: $count, after: $cursor) {\n    edges {\n      node {\n        __typename\n        ... on User {\n          id\n          ...TestPagination_user\n        }\n        ... on Group {\n          id\n          name\n          adminsConnection(first: 1) {\n            edges {\n              node {\n                id\n                firstName\n              }\n            }\n          }\n        }\n        ... on Node {\n          id\n        }\n      }\n      cursor\n    }\n    pageInfo {\n      endCursor\n      hasNextPage\n    }\n  }\n}\n\nfragment TestPagination_user on User {\n  firstName\n  friendsConnection(first: 1) {\n    totalCount\n  }\n}\n"
  }
};
})() |json}
];

include ReasonRelay.MakePreloadQuery({
  type variables = Types.variables;
  type queryPreloadToken = preloadToken;
  type response = Types.response;
  let query = node;
  let convertVariables = Internal.convertVariables;
});
