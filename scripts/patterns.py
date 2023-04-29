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
            Item(name='Main', pattern='40 53 48 81 EC ? ? ? ? FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CGameApplication', functions=[
            Item(name='Run', pattern='48 89 5C 24 08 57 48 83 EC 20 48 8B D9 33 FF 90', expected=3, index=0)
        ]),

        Group(name='CInitializationState', functions=[
            Item(name='Run', pattern='48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C2 8B 88 F8 00 00 00', expected=1, index=0)
        ]),

        Group(name='CRunningState', functions=[
            Item(name='Run', pattern='40 53 48 83 EC 20 48 8B 0D ? ? ? ? 48 8B DA E8 ? ? ? ? 84 C0', expected=1, index=0)
        ]),

        Group(name='CShutdownState', functions=[
            Item(name='Run', pattern='48 89 6C 24 18 56 48 83 EC 30 48 8B 0D ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='Scripts', function=[
            Item(name='RedscriptCompile', pattern='48 89 5C 24 08 48 89 74 24 10 57 48 83 EC 40 48 8B FA 48 8B F1 48 8D 54 24 30 49 8B C9 49 8B D8', expected=1, index=0),
            Item(name='RedmodCompile', pattern='48 89 5C 24 08 48 89 6C 24 10 48 89 74 24 18 57 48 83 EC 20 41 0F B7 D8 0F B6 FA 48 8B F1 E8', expected=1, index=0)
        ])
    ]
