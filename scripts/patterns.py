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
        Group(name='CBaseFunction', pointers=[
            Item(name='Handlers', pattern='4C 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 4C 89 9B ? ? ? ?', expected=2, index=1, offset=3)
        ]),

        Group(name='CGameEngine', pointers=[
            Item(pattern='48 89 05 ? ? ? ? 48 8B D8 48 8B 10 FF 92 ? ? ? ?', offset=3)
        ]),

        Group(name='CRTTIRegistrator', pointers=[
            Item(name='RTTIAsyncId', pattern='F0 0F C1 05 ? ? ? ? FF C0 48 8D 0D ? ? ? ? 89 05 ? ? ? ? E8 ? ? ? ?', expected=11821, index=0, offset=4)
        ]),

        Group(name='CStack', pointers=[
            Item(name='vtbl', pattern='48 8D 05 ? ? ? ? 48 89 45 ? 48 8D 45 ? 48 89 45 ? 66 0F 7F 45 ?', offset=3, expected=1, index=0)
        ]),

        Group(name='JobDispatcher', pointers=[
            Item(pattern='48 89 05 ? ? ? ? 48 83 C4 ? 5F C3', offset=3, expected=6, index=4)
        ]),

        Group(name='Memory', pointers=[
            Item(name='Vault', pattern='C6 04 0A 01 48 8D 0D ? ? ? ? 8B 50 ? 48 8B C1', offset=7, expected=2, index=0),
        ]),

        Group(name='OpcodeHandlers', pointers=[
            Item(pattern='4C 8D 05 ? ? ? ? 48 8D 0D ? ? ? ? 4C 89 9B ? ? ? ?', offset=3, expected=2, index=0)
        ]),

        Group(name='ResourceDepot', pointers=[
            Item(pattern="48 89 05 ? ? ? ? 49 8B 5B ? 49 8B 73", offset=3, expected=1, index=0)
        ]),

        Group(name='ResourceLoader', pointers=[
            Item(pattern='48 89 05 ? ? ? ? 48 83 C4 ? 5F C3', offset=3, expected=6, index=2)
        ]),
    ]
