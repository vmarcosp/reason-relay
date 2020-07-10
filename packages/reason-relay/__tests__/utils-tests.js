const { traverser } = require("../src/utils");

describe("conversion", () => {
  it("handles nullables at various levels", () => {
    expect(
      traverser(
        {
          me: {
            name: "Name",
            age: null,
            nicknames: [null, "SomeName"],
            nestedObjects: [{ someProp: null, otherProp: "Lars" }, null],
          },
          otherProp: null,
        },
        {
          __root: {
            "": {
              f: "RootFragment_fragment",
            },
            otherProp: {
              n: "",
            },
            me: {
              n: "",
              f: "MeFragment_fragment",
            },
            me_age: {
              n: "",
            },
            me_nicknames: {
              n: "",
            },
            me_nestedObjects: {
              n: "",
              f: "SomeFragment_fragment",
            },
            me_nestedObjects_someProp: {
              n: "",
            },
          },
        },
        {},
        undefined
      )
    ).toEqual({
      getFragmentRef_RootFragment_fragment: expect.any(Function),
      me: {
        getFragmentRef_MeFragment_fragment: expect.any(Function),
        name: "Name",
        age: undefined,
        nicknames: [undefined, "SomeName"],
        nestedObjects: [
          {
            someProp: undefined,
            otherProp: "Lars",
            getFragmentRef_SomeFragment_fragment: expect.any(Function),
          },
          undefined,
        ],
      },
      otherProp: undefined,
    });
  });

  it("handles converting enums", () => {
    expect(
      traverser(
        {
          ageRange: "999",
          me: {
            name: "Name",
            ageRange: "123",
            ageRanges: [null, "234"],
            nestedObjects: [{ someProp: null, otherProp: "345" }, null],
          },
        },
        {
          __root: {
            ageRange: {
              e: "enum_Enum",
            },
            me_ageRange: {
              n: "",
              e: "enum_Enum",
            },
            me_ageRanges: {
              n: "",
              e: "enum_Enum",
            },
            me_nestedObjects: {
              n: "",
            },
            me_nestedObjects_someProp: {
              n: "",
            },
            me_nestedObjects_otherProp: {
              n: "",
              e: "enum_Enum",
            },
          },
        },
        {
          enum_Enum: (v) => parseInt(v, 10),
        },
        undefined
      )
    ).toEqual({
      ageRange: 999,
      me: {
        name: "Name",
        ageRange: 123,
        ageRanges: [undefined, 234],
        nestedObjects: [
          {
            someProp: undefined,
            otherProp: 345,
          },
          undefined,
        ],
      },
      otherProp: undefined,
    });
  });

  it("handles converting unions, including nested unions", () => {
    expect(
      traverser(
        {
          someUnion: {
            __typename: "User",
            firstName: "First",
            ageRange: "123",
            meta: {
              ageRange: "234",
              nullable: null,
            },
          },
          friends: [
            null,
            {
              __typename: "User",
              firstName: "First",
              ageRange: "123",
              meta: {
                ageRange: "234",
                nullable: null,
              },
            },
            {
              __typename: "Observer",
              name: null,
              ageRange: "345",
              meta: {
                ageRange: "456",
                nullable: null,
              },
              friends: [
                null,
                {
                  __typename: "User",
                  firstName: "Second",
                  ageRange: "999",
                  meta: {
                    ageRange: "123",
                    nullable: null,
                  },
                },
              ],
            },
          ],
        },
        {
          __root: {
            "": {
              f: "1",
            },
            someUnion: {
              n: "",
              u: "union_Union",
            },
            someUnion_user: {
              f: "2",
            },
            someUnion_user_ageRange: {
              e: "enum_Enum",
            },
            someUnion_user_meta: {
              f: "3",
            },
            someUnion_user_meta_ageRange: {
              e: "enum_Enum",
            },
            someUnion_user_meta_nullable: {
              n: "",
            },
            friends: {
              n: "",
              u: "union_Union",
            },
            friends_user: {
              f: "4",
            },
            friends_user_ageRange: {
              e: "enum_Enum",
            },
            friends_user_meta: {
              f: "5",
            },
            friends_user_meta_ageRange: {
              e: "enum_Enum",
            },
            friends_user_meta_nullable: {
              n: "",
            },
            friends_observer: {
              f: "6",
            },
            friends_observer_name: {
              n: "",
            },
            friends_observer_ageRange: {
              e: "enum_Enum",
            },
            friends_observer_meta: {
              f: "7",
            },
            friends_observer_meta_ageRange: {
              e: "enum_Enum",
            },
            friends_observer_meta_nullable: {
              n: "",
            },
            friends_observer_friends: {
              n: "",
              u: "union_Union",
            },
            friends_observer_friends_user_ageRange: {
              e: "enum_Enum",
            },
            friends_observer_friends_user: {
              f: "8",
            },
            friends_observer_friends_user_meta: {
              f: "9",
            },
            friends_observer_friends_user_meta_ageRange: {
              e: "enum_Enum",
            },
            friends_observer_friends_user_meta_nullable: {
              n: "",
            },
          },
        },
        {
          enum_Enum: (v) => parseInt(v, 10),
          union_Union: (v) => [123, v],
        },
        undefined
      )
    ).toEqual({
      getFragmentRef_1: expect.any(Function),
      someUnion: [
        123,
        {
          getFragmentRef_2: expect.any(Function),
          __typename: "User",
          firstName: "First",
          ageRange: 123,
          meta: {
            getFragmentRef_3: expect.any(Function),
            ageRange: 234,
            nullable: undefined,
          },
        },
      ],
      friends: [
        undefined,
        [
          123,
          {
            getFragmentRef_4: expect.any(Function),
            __typename: "User",
            firstName: "First",
            ageRange: 123,
            meta: {
              getFragmentRef_5: expect.any(Function),
              ageRange: 234,
              nullable: undefined,
            },
          },
        ],
        [
          123,
          {
            getFragmentRef_6: expect.any(Function),
            __typename: "Observer",
            name: undefined,
            ageRange: 345,
            meta: {
              getFragmentRef_7: expect.any(Function),
              ageRange: 456,
              nullable: undefined,
            },
            friends: [
              undefined,
              [
                123,
                {
                  getFragmentRef_8: expect.any(Function),
                  __typename: "User",
                  firstName: "Second",
                  ageRange: 999,
                  meta: {
                    getFragmentRef_9: expect.any(Function),
                    ageRange: 123,
                    nullable: undefined,
                  },
                },
              ],
            ],
          },
        ],
      ],
    });
  });

  it("handles recursive objects (input objects)", () => {
    expect(
      traverser(
        {
          someInput: {
            someEnum: "999",
            lat: null,
            meta: {
              someEnum: "888",
              nullable: null,
            },
            anotherInput: {
              meta: null,
              someEnum: "123",
              anotherInput: {
                someEnum: "234",
                anotherInput: null,
                meta: {
                  someEnum: "888",
                  nullable: null,
                },
              },
            },
          },
        },
        {
          AnotherInput: {
            someEnum: {
              e: "enum_Enum",
            },
            anotherInput: {
              n: "",
              r: "AnotherInput",
            },
            meta: {
              n: "",
            },
            meta_someEnum: {
              e: "enum_Enum",
            },
            meta_nullable: {
              n: "",
            },
          },
          SomeInput: {
            lat: {
              n: "",
            },
            someEnum: {
              e: "enum_Enum",
            },
            anotherInput: {
              r: "AnotherInput",
            },
            meta: {
              n: "",
            },
            meta_someEnum: {
              e: "enum_Enum",
            },
            meta_nullable: {
              n: "",
            },
          },
          __root: {
            someInput: {
              r: "SomeInput",
            },
          },
        },
        {
          enum_Enum: (v) => parseInt(v, 10),
        },
        undefined
      )
    ).toEqual({
      someInput: {
        someEnum: 999,
        lat: undefined,
        meta: {
          someEnum: 888,
          nullable: undefined,
        },
        anotherInput: {
          meta: undefined,
          someEnum: 123,
          anotherInput: {
            someEnum: 234,
            anotherInput: undefined,
            meta: {
              someEnum: 888,
              nullable: undefined,
            },
          },
        },
      },
    });
  });

  it("handles top level unions on fragments", () => {
    expect(
      traverser(
        {
          name: "Name",
          onlineStatus: "Online",
        },
        {
          __root: {
            "": { u: "fragment" },
            onlineStatus: { n: "", e: "enum_OnlineStatus" },
          },
        },
        {
          fragment: (v) => [123, v],
          enum_OnlineStatus: (v) => "enum_OnlineStatus",
        },
        undefined
      )
    ).toEqual([
      123,
      {
        name: "Name",
        onlineStatus: "enum_OnlineStatus",
      },
    ]);
  });
});
