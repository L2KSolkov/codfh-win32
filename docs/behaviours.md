# RenderWare Studio behaviours

Every behaviour the image registers with `RWS::CClassFactory`. Each dynamic initializer in the
game's block (`0x3096E0`-`0x30DBBE`) builds a `CRegistrar` from the class name, the class's
`MakeNew`, its size and its allocation policy. That makes the name, MakeNew and size below
evidence for naming a class and its methods. `tools/behaviours.py` lists the registrations (the
four pushes before each registrar call).

| Registrar call | Class | MakeNew | Size |
|---|---|---|---|
| `0x309926` | CDebugScript | `sub_42F40` | `0x24` |
| `0x30a4c9` | AddTaskTrigger | `sub_9DD80` | `0x100` |
| `0x30a4f9` | AnimatedBGTrigger | `sub_9F130` | `0x190` |
| `0x30a526` | CAnimBankInfo | `sub_A02D0` | `0x68` |
| `0x30a559` | CAnimPackSelector | `sub_A0A50` | `0x208` |
| `0x30a589` | AnimPackTrigger | `sub_A11E0` | `0x1c0` |
| `0x30a5b9` | AnimTestTrigger | `sub_A1690` | `0x1c0` |
| `0x30a5e9` | HitDeathTestTrigger | `sub_A1CA0` | `0x1b0` |
| `0x30a619` | SceneTestTrigger | `sub_A2080` | `0x1b0` |
| `0x30a649` | CCESSPoolTrigger | `sub_A23F0` | `0x160` |
| `0x30a679` | ConfinedAreaTrigger | `sub_A2C20` | `0xd0` |
| `0x30a6a9` | CustomTrigger | `sub_A2DD0` | `0x120` |
| `0x30a6d9` | DestructableObjectTrigger | `sub_A3510` | `0x100` |
| `0x30a709` | MeshSwapDestructableObjectTrigger | `sub_A3A40` | `0x120` |
| `0x30a739` | DogTrigger | `sub_A3E80` | `0x130` |
| `0x30a766` | CMountedWeaponBehavior | `sub_A4950` | `0x24` |
| `0x30a799` | MountedWeaponTrigger | `sub_A5360` | `0x100` |
| `0x30a7c6` | CNPCWeaponBehavior | `sub_A58B0` | `0x24` |
| `0x30a7f6` | XBOXPadMap | `sub_A6C50` | `0x1c` |
| `0x30a829` | ParticleTrigger | `sub_A6D80` | `0x380` |
| `0x30a856` | PathNode | `sub_A8FC0` | `0x1c` |
| `0x30a886` | CPickupSelector | `sub_A90E0` | `0x20` |
| `0x30a8b9` | PickupTrigger | `sub_A93B0` | `0xe0` |
| `0x30a8e9` | PlayerTrigger | `sub_A9980` | `0x470` |
| `0x30a919` | ProjectileGeneratorTrigger | `sub_AD1B0` | `0x280` |
| `0x30a946` | RenderTrigger | `sub_AF150` | `0x18` |
| `0x30a979` | SceneTrigger | `sub_AF9C0` | `0xd0` |
| `0x30a9a6` | SectionInfo | `sub_AFBC0` | `0x20` |
| `0x30a9d9` | SectionTrigger | `sub_B0180` | `0xe0` |
| `0x30aa06` | StartingSections | `sub_B0410` | `0x20` |
| `0x30aa36` | CShellBehaviorClass | `sub_B07D0` | `0x20` |
| `0x30aa66` | CShellLevelBehaviorClass | `sub_B6EB0` | `0x20` |
| `0x30aa99` | SimpleMechanicTrigger | `sub_B7330` | `0x110` |
| `0x30aac9` | SoldierTrigger | `sub_B7AA0` | `0x1a0` |
| `0x30aaf9` | CSoundBankSelector | `sub_B9110` | `0x1c0` |
| `0x30ab29` | SoundBankTrigger | `sub_B99C0` | `0x1c0` |
| `0x30ab56` | SplinePath | `sub_B9EA0` | `0x38` |
| `0x30ab89` | StopSoundStreamTrigger | `sub_BA9E0` | `0xd0` |
| `0x30abb9` | StreamTrigger | `sub_BAC50` | `0x110` |
| `0x30abe9` | StreamVolume | `sub_BB380` | `0x110` |
| `0x30ac19` | Trigger | `sub_BB9B0` | `0xc0` |
| `0x30ac49` | VehicleEnterExitTrigger | `sub_BEAB0` | `0xf0` |
| `0x30ac79` | FlakTrigger | `sub_BF650` | `0x210` |
| `0x30aca9` | VehicleTrigger | `sub_BF960` | `0x200` |
| `0x30acd6` | CWeaponBehavior | `sub_C10B0` | `0x28` |
| `0x30ad06` | CExplosiveBehavior | `sub_C4830` | `0x28` |
| `0x30ad36` | CTankBehavior | `sub_C4C10` | `0x28` |
| `0x30ad66` | CAntiTankBehavior | `sub_C4D30` | `0x28` |
| `0x30ad96` | CGrenadeBehavior | `sub_C4F10` | `0x28` |
| `0x30adc9` | WorldLight | `sub_C5380` | `0xe0` |
| `0x30adf6` | LevelInfo | `sub_C5A60` | `0x20` |
| `0x30ae26` | CPickupBehavior | `sub_C5D70` | `0x28` |
| `0x30ae59` | LevelClumpBankParamTrigger | `sub_C60E0` | `0xc0` |
| `0x30ae89` | StreamClumpTrigger | `sub_C64A0` | `0xd0` |
| `0x30aeb9` | LevelScriptTrigger | `sub_C66C0` | `0xd0` |
| `0x30aee9` | PlaySoundTrigger | `sub_C6A80` | `0x120` |
| `0x30af19` | GimpTrigger | `sub_C6DF0` | `0x160` |
| `0x30af46` | CGlobalSounds | `sub_C7CE0` | `0x20` |
| `0x30af76` | CPoolSizes | `sub_CA2C0` | `0x44` |
| `0x30afa6` | CMountedWeaponSelector | `sub_CA790` | `0x20` |
| `0x30afd9` | LadderTrigger | `sub_CAA90` | `0xe0` |
| `0x30b009` | ShrimpTrigger | `sub_CAE20` | `0x110` |
| `0x30b039` | PulseZoneTrigger | `sub_CB430` | `0xf0` |
| `0x30b069` | GimpVehicleTrigger | `sub_CB9D0` | `0x100` |
| `0x30b099` | EndLevelTrigger | `sub_CC090` | `0xd0` |
| `0x30b0c9` | FogTrigger | `sub_CC370` | `0xe0` |
| `0x30b0f9` | PASTrigger | `sub_CC650` | `0xd0` |
| `0x30b5a9` | ParticleEditor | `sub_F1320` | `0x258` |
| `0x30b636` | SparkParticle | `sub_F4570` | `0x28` |
| `0x30c279` | cNetLevelParams | `sub_1B6FE0` | `0xd8` |
| `0x30c2b9` | cNetPickupTrigger | `sub_1BE0B0` | `0x100` |
| `0x30c2e9` | cNetPlayerTrigger | `sub_1BE4D0` | `0x480` |
| `0x30c319` | cNetSoldierTrigger | `sub_1C06E0` | `0x1a0` |
| `0x30c359` | cNetSpawnPoint | `sub_1C0910` | `0x100` |
| `0x30c389` | cNetStaticCamTrigger | `sub_1C2120` | `0xd0` |
| `0x30c3b6` | cNetTriggerViewControl | `sub_1C2AB0` | `0x40` |

