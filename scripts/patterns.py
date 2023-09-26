from typing import List

class Item:
    name: str
    pattern: str
    expected: int
    index: int
    offset: int

    def __init__(self, pattern: str, name: str = '', expected: int = 1, index: int = 0, offset: int = 0) -> None:
        self.name = name
        self.pattern = pattern
        self.expected = expected
        self.index = index
        self.offset = offset

class Group:
    name: str
    pointers: List[Item]
    functions: List[Item]

    def __init__(self, name: str, pointers: List[Item] = [], functions: List[Item] = []) -> None:
        self.name = name
        self.pointers = pointers
        self.functions = functions

def get_groups() -> List[Group]:
    return [
        Group(name='Global', functions=[
            Item(name='Main', pattern='40 55 53 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? FF 15 ? ? ? ?', expected=1, index=0),
            Item(name='ExecuteProcess', pattern='48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 41 81 79 ? ? ? ? ?', expected=1, index=0),
        ]),

        Group(name='CGameApplication', functions=[
            Item(name='AddState', pattern='48 89 5C 24 ? 48 89 54 24 ? 57 48 83 EC ? 48 8B 02 48 8D B9 ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CInitializationState', functions=[
            Item(name='Run', pattern='40 53 48 83 EC ? 48 8B 05 ? ? ? ? 33 DB 4C 8B C2 8B 88 ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CRunningState', functions=[
            Item(name='Run', pattern='40 53 48 83 EC ? 83 64 24 ? ? 48 8D 05 ? ? ? ? 48 8B 0D ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CShutdownState', functions=[
            Item(name='Run', pattern='40 53 48 83 EC ? 48 8B DA E8 ? ? ? ? 48 8B CB 89 83 ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CBaseEngine', functions=[
            Item(name='InitScripts', pattern='48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 41 0F B7 F1', expected=1, index=0),
            Item(name='LoadScripts', pattern='48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 49 8D 99 ? ? ? ?', expected=1, index=0)
        ])
    ]
