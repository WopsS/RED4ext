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
            Item(name='Main', pattern='40 53 48 81 EC C0 01 00 00 FF 15 ? ? ? ? E8 ? ? ? ? E8 ? ? ? ?', expected=1, index=0)
        ]),

        Group(name='CInitializationState', functions=[
            Item(name='Run', pattern='48 83 EC 28 48 8B 05 ? ? ? ? 4C 8B C2 8B 88 F8 00 00 00', expected=1, index=0)
        ]),

        Group(name='CShutdownState', functions=[
            Item(name='Run', pattern='48 89 6C 24 18 56 48 83 EC 30 48 8B 0D ? ? ? ?', expected=1, index=0)
        ])
    ]