The base trigger class is `Trigger` (MakeNew `sub_BB9B0`, 0xC0 bytes). The recovered sources
still call it `Trigger` (include/types/type_44350.h). The spawnable triggers derive from it:
`AddTaskTrigger` is the kind-0x17 trigger and `AnimatedBGTrigger` the kind-8 one
(unit_09AD40).

`Trigger` itself (`0xBB9B0`-`0xBEAB0`, src/recovered/unit_0BB9B0.cpp) matches in full: its
MakeNew, constructor, destructor, HandleAttributes (40 commands, after the system commands of
`sub_BD0B0` and a first pass for command 35), HandleEvents, the facing tests `vf_028` and
`vf_02C`, and the helpers the derived triggers share (its blocks of messages, `sub_BD490` to
`sub_BDAC0`; its message filter list, `sub_BDB60`; moving it and back, `sub_BE710` and
`sub_BE810`). Its HandleAttributes has both command iterators at function scope; with the first
in a block of its own, the case locals land a slot too near `ebp`.

`PlayerTrigger` (`0xA9980`-`0xAD1B0`, unit_0A9980): matched, HandleAttributes (`sub_AA400`) included;
its 116 commands include the camera's view angles from the video mode (command 18) and a weapons block
(command 5). Its settings are copied into the player entity (type_10F710) by `sub_ACF10`.
