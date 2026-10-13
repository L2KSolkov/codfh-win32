// The script interpreter's commands ("efuncs"), first unit: the command
// lookup (sub_441B0), the debugger's hook (sub_44220), the result push
// (sub_44350) and the first commands of the table String1 (0x4276E0), each
// named there. The commands' units run on to sub_67200 at least; their
// original file names and boundaries are not recovered (M1), so this one is
// named for its start address.

#include "game/clumpdata.h"
#include <xmmintrin.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rw/ostypes.h"
#include "rw/rprandom.h"
#include "rw/bavector.h"
#include "game/data.h"
#include "types/musicplayer.h"
#include "game/functions.h"
#include "types/type_3D2E7C.h"
#include "types/type_3CE1FC.h"
#include "types/type_3CE4B4.h"
#include "types/type_3CE6D0.h"
#include "types/type_154C0_1048.h"
#include "types/type_3DF30.h"
#include "types/type_3DF8D8.h"
#include "types/type_10F710.h"
#include "types/type_1227C0.h"
#include "types/AIData.h"
#include "types/alfaobject.h"
#include "types/animbank.h"
#include "types/alfasched.h"
#include "types/type_3D3548.h"
#include "types/type_3DAFC8.h"
#include "types/type_3DBC78.h"
#include "types/type_4AE70.h"
#include "game/surfaceparticles.h"
#include "types/type_3DC048.h"
#include "types/type_3DC378.h"
#include "types/type_3DA6C0.h"
#include "types/type_3DAC58.h"
#include "types/type_3DDB98.h"
#include "types/type_17DB90.h"
#include "types/type_3DE0E0.h"
#include "types/type_495F0.h"
#include "types/type_4B9E90.h"
#include "types/type_545C0.h"
#include "types/type_5A6C0.h"
#include "types/type_62A60.h"
#include "types/type_44350.h"
#include "types/type_6EE50.h"
#include "types/type_67620.h"
#include "types/type_92430.h"
#include "types/ccess.h"
#include "types/CAnimPackSelector.h"
#include "types/type_9BB60.h"
#include "types/type_DC400.h"
#include "types/type_3DD948.h"
#include "game/netmsg.h"
#include "types/type_3D32F8.h"
#include "types/ParticleTrigger.h"
#include "types/EndLevelTrigger.h"
#include "game/gameloop.h"

// The commands, defined in this unit and the next ones (the table below names them).
void sub_442D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_443C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44400(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44440(RwUInt32 arg_0, type_44350 *arg_4);
void sub_444C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44540(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44590(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44610(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44690(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44710(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44770(RwUInt32 arg_0, type_44350 *arg_4);
void sub_447D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44820(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44900(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44970(RwUInt32 arg_0, type_44350 *arg_4);
void sub_449E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44AD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44BB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44C70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44D00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44DA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44DF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44ED0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44F30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_44FC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45050(RwUInt32 arg_0, type_44350 *arg_4);
void sub_450E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_451E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45280(RwUInt32 arg_0, type_44350 *arg_4);
void sub_453F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_454A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45540(RwUInt32 arg_0, type_44350 *arg_4);
void sub_455A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45610(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45680(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45720(RwUInt32 arg_0, type_44350 *arg_4);
void sub_457A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_458A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45A50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45AF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45C60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45CD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45E00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45FD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_45FF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46040(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46120(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46180(RwUInt32 arg_0, type_44350 *arg_4);
void sub_461E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46280(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46320(RwUInt32 arg_0, type_44350 *arg_4);
void sub_463C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_464F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46570(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46680(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46720(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46840(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46B50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46BC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46C20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46C80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46D60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46E40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46EF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46F40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_46FE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47150(RwUInt32 arg_0, type_44350 *arg_4);
void sub_471D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47250(RwUInt32 arg_0, type_44350 *arg_4);
void sub_472D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47350(RwUInt32 arg_0, type_44350 *arg_4);
void sub_473C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_474E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47560(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47700(RwUInt32 arg_0, type_44350 *arg_4);
void sub_477A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47A20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47C20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_47F00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_481C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48230(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48290(RwUInt32 arg_0, type_44350 *arg_4);
void sub_484B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48570(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48800(RwUInt32 arg_0, type_44350 *arg_4);
void sub_488D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48A10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48B10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48B80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48C10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48C70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_48DA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49040(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49080(RwUInt32 arg_0, type_44350 *arg_4);
void sub_490D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49120(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_491C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49270(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49320(RwUInt32 arg_0, type_44350 *arg_4);
void sub_493D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49420(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49470(RwUInt32 arg_0, type_44350 *arg_4);
void sub_494C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49500(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49590(RwUInt32 arg_0, type_44350 *arg_4);
void sub_495F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49970(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49A00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49A50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49AF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49C90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49D10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_49D70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A0F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A180(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A210(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A270(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A2E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A350(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A420(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A580(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A6F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A8B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A8F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4A960(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4AB20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4AB90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4AF10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B0B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B0F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B150(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B220(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B300(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B3A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B490(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B770(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B820(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B870(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B8C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B910(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B990(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4B9B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BA80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BAA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BBE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BCF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BD70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BE20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BE70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BEF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4BFA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C020(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C080(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C150(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C1D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C2A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C340(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C3E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C460(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C4E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C590(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C670(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C6D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C770(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C860(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4C9E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CA50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CAC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CB20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CBE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CC80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CCF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CD80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CE10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CE80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CF30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4CFA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D090(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D660(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D720(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D7F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D8B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4D9B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4DB20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E470(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E550(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E650(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E740(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E830(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4E930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4EA40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4EAD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4EE30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F110(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F3F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F440(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F4C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F530(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F5D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F670(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F6C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F710(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F790(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F800(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F870(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F8E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F950(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4F9C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FA70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FB20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FC10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FC90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FD60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FE10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FE80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FF00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_4FF80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50000(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50080(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50100(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_501F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50260(RwUInt32 arg_0, type_44350 *arg_4);
void sub_502F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_503A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50410(RwUInt32 arg_0, type_44350 *arg_4);
void sub_504C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50620(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50760(RwUInt32 arg_0, type_44350 *arg_4);
void sub_507E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_508A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_509C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50AE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50CB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50D30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50DD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50E80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_50F80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_510C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_512E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_515B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51650(RwUInt32 arg_0, type_44350 *arg_4);
void sub_516F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51790(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51820(RwUInt32 arg_0, type_44350 *arg_4);
void sub_518C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51A10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51AB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51B30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51BE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51C80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51D00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51E20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51F10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_51FB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52050(RwUInt32 arg_0, type_44350 *arg_4);
void sub_520F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_521A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52260(RwUInt32 arg_0, type_44350 *arg_4);
void sub_522B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52310(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52390(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52440(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52500(RwUInt32 arg_0, type_44350 *arg_4);
void sub_525C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_526D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_527E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52900(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52A30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52B70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52C30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52F30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_52FF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_530B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53280(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53420(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53730(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53800(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53890(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53A00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53A60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53C10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53CA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53D50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53DF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53E80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_53F40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_540A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54110(RwUInt32 arg_0, type_44350 *arg_4);
void sub_541B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54250(RwUInt32 arg_0, type_44350 *arg_4);
void sub_542E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_545C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54640(RwUInt32 arg_0, type_44350 *arg_4);
void sub_547E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_548E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54980(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54AB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54B00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54C30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54D20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54E50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_54EC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55020(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55210(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55310(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55430(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55570(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55660(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55720(RwUInt32 arg_0, type_44350 *arg_4);
void sub_557B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55870(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55900(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55930(RwUInt32 arg_0, type_44350 *arg_4);
void sub_559D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55A70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55B20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55BD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55C20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55D10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55DD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55E40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55EC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55ED0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_55F60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56020(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56100(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_561E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56350(RwUInt32 arg_0, type_44350 *arg_4);
void sub_564C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56630(RwUInt32 arg_0, type_44350 *arg_4);
void sub_567A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56910(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56A80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56AF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56C10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56DC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_56F00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57040(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57180(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57320(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57460(RwUInt32 arg_0, type_44350 *arg_4);
void sub_575A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_576E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_577A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57860(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57920(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57A50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57B70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57CF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_57EE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58030(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58210(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58360(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58670(RwUInt32 arg_0, type_44350 *arg_4);
void sub_587F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58A20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58B20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58DD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58EC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_58F10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_590F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_592E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_594B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_595A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59690(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59730(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59770(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59880(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59960(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59A90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59BB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59CB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59DD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_59EF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A060(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A110(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A1C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A2C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A370(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A3E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A480(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A510(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A570(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A5B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A6C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5A9D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5AAE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5ABC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5AD70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5AE10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5AF50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5B080(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5B240(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5B8A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5BAA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5BBF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5BDA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5BED0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C040(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C1B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C320(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C4F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C6C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C890(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5C9B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CB00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CBD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CC80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CDC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CE90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5CF70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D050(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D4B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D650(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D710(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D780(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D7A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D7C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D7E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D850(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5D920(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5DB10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5DD00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5DDF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5DE90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5DFA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E0D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E180(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E230(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E2F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E3A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E4B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E5B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E610(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E6A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E730(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5E880(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5EB50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5EC30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5EE80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5EFC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5F4B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5F950(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FC30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FCA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FD90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FDF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FE50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FED0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FF50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_5FFB0(RwUInt32 arg_0, type_44350 *arg_4);
#ifdef CODFH_SP
void sp_sub_4EB80(RwUInt32 arg_0, type_44350 *arg_4);
void sp_sub_4EBD0(RwUInt32 arg_0, type_44350 *arg_4);
#endif
void sub_60030(RwUInt32 arg_0, type_44350 *arg_4);
void sub_600B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60130(RwUInt32 arg_0, type_44350 *arg_4);
void sub_601B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60230(RwUInt32 arg_0, type_44350 *arg_4);
void sub_602B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60330(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60440(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60490(RwUInt32 arg_0, type_44350 *arg_4);
void sub_604E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60630(RwUInt32 arg_0, type_44350 *arg_4);
void sub_606B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60770(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60830(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60850(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60910(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60960(RwUInt32 arg_0, type_44350 *arg_4);
void sub_609B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60A30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60BF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60D10(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60DB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60E50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60F00(RwUInt32 arg_0, type_44350 *arg_4);
void sub_60FB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61120(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61290(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61400(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61500(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61600(RwUInt32 arg_0, type_44350 *arg_4);
void sub_617D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61890(RwUInt32 arg_0, type_44350 *arg_4);
void sub_619B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61AB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61C80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61D50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61DF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_61E90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_620E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62310(RwUInt32 arg_0, type_44350 *arg_4);
void sub_623E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62450(RwUInt32 arg_0, type_44350 *arg_4);
void sub_624A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62520(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62570(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62610(RwUInt32 arg_0, type_44350 *arg_4);
void sub_626E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_627C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62840(RwUInt32 arg_0, type_44350 *arg_4);
void sub_628C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62940(RwUInt32 arg_0, type_44350 *arg_4);
void sub_629E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62A60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62B20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62DD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62EF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62F30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_62FB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63030(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63110(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63290(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63310(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63390(RwUInt32 arg_0, type_44350 *arg_4);
void sub_633F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_634E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63540(RwUInt32 arg_0, type_44350 *arg_4);
void sub_635A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63600(RwUInt32 arg_0, type_44350 *arg_4);
void sub_636A0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_637B0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63900(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63B40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63C30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63C90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63E50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63EC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63F50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_63FC0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64050(RwUInt32 arg_0, type_44350 *arg_4);
void sub_640C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64170(RwUInt32 arg_0, type_44350 *arg_4);
void sub_641E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64270(RwUInt32 arg_0, type_44350 *arg_4);
void sub_642E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64380(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64400(RwUInt32 arg_0, type_44350 *arg_4);
void sub_644E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64550(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64620(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64740(RwUInt32 arg_0, type_44350 *arg_4);
void sub_648C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64A40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64B60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64C40(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64D70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64DF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64E70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64EF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64F70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_64FF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65180(RwUInt32 arg_0, type_44350 *arg_4);
void sub_654C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65580(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65620(RwUInt32 arg_0, type_44350 *arg_4);
void sub_656D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_657D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65850(RwUInt32 arg_0, type_44350 *arg_4);
void sub_658D0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65950(RwUInt32 arg_0, type_44350 *arg_4);
void sub_659F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65A90(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65B30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65BD0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65C70(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65CF0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_65EB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66070(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66230(RwUInt32 arg_0, type_44350 *arg_4);
void sub_663F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66590(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66730(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66750(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66810(RwUInt32 arg_0, type_44350 *arg_4);
void sub_669F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66A80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66AE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66B50(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66BB0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66C20(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66C60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66D30(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66E60(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66EE0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66F80(RwUInt32 arg_0, type_44350 *arg_4);
void sub_66FA0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_67070(RwUInt32 arg_0, type_44350 *arg_4);
void sub_670C0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_670F0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_67110(RwUInt32 arg_0, type_44350 *arg_4);
void sub_67160(RwUInt32 arg_0, type_44350 *arg_4);
void sub_671E0(RwUInt32 arg_0, type_44350 *arg_4);
void sub_67200(RwUInt32 arg_0, type_44350 *arg_4);

// Its data definitions (PLAN M5), in the image's address order.
// 0x004276E0
type_4276E0 String1[] = {
    { "PrintInt", sub_443C0 },
    { "PrintFloat", sub_44400 },
    { "CreateThread", sub_44820 },
    { "CreateSoldier", sub_44900 },
    { "CameraShake", sub_44AD0 },
    { "ControllerShake", sub_449E0 },
    { "TimeScale", sub_44BB0 },
    { "PlayerShock", sub_44C70 },
    { "SetMotionBlur", sub_44DF0 },
    { "SetFogDistance", sub_44F30 },
    { "SetClipDistance", sub_44FC0 },
    { "SetFogType", sub_45050 },
    { "SetEntityScale", sub_45280 },
    { "SetRenderPriority", sub_450E0 },
    { "SetPriorityCollision", sub_451E0 },
    { "SetPerformanceMap", sub_46570 },
    { "SetPerformanceValue", sub_461E0 },
    { "SetHitDeathValue", sub_46280 },
    { "SetupAssassinationValues", sub_463C0 },
    { "SetSpecialIdlePerformanceValue", sub_46320 },
    { "GetPerformanceValue", sub_464F0 },
    { "GetMyTriggerPointer", sub_45720 },
    { "SetMyTriggerActionIcon", sub_45A50 },
    { "SetMyTriggerPosition", sub_45AF0 },
    { "RestoreMyTriggerPosition", sub_45C60 },
    { "SetPerformanceID", sub_46680 },
    { "GetLastHitLocation", sub_46B50 },
    { "GetPrimaryAnimationDuration", sub_45540 },
    { "SetFadeOut", sub_455A0 },
    { "SetFadeLevel", sub_45610 },
    { "SetMyWidthHeight", sub_45680 },
    { "PlayHitDeathAnim", sub_46720 },
    { "PlayHitDeathAnimDefaultData", sub_46840 },
    { "PlayCurrentPerformance", sub_46BC0 },
    { "PlaySpecialIdlePerformance", sub_46C20 },
    { "PlayAlarmCrankPerformance", sub_47C20 },
    { "PlayPickUpMMGPerformance", sub_47A20 },
    { "PlayCoverPointRegistrationPerformance", sub_46C80 },
    { "GetMyMMGMinBurstLength", sub_47150 },
    { "GetMyMMGMaxBurstLength", sub_471D0 },
    { "GetMyMMGMinPauseLength", sub_47250 },
    { "GetMyMMGMaxPauseLength", sub_472D0 },
    { "GotoPointUsingRegistration", sub_48DA0 },
    { "WillTransitionPlay", sub_47930 },
    { "SnapToCover", sub_46D60 },
    { "AttachToMountedWeapon", sub_473C0 },
    { "DetachFromMountedWeapon", sub_474E0 },
    { "AreWeUsingAMountedWeapon", sub_46E40 },
    { "IsPlayerUsingAMountedWeapon", sub_46EF0 },
    { "SetMyMMGToFireEvenIfICantSeeTarget", sub_46F40 },
    { "SetMyMMGYawAndPitch", sub_46FE0 },
    { "AttachProp", sub_47560 },
    { "AttachPropEx", sub_477A0 },
    { "DetachProp", sub_47700 },
    { "ResetNPCMountedWeaponAimMatrix", sub_47F00 },
    { "MountedWeaponReloaded", sub_47350 },
    { "DisablePerformances", sub_481C0 },
    { "SetStarStatus", sub_48230 },
    { "SetSceneMap", sub_48A10 },
    { "GetThisStateMachinePointer", sub_45FD0 },
    { "GetMyAIObjectPointer", sub_45FF0 },
    { "GetEntityHandle", sub_46040 },
    { "AssertValue", sub_442D0 },
    { "CreateMyChild", sub_453F0 },
    { "DestroySelf", sub_454A0 },
    { "CreateTank", sub_44970 },
    { "TimeToTicks", sub_44ED0 },
    { "GetVisionRange", sub_49080 },
    { "GetWeaponsMinMediumRange", sub_490D0 },
    { "CancelGrenadeThrowPoint", sub_49D10 },
    { "SetGrenadeThrowPoint", sub_49D70 },
    { "OverrideNPCGrenadeTimer", sub_49C90 },
    { "GetWeaponsMinLongRange", sub_49120 },
    { "GetWeaponsTooCloseForComfortRange", sub_49170 },
    { "GetWeaponsStandMeleeRange", sub_491C0 },
    { "GetWeaponsLungeMeleeRange", sub_49270 },
    { "GetWeaponsRunMeleeRange", sub_49320 },
    { "GetWeaponIsBoltActionRifle", sub_493D0 },
    { "RegisterDistanceCheck", sub_4A580 },
    { "RegisterDistanceCheckMsg", sub_4A6F0 },
    { "UnregisterDistanceCheck", sub_4A8B0 },
    { "UnregisterDistanceCheckPtr", sub_4A8F0 },
    { "DistanceToTarget", sub_4A960 },
    { "IHaveATarget", sub_4AB20 },
    { "GetNumberOfRestarts", sub_66730 },
    { "PlayParticleSystemAtXYZ", sub_4AB90 },
    { "SpawnParticle", sub_4BBE0 },
    { "SpawnParticleAtPosition", sub_4BAA0 },
    { "SpawnParticleSpawner", sub_4AF10 },
    { "KillParticleSpawner", sub_4B0B0 },
    { "SwitchToDestroyedClump", sub_4B0F0 },
    { "EnableWeaponRender", sub_4B150 },
    { "SetRenderPartState", sub_4B220 },
    { "GetRenderPartState", sub_4B300 },
    { "SetRenderPartStateByName", sub_4B3A0 },
    { "CreateExplosionZone", sub_4B490 },
    { "GetSquadLeader", sub_4BE70 },
    { "SetSquadLeader", sub_4BEF0 },
    { "SetAIMode", sub_4BFA0 },
    { "GetAIMode", sub_4C020 },
    { "SetAIFlag", sub_4C080 },
    { "GetAIFlag", sub_4C150 },
    { "ClearAIFlag", sub_4C1D0 },
    { "SetAIParam", sub_4C2A0 },
    { "FindAStarPathToAIObj", sub_4EAD0 },
    { "FindAStarPathToPathNode", sub_4EE30 },
    { "FindAStarPathToPoint", sub_4F110 },
    { "GetSceneActionMsg", sub_48B10 },
    { "SetSceneValue", sub_48B80 },
    { "PlayCurrentScene", sub_48C10 },
    { "GetSceneActionCount", sub_49040 },
    { "GetMyTarget", sub_4C4E0 },
    { "SetMyTarget", sub_4C590 },
    { "ClearMyTarget", sub_4C670 },
    { "GetTargetPosture", sub_4E930 },
    { "GetAttackStandPosture", sub_62610 },
    { "GetTargetType", sub_4EA40 },
    { "GetManeuverType", sub_4C3E0 },
    { "SetManeuverType", sub_4C340 },
    { "SetManeuverState", sub_4C460 },
    { "ClearFireAndMovementPoint", sub_540A0 },
    { "DisableFireAndMovement", sub_54110 },
    { "SetFireAndMovementExclusionEnemyDistance", sub_541B0 },
    { "SetFireAndMovementPointFromName", sub_53F40 },
    { "GetAIControl", sub_4F3F0 },
    { "SetAIControl", sub_4F440 },
    { "GetHitPoints", sub_4F4C0 },
    { "SetHitPoints", sub_4F530 },
    { "IncrementHitPoints", sub_4F5D0 },
    { "GetDestructionID", sub_4F6C0 },
    { "GetDamageLevel", sub_4F670 },
    { "SetDamageLevel", sub_4F710 },
    { "DotProductVectors", sub_45CD0 },
    { "CrossProductVectorComponent", sub_45E00 },
    { "VehicleInProximity", sub_507E0 },
    { "VehicleAttachEntity", sub_508A0 },
    { "VehicleAttachEntityToMountedWeapon", sub_509C0 },
    { "VehicleAttachPlayerPassenger", sub_50AE0 },
    { "VehicleGetAttachedEntity", sub_50D30 },
    { "VehicleGetPlayerPassenger", sub_50D30 },
    { "VehicleGetPlayerPosture", sub_50CB0 },
    { "PlayerExitVehicleTransition", sub_510C0 },
    { "PlayerEnterVehicleTransition", sub_512E0 },
    { "VehicleSetEngine", sub_515B0 },
    { "VehicleSetMaxThrottle", sub_51650 },
    { "VehicleSetMaxSpeed", sub_516F0 },
    { "VehicleSetCruiseSpeed", sub_51790 },
    { "VehicleGetHatchState", sub_51820 },
    { "VehicleSetHatchState", sub_518C0 },
    { "VehicleMountedWeaponGetAttachedEntity", sub_50DD0 },
    { "VehicleGetMountedWeapon", sub_50E80 },
    { "VehicleShowMountedWeapon", sub_50F80 },
    { "VehicleSetThrottle", sub_51A10 },
    { "VehicleGetVelocity", sub_51AB0 },
    { "VehicleSetBrake", sub_51B30 },
    { "VehicleEnablePhysics", sub_51BE0 },
    { "VehicleTrigger_GetMyName", sub_51C80 },
    { "SoldierEntity_GetMyVehiclesName", sub_51D00 },
    { "SoldierTrigger_GetMyVehiclesName", sub_51E20 },
    { "VehicleSetSteering", sub_51F10 },
    { "VehicleSecondaryTurn", sub_51FB0 },
    { "VehicleSecondaryPitch", sub_52050 },
    { "VehicleFireWeapon", sub_520F0 },
    { "VehicleEnableTurretTrack", sub_521A0 },
    { "VehicleDisableTurretTrack", sub_52260 },
    { "VehicleGetDeathTask", sub_522B0 },
    { "VehicleSetGimpLevel", sub_52310 },
    { "SetVehicleWeaponDisabled", sub_52390 },
    { "SetGravity", sub_4F790 },
    { "SetEnvCollisionNotification", sub_4F870 },
    { "SetWallCollisionNotification", sub_4F8E0 },
    { "SetGroundCollisionNotification", sub_4F950 },
    { "SetCollideWithFlags", sub_4F9C0 },
    { "ClearCollideWithFlags", sub_4FA70 },
    { "SetJiggleReactionOnNamedEntity", sub_4FB20 },
    { "SetJiggleReactionOnEntity", sub_4FC10 },
    { "SetNoFallThroughWorld", sub_4F800 },
    { "SetVelocity", sub_4FC90 },
    { "ScaleVelocity", sub_4FD60 },
    { "GetVelocityMagnitude", sub_4FE10 },
    { "GetCollisionWidth", sub_669F0 },
    { "OrientToCoverPoint", sub_52440 },
    { "OrientToCoverPointImmediate", sub_52500 },
    { "GetCoverPointPeekFlags", sub_525C0 },
    { "GetCoverPointType", sub_526D0 },
    { "SetCoverPoint", sub_52B70 },
    { "SetCoverPointFromName", sub_52C30 },
    { "SetArrivedAtCoverPoint", sub_52F30 },
    { "ClearCoverPoint", sub_52FF0 },
    { "IsCoverSafeFromGrenade", sub_530B0 },
    { "IsConnectedCorner", sub_527E0 },
    { "IsConnectedCornerOccupied", sub_52900 },
    { "SetConnectedCornerOccupied", sub_52A30 },
    { "CanSeeTarget", sub_53170 },
    { "IsFacingTarget", sub_53280 },
    { "SetMyDistanceFromTarget", sub_53420 },
    { "SetMyPosition", sub_57A50 },
    { "SetMyOrientation", sub_57EE0 },
    { "RotateMyOrientation", sub_4D9B0 },
    { "RideVehicle", sub_58030 },
    { "StopRidingVehicle", sub_58210 },
    { "RestartLevel", sub_5D780 },
    { "GetGameFrame", sub_5D7C0 },
    { "QuitLevel", sub_5D7A0 },
    { "QuitAndLoadNextLevel", sub_5D7E0 },
    { "EnableEndLevelTrigger", sub_5D850 },
    { "DisableNamedCoverPoint", sub_5D920 },
    { "EnableNamedPathNode", sub_5DD00 },
    { "EnableNamedCoverPoint", sub_5DB10 },
    { "EfuncPlaySound", sub_5E880 },
    { "EfuncPlaySoundAndFacialAnim", sub_5EB50 },
    { "EfuncPlaySoundOnNamedEntity", sub_5EC30 },
    { "EfuncPlaySoundAndFacialAnimOnNamedEntity", sub_5EE80 },
    { "EfuncPlayIndexSound", sub_5EFC0 },
    { "EfuncPlayIndexSoundOnNamedEntity", sub_5F4B0 },
    { "PrimeAudioStream", sub_5E730 },
    { "StartPrimedAudioStream", sub_5E6A0 },
    { "FadeSubstreamVolume", sub_5F950 },
    { "RenderFadeOut", sub_44D00 },
    { "RenderFadeIn", sub_44DA0 },
    { "SoundStillPlaying", sub_5FC30 },
    { "AttachToEntity", sub_58360 },
    { "DetachFromEntity", sub_58670 },
    { "GetUniqueNumber", sub_53730 },
    { "RandRange", sub_53800 },
    { "RandRangeFloat", sub_53890 },
    { "SetCollision", sub_4FE80 },
    { "SetEnvironmentCollision", sub_4FF00 },
    { "SetNoRender", sub_50000 },
    { "SetEntityCollision", sub_4FF80 },
    { "SetFiring", sub_50080 },
    { "InfiniteAmmoClip", sub_50100 },
    { "AllowFiring", sub_50170 },
    { "GetSuppressed", sub_501F0 },
    { "GetAttitude", sub_50260 },
    { "SetEngineAttitude", sub_502F0 },
    { "SetTriggerCollision", sub_503A0 },
    { "SetTriggerProximityChecks", sub_50410 },
    { "IsNamedEntityInTrigger", sub_504C0 },
    { "GetNumberOfObjectsInTrigger", sub_50620 },
    { "SetAllowTargetLOSLoss", sub_50760 },
    { "RegisterAStarCheck", sub_53A60 },
    { "UnRegisterAStarCheck", sub_53C10 },
    { "IsPathBlocked", sub_53CA0 },
    { "IsPathBlockedWhileStrafing", sub_53D50 },
    { "SuggestManeuver", sub_53DF0 },
    { "ForceManeuver", sub_53E80 },
    { "GetStartState", sub_54250 },
    { "SetDeadFlag", sub_55DD0 },
    { "SetCollisionNotifyFlag", sub_55E40 },
    { "SetDoorPathNodeState", sub_542E0 },
    { "SetAnimatedBGEntityType", sub_545C0 },
    { "AttachPlayerToAnimatedBGEntity", sub_54640 },
    { "AnimatedBGEntityAttachPlayerToMountedWeapon", sub_547E0 },
    { "AnimatedBGEntityMountedWeaponGetAttachedPlayer", sub_548E0 },
    { "SendFlying", sub_54980 },
    { "DestroyParticle", sub_4BCF0 },
    { "SpecialCCESSPoolCreation", sub_4BD70 },
    { "ClearCCESSPoolTriggers", sub_4BE20 },
    { "SwapToDestroyedVersion", sub_54AB0 },
    { "RegisterTimer", sub_53930 },
    { "UnregisterTimerByMessage", sub_53A00 },
    { "ToggleCCESSPoolCreation", sub_55A70 },
    { "SetCCESSPoolManager", sub_55B20 },
    { "SetNumSpawnableEntities", sub_55D10 },
    { "SetCCESSPoolManagerState", sub_55BD0 },
    { "ChangeCCESSPoolSize", sub_55C20 },
    { "PlaySound", sub_55900 },
    { "LockPlayerMovement", sub_55930 },
    { "SetPlayerState", sub_559D0 },
    { "DropPickup", sub_55EC0 },
    { "DropGrenadeAtLocationXYZ", sub_495F0 },
    { "PZ_Manipulate", sub_54B00 },
    { "PZ_SetUserData", sub_54C30 },
    { "PG_ManipulateProjectileGenerator", sub_55020 },
    { "PG_SetSplinePathFromName", sub_54EC0 },
    { "PG_SetParentAndAttachPoint", sub_54D20 },
    { "PG_DetatchFromParent", sub_54E50 },
    { "PG_TargetObjectByScript", sub_55210 },
    { "PG_TargetNamedObjectByScript", sub_55310 },
    { "PG_TargetPoint", sub_55430 },
    { "PG_TargetNamedPoint", sub_55570 },
    { "PG_EnableFiringStages", sub_55660 },
    { "PG_TargetDefault", sub_55720 },
    { "PG_EnableLOSCheck", sub_557B0 },
    { "PG_ForcedFire", sub_55870 },
    { "GetTaskReturnRegister", sub_46120 },
    { "GetWakeUpMessageID", sub_46180 },
    { "Custom_GetStartMessage", sub_55ED0 },
    { "Custom_GetSceneID", sub_55F60 },
    { "Custom_SendMessages", sub_56020 },
    { "Custom_SetObject", sub_56100 },
    { "Custom_SetAnimatedObject", sub_56170 },
    { "GetAttachPointXFromNamedEntity", sub_561E0 },
    { "GetAttachPointYFromNamedEntity", sub_56350 },
    { "GetAttachPointZFromNamedEntity", sub_564C0 },
    { "GetAttachPointOrientationXFromNamedEntity", sub_56630 },
    { "GetAttachPointOrientationYFromNamedEntity", sub_567A0 },
    { "GetAttachPointOrientationZFromNamedEntity", sub_56910 },
    { "SetCrewAttachPosition", sub_56A80 },
    { "SetFiveWayBlend", sub_48290 },
    { "SetEntityToFollow", sub_4C770 },
    { "GetEntityToFollow", sub_4C6D0 },
    { "FireWeaponXTimes", sub_4C860 },
    { "FireWeaponContinuous", sub_4C930 },
    { "SetHeadTrack", sub_484B0 },
    { "SetTurnMode", sub_48570 },
    { "GetTurnAmount", sub_48800 },
    { "GetTerrainAngle", sub_488D0 },
    { "GetEntityFromName", sub_56AF0 },
    { "GetPositionXFromName", sub_56DC0 },
    { "GetPositionYFromName", sub_56F00 },
    { "GetPositionZFromName", sub_57040 },
    { "GetOffsetPositionXFromAIObj", sub_60FB0 },
    { "GetOffsetPositionYFromAIObj", sub_61120 },
    { "GetOffsetPositionZFromAIObj", sub_61290 },
    { "SetupGotoPoint", sub_57180 },
    { "GetOrientationXFromName", sub_57320 },
    { "GetOrientationYFromName", sub_57460 },
    { "GetOrientationZFromName", sub_575A0 },
    { "GetOrientationXFromAIObj", sub_576E0 },
    { "GetOrientationYFromAIObj", sub_577A0 },
    { "GetOrientationZFromAIObj", sub_57860 },
    { "SetupMatchOrientation", sub_57920 },
    { "IsNameValid", sub_56C10 },
    { "GetDodgeDirection", sub_587F0 },
    { "CheckAttackPostureTransition", sub_58B20 },
    { "SetPickup", sub_58A20 },
    { "SetPlayerBuddy", sub_58DD0 },
    { "SetBuddyHealthType", sub_58EC0 },
    { "GetMyWeaponGroupType", sub_49420 },
    { "IsMyWeaponOutOfAmmo", sub_49470 },
    { "ForceMyWeaponToReload", sub_494C0 },
    { "SetAdvancedShotLocation", sub_49500 },
    { "DoIHaveGrenades", sub_49590 },
    { "DoIHaveAGrenadeInHand", sub_49970 },
    { "DropGrenade", sub_49A00 },
    { "ShouldIThrowAGrenade", sub_49A50 },
    { "ShouldIDoTheAssaultWalk", sub_49AF0 },
    { "ShouldIMeleeAttack", sub_4A0F0 },
    { "TurnPlayerWeaponOnorOff", sub_4A180 },
    { "TurnCrosshairOnorOff", sub_4A210 },
    { "SetPlayerWeapon", sub_4A350 },
    { "GivePlayerAmmo", sub_4A350 },
    { "RemovePlayerWeapon", sub_4A350 },
    { "RequestToStreamPlayerWeapon", sub_4A2E0 },
    { "IsPlayerWeaponStreamed", sub_4A270 },
    { "GivePlayerInventoryItem", sub_4A420 },
    { "RequestAIAction_RetreatFromTarget", sub_4C9E0 },
    { "BitAnd", sub_44440 },
    { "BitOr", sub_444C0 },
    { "BitNot", sub_44540 },
    { "BitLShift", sub_44590 },
    { "BitRShift", sub_44610 },
    { "Modulo", sub_44690 },
    { "Fabs", sub_44710 },
    { "Abs", sub_447D0 },
    { "Sqrt", sub_44770 },
    { "CompareGodalls", sub_59690 },
    { "ReturnNegGodID", sub_59730 },
    { "RequestAIAction_PursueTarget", sub_4CA50 },
    { "RequestAIAction_AttackFromCover", sub_4CAC0 },
    { "SetTaskCommand_GoToAttachPoint", sub_58F10 },
    { "SetTaskCommand_TurnToAttachPoint", sub_590F0 },
    { "SetTaskCommand_TeleportToAttachPoint", sub_592E0 },
    { "TeleportToNamedObject", sub_57B70 },
    { "TeleportNamedObjectToNamedPoint", sub_57CF0 },
    { "Vehicle_AllowAttack", sub_594B0 },
    { "Vehicle_AllowMove", sub_595A0 },
    { "Vehicle_IncrementRiderCount", sub_59770 },
    { "Vehicle_DecrementRiderCount", sub_59960 },
    { "FlakVehicle_SetCrewMember", sub_59A90 },
    { "FlakVehicle_GetCrewMember", sub_59BB0 },
    { "FlakVehicle_SetCrewMemberStatus", sub_59CB0 },
    { "FlakVehicle_ClearCrewMember", sub_59DD0 },
    { "Vehicle_IncrementIncomingRiderCount", sub_59880 },
    { "Vehicle_DecrementIncomingRiderCount", sub_59EF0 },
    { "Vehicle_GetVehicleEntityHandle", sub_46040 },
    { "NamedEntityExists", sub_5A060 },
    { "GetRidingVehicle", sub_5A110 },
    { "SetRestrictedTankTargetZone", sub_5A1C0 },
    { "ClearRestrictedTankTargetZone", sub_5A2C0 },
    { "GetTankHFOV", sub_5A370 },
    { "SetTankHFOV", sub_5A3E0 },
    { "GetPreferredAttackRange", sub_5A480 },
    { "DontWaitForNoRenderToDeleteMe", sub_5A510 },
    { "AttachRingMountGunToGunner", sub_5A6C0 },
    { "BlockFacing", sub_5A5B0 },
    { "HasDefaultSplinePath", sub_5AF50 },
    { "SetSplinePathFromName", sub_5B240 },
    { "SetSplineEndPosition", sub_5B8A0 },
    { "DivorceSplinePath", sub_5B080 },
    { "GetClosestPositionOnSpline", sub_5BAA0 },
    { "GetClosestPositionFromPlayerOnSpline", sub_5BBF0 },
    { "GetSplineLength", sub_5BDA0 },
    { "GetSplinePositionX", sub_5BED0 },
    { "GetSplinePositionY", sub_5C040 },
    { "GetSplinePositionZ", sub_5C1B0 },
    { "GetSplinePositionXFromName", sub_5C320 },
    { "GetSplinePositionYFromName", sub_5C4F0 },
    { "GetSplinePositionZFromName", sub_5C6C0 },
    { "SetSplinePosition", sub_5C890 },
    { "GetSplinePositionFromName", sub_5C9B0 },
    { "SetSplineIncrement", sub_5CB00 },
    { "GetSplineIncrement", sub_5CBD0 },
    { "GetSplineIncrementFromName", sub_5CC80 },
    { "SetSplineMovementByAnimation", sub_5CDC0 },
    { "SetSplineGoodToGo", sub_5CE90 },
    { "SetPointGoodToGo", sub_5CF70 },
    { "EnableCanShootCheckMessages", sub_4CB20 },
    { "EnableGrenadeHints", sub_4CBE0 },
    { "DisableGoGoGo", sub_4CC80 },
    { "FoundPointPathForGoGoGo", sub_4CCF0 },
    { "DidIJustGoGoGo", sub_4CD80 },
    { "FinishedGoGoGo", sub_4CE10 },
    { "GetTargetsCanShootStatus", sub_4CF30 },
    { "CanIShoot", sub_4CE80 },
    { "CanIDiveAwayFromGrenade", sub_4D170 },
    { "CanIDiveForward", sub_4CFA0 },
    { "PlayDiveToPoint", sub_4D090 },
    { "CanGetCoverFromGrenade", sub_4D660 },
    { "CanGetPointFromGrenade", sub_4D720 },
    { "SetMoveOutOfWayFattyPoint", sub_4D7F0 },
    { "GetContactType", sub_4D8B0 },
    { "EnableColorCodedName", sub_4D930 },
    { "CanIDiveAwayFromTank", sub_4DB20 },
    { "IsThreatenedByTank", sub_4E470 },
    { "GetDistanceFromGrenade", sub_4E550 },
    { "GetDistanceFromPoint", sub_4E650 },
    { "GetPlayerDistanceFromPoint", sub_4E740 },
    { "GetDistanceFromTank", sub_4E830 },
    { "LoadSoundBank", sub_5A9D0 },
    { "LoadAnimGroup", sub_5AAE0 },
    { "SetRestartAnimGroup", sub_5ABC0 },
    { "PlayFacialAnimation", sub_5AD70 },
    { "PlayFacialAnimationOnNamedEntity", sub_5AE10 },
    { "RequestSaveGame", sub_66F80 },
    { "SetPlayerBumpRadius", sub_62F30 },
    { "GetTransitionDistance", sub_5D050 },
    { "DoesNameHaveOrientation", sub_5D650 },
    { "PlayCurrentSceneAtNamedPoint", sub_48C70 },
    { "StopCurrentPerformance", sub_48170 },
    { "GetLastPerformanceTypePlayed", sub_5D710 },
    { "DoesSceneHaveTranstion", sub_5D4B0 },
    { "IsWithinDefendArea", sub_5DDF0 },
    { "IsPointWithinDefendArea", sub_5DE90 },
    { "IsTargetWithinDefendArea", sub_5DFA0 },
    { "SetupDefendAreaGotoPoint", sub_5E0D0 },
    { "SetupDefendAreaAnchorPosGotoPoint", sub_5E180 },
    { "SetDefendArea", sub_5E230 },
    { "SetDefendAreaCurrentPosition", sub_5E2F0 },
    { "SetDefendAreaCylinder", sub_5E3A0 },
    { "SetDefendAreaCylinderCurrentPosition", sub_5E4B0 },
    { "ClearDefendArea", sub_5E5B0 },
    { "GetDefendAreaRadius", sub_5E610 },
    { "AddObjective", sub_5FCA0 },
    { "RemoveObjective", sub_5FD90 },
    { "GetObjectiveFlags", sub_5FDF0 },
    { "SetObjectiveFlags", sub_5FE50 },
    { "ClearObjectiveFlags", sub_5FED0 },
    { "GetObjectiveCounter", sub_5FF50 },
#ifdef CODFH_SP // single player's counter commands are their own functions (SP .data 0x32066C)
    { "SetObjectiveCounter", sp_sub_4EB80 },
    { "ModifyObjectiveCounter", sp_sub_4EBD0 },
#else
    { "SetObjectiveCounter", sub_5FFB0 },
    { "ModifyObjectiveCounter", sub_5FFB0 },
#endif
    { "SetActivateMessage", sub_60030 },
    { "SetCompleteMessage", sub_600B0 },
    { "SetFailMessage", sub_60130 },
    { "SetIncrementCounterMessage", sub_601B0 },
    { "SetDecrementCounterMessage", sub_60230 },
    { "SetObjectiveNagTimer", sub_602B0 },
    { "SetObjectiveTarget", sub_60330 },
    { "PrintObjective", sub_60440 },
    { "EnableObjectiveTargetSystem", sub_60490 },
    { "SetObjectiveSplinePath", sub_604E0 },
    { "AddSubObjectiveTarget", sub_606B0 },
    { "ClearSubObjectiveTarget", sub_60770 },
    { "ClearAllSubObjectiveTargets", sub_60830 },
    { "SetAttackStandHoldCount", sub_62570 },
    { "DisplayHelpMessage", sub_60850 },
    { "ClearAllHelpMessages", sub_60960 },
    { "KillHelpMessage", sub_60910 },
    { "RequestClumpBankLoad", sub_4B820 },
    { "IsClumpBankLoaded", sub_4B870 },
    { "SetDefaultClumpBank", sub_4B8C0 },
    { "SetObjectiveLookaheadDistance", sub_60630 },
    { "IsLevelSectionLoaded", sub_4B770 },
    { "SetCheckPointRegister", sub_4B910 },
    { "GetCheckPointRegister", sub_4B990 },
    { "SetStartingSections", sub_4B9B0 },
    { "TakeCheckpointSnapshot", sub_4BA80 },
    { "GetLocalYawAngleToPathPoint", sub_609B0 },
    { "GetWorldYawAngleToTargetFrompPathPoint", sub_60A30 },
    { "SetVisionMultiplier", sub_60BF0 },
    { "GetTeam", sub_60D10 },
    { "GetPositionXFromAIObj", sub_60DB0 },
    { "GetPositionYFromAIObj", sub_60E50 },
    { "GetPositionZFromAIObj", sub_60F00 },
    { "GetHierarchyPositionXFromAIObj", sub_61400 },
    { "GetHierarchyPositionYFromAIObj", sub_61500 },
    { "GetHierarchyPositionZFromAIObj", sub_61600 },
    { "CanTurnToTurnLocation", sub_617D0 },
    { "CanTurnTo", sub_61890 },
    { "SetTurnLocationTo", sub_619B0 },
    { "SetTurnLocationOverrideTo", sub_61AB0 },
    { "ShouldITurnToPos", sub_61C80 },
    { "ShouldITurnToTurnLocation", sub_61D50 },
    { "ShouldITurnToTarget", sub_61DF0 },
    { "CanSee", sub_61E90 },
    { "CanPotentiallySee", sub_620E0 },
    { "GetCollisionDistanceToPoint", sub_62310 },
    { "SetPlayerPosture", sub_623E0 },
    { "GetPlayerPosture", sub_62450 },
    { "SetPosture", sub_624A0 },
    { "GetPosture", sub_62520 },
    { "SetFireAtNoTarget", sub_626E0 },
    { "IsValidAIObj", sub_627C0 },
    { "SetAlerted", sub_62940 },
    { "IsAlerted", sub_629E0 },
    { "SetThrobbing", sub_62840 },
    { "SetActionItem", sub_628C0 },
    { "RedSquareHax", sub_5A570 },
    { "SetCameraMode", sub_62A60 },
    { "SetCameraAlignTargetFromNamedPoint", sub_62B20 },
    { "SetCameraSplinePathFromName", sub_62DD0 },
    { "ResetCameraZoom", sub_62EF0 },
    { "EnableFrustumCheck", sub_67110 },
    { "GetPlayerEntity", sub_63290 },
    { "GetPlayerAIObject", sub_63310 },
    { "DisableAnimBlending", sub_63390 },
    { "GetClosestAlarmPoint", sub_62FB0 },
    { "GetClosestAlarmObject", sub_63110 },
    { "SetAlarmPathNodeOccupied", sub_63030 },
    { "SetHudVisible", sub_633F0 },
    { "Breakpoint", sub_634E0 },
    { "SetVehicleCoverPoint", sub_63540 },
    { "ClearVehicleCoverPoint", sub_635A0 },
    { "GetVehicleAIObjFromVehicleCoverPoint", sub_63600 },
    { "SetVehicleToFollow", sub_636A0 },
    { "RegisterEntityFollowed", sub_63B40 },
    { "UnRegisterEntityFollowed", sub_63C30 },
    { "SetCurrentEntityFollowed", sub_637B0 },
    { "SetCurrentEntityFollowedOnSpline", sub_63900 },
    { "SetCoverPointSearch", sub_63EC0 },
    { "GetCoverPointSearch", sub_63F50 },
    { "SetVehicleCoverPointSearch", sub_63FC0 },
    { "GetVehicleCoverPointSearch", sub_64050 },
    { "SetCoverPointSearchType", sub_640C0 },
    { "GetCoverPointSearchType", sub_64170 },
    { "SetCoverPointSearchRadius", sub_641E0 },
    { "GetEntityType", sub_642E0 },
    { "OccupyVehicleCoverpointSelected", sub_64380 },
    { "OccupyDefendAreaCoverPointSelected", sub_644E0 },
    { "IsDefendAreaSelectedBetter", sub_64270 },
    { "EnableVehicleCoverPoints", sub_64400 },
    { "GetAngularYDiffToObj", sub_63C90 },
    { "GetAIAction", sub_63E50 },
    { "DistanceToDestination", sub_64620 },
    { "DistanceToEnemy", sub_64740 },
    { "DistanceToEnemyDeadOrAlive", sub_648C0 },
    { "SetUpdateCallBack", sub_64550 },
    { "GetDistanceFromObject", sub_64A40 },
    { "GetDistanceFromCurrentCoverPoint", sub_64B60 },
    { "IsWithinRangeOfObject", sub_64C40 },
    { "GetMyTriggerMetric", sub_457A0 },
    { "GetMyTriggerVectorComponent", sub_458A0 },
    { "PlayerStealthMessageActive", sub_64D70 },
    { "SetGimpVehicleMoveState", sub_64DF0 },
    { "SetGimpVehicleFireState", sub_64E70 },
    { "SetGimpVehicleMoveSpeed", sub_64EF0 },
    { "SetGimpVehicleRotSpeed", sub_64F70 },
    { "SetSplineOffsetXYZ", sub_64FF0 },
    { "SetSplineOffsetXYZIJK", sub_65180 },
    { "SetSplineOffsetMatrix", sub_654C0 },
    { "SetProceduralRollOnSpline", sub_65580 },
    { "GetMatrixFromAIObj", sub_65620 },
    { "GetMatrixFromName", sub_656D0 },
    { "GetGlobalRegister_AsInt", sub_657D0 },
    { "GetGlobalRegister_AsFloat", sub_65850 },
    { "GetGlobalRegister_AsOther", sub_658D0 },
    { "GetGlobalRegister_AsGodName", sub_65950 },
    { "SetGlobalRegister_AsInt", sub_659F0 },
    { "SetGlobalRegister_AsFloat", sub_65A90 },
    { "SetGlobalRegister_AsOther", sub_65B30 },
    { "SetGlobalRegister_AsGodName", sub_65BD0 },
    { "SetCanAlliesDamage", sub_65CF0 },
    { "SetCanEnemiesDamage", sub_65EB0 },
    { "SetCanBulletsDamage", sub_66070 },
    { "SetCanExplosionsDamage", sub_66230 },
    { "GetCanAlliesDamage", sub_663F0 },
    { "GetCanEnemiesDamage", sub_663F0 },
    { "GetCanBulletsDamage", sub_663F0 },
    { "GetCanExplosionsDamage", sub_66590 },
    { "GetNumberOfActiveObjects", sub_66750 },
    { "ShouldIContinueLeadingToPoint", sub_66810 },
    { "RemoveInterrupt", sub_65C70 },
    { "SetPlayerConfined", sub_66A80 },
    { "SetPlayerHealthPercentage", sub_66AE0 },
    { "DisablePlayerDamage", sub_66B50 },
    { "IsOnlyLiveOnce", sub_66BB0 },
    { "CausePlayerPainOnHUD", sub_66C20 },
    { "SetLadderMovement", sub_67160 },
    { "GetGameDifficulty", sub_671E0 },
    { "SetBombSiteInProximity", sub_66C60 },
    { "CreateBomb", sub_66D30 },
    { "DeclareBombSite", sub_66E60 },
    { "DeclareCaptureFlagBase", sub_66F80 },
    { "CreateFlag", sub_66F80 },
    { "SetCaptureFlagBaseInProximity", sub_66FA0 },
    { "FlagRenderTimeOut", sub_67070 },
    { "DeclareBombPlanted", sub_66EE0 },
    { "GetGameType", sub_670C0 },
    { "SDObjectivesComplete", sub_670F0 },
    { "GetWeaponType", sub_67200 },
    { 0, 0 },
};
// 0x00428A08
RwReal flt_428A08 = 30.0f;
// 0x00428A0C
RwReal flt_428A0C = 0.001f;
// 0x00428A10
RwReal flt_428A10 = 75.0f;
// 0x00428A14
RwReal flt_428A14 = 200.0f;
// 0x00428A18
RwReal flt_428A18 = 75.0f;
// 0x00428A1C
RwReal flt_428A1C = 250.0f;
// 0x00428A20
RwReal flt_428A20 = 75.0f;
// 0x00428A24
RwReal flt_428A24 = 250.0f;
// 0x00428A28
#ifdef CODFH_SP // file-static in single player: sub_5F950 keeps no store of it before the unk_248 load (SP 0x4E5A0)
static RwReal dword_428A28 = -1.0f;
#else
RwReal dword_428A28 = -1.0f;
#endif
// 0x00428A2C
#ifdef CODFH_SP // file-static in single player: sub_5F950 (SP 0x4E5A0) matches only with it and flt_439E70 static
static RwInt32 dword_428A2C = -1;
#else
RwInt32 dword_428A2C = -1;
#endif
// 0x00439940
RwInt32 dword_439940;
// 0x00439948
RwChar Buffer[1312];
// 0x00439E68
RwInt32 dword_439E68[2];
// 0x00439E70
#ifdef CODFH_SP // file-static in single player (as dword_428A2C)
static RwReal flt_439E70[2];
#else
RwReal flt_439E70[2];
#endif
// (Defined after the data: VC7.1 emits a unit's data definitions in reverse order, and
// the image has these constants before the data's texts.)
// 0x003CE9B0
extern const RwReal flt_3CE9B0 = 16.666666f;
#ifndef CODFH_SP // single player has neither unreferenced 0.01f: 0.1f follows 16.666666f (SP 0x2DC480)
// 0x003CE9B4
extern const RwReal flt_3CE9B4 = 0.01f;
// 0x003CE9B8
extern const RwReal flt_3CE9B8 = 0.01f;
#endif
// 0x003CE9BC
extern const RwReal flt_3CE9BC = 0.1f;
// End of its data definitions.




// The commands' table (sub_441B0 looks a name up in it), ended by an empty entry.

// Globals with constructors defined here (their initializers and exit
// functions at the end of .text).
type_439A48 dword_439A48[8];
// Its data (PLAN M5): literals, constants and tables where the image has them.
// match: ?flt_3CE9B0@@3MB @ 0x003CE9B0
// match: ?flt_3CE9B4@@3MB @ 0x003CE9B4
// match: ?flt_3CE9B8@@3MB @ 0x003CE9B8
// match: ?flt_3CE9BC@@3MB @ 0x003CE9BC
// match: ??_C@_0O@GHHMCIKC@GetWeaponType?$AA@ @ 0x003CE9C0
// match: ??_C@_0BF@CFBPCBJD@SDObjectivesComplete?$AA@ @ 0x003CE9D0
// match: ??_C@_0M@JNMFHEPP@GetGameType?$AA@ @ 0x003CE9E8
// match: ??_C@_0BD@MBBAJBNC@DeclareBombPlanted?$AA@ @ 0x003CE9F4
// match: ??_C@_0BC@GJFGMDMA@FlagRenderTimeOut?$AA@ @ 0x003CEA08
// match: ??_C@_0BO@JKPBOFIN@SetCaptureFlagBaseInProximity?$AA@ @ 0x003CEA1C
// match: ??_C@_0L@KGCPNDGC@CreateFlag?$AA@ @ 0x003CEA3C
// match: ??_C@_0BH@COFNJCBF@DeclareCaptureFlagBase?$AA@ @ 0x003CEA48
// match: ??_C@_0BA@PKCNHAJH@DeclareBombSite?$AA@ @ 0x003CEA60
// match: ??_C@_0L@DFHHNHGN@CreateBomb?$AA@ @ 0x003CEA70
// match: ??_C@_0BH@CGCHACJI@SetBombSiteInProximity?$AA@ @ 0x003CEA7C
// match: ??_C@_0BC@PJEKPAJK@GetGameDifficulty?$AA@ @ 0x003CEA94
// match: ??_C@_0BC@FHHKHCLI@SetLadderMovement?$AA@ @ 0x003CEAA8
// match: ??_C@_0BF@PCPHNEPJ@CausePlayerPainOnHUD?$AA@ @ 0x003CEABC
// match: ??_C@_0P@HKGFMCPJ@IsOnlyLiveOnce?$AA@ @ 0x003CEAD4
// match: ??_C@_0BE@NLJKBHAA@DisablePlayerDamage?$AA@ @ 0x003CEAE4
// match: ??_C@_0BK@KJHJGFBA@SetPlayerHealthPercentage?$AA@ @ 0x003CEAF8
// match: ??_C@_0BC@BAPOMMKN@SetPlayerConfined?$AA@ @ 0x003CEB14
// match: ??_C@_0BA@FEHFFNKP@RemoveInterrupt?$AA@ @ 0x003CEB28
// match: ??_C@_0BO@GCKPGOBP@ShouldIContinueLeadingToPoint?$AA@ @ 0x003CEB38
// match: ??_C@_0BJ@OAFKAMCE@GetNumberOfActiveObjects?$AA@ @ 0x003CEB58
// match: ??_C@_0BH@LDOKKFFK@GetCanExplosionsDamage?$AA@ @ 0x003CEB74
// match: ??_C@_0BE@IJOKLHKE@GetCanBulletsDamage?$AA@ @ 0x003CEB8C
// match: ??_C@_0BE@ECEJFHPA@GetCanEnemiesDamage?$AA@ @ 0x003CEBA0
// match: ??_C@_0BD@EHOLOLGA@GetCanAlliesDamage?$AA@ @ 0x003CEBB4
// match: ??_C@_0BH@LCMEICIF@SetCanExplosionsDamage?$AA@ @ 0x003CEBC8
// match: ??_C@_0BE@CHMBPHNI@SetCanBulletsDamage?$AA@ @ 0x003CEBE0
// match: ??_C@_0BE@OMGCBHIM@SetCanEnemiesDamage?$AA@ @ 0x003CEBF4
// match: ??_C@_0BD@LNMBNNII@SetCanAlliesDamage?$AA@ @ 0x003CEC08
// match: ??_C@_0BM@NJOOEEGG@SetGlobalRegister_AsGodName?$AA@ @ 0x003CEC1C
// match: ??_C@_0BK@BBDJEDPH@SetGlobalRegister_AsOther?$AA@ @ 0x003CEC38
// match: ??_C@_0BK@KKCCPJJP@SetGlobalRegister_AsFloat?$AA@ @ 0x003CEC54
// match: ??_C@_0BI@HPBMKOCA@SetGlobalRegister_AsInt?$AA@ @ 0x003CEC70
// match: ??_C@_0BM@MEGGGBMC@GetGlobalRegister_AsGodName?$AA@ @ 0x003CEC88
// match: ??_C@_0BK@JBPPIOFB@GetGlobalRegister_AsOther?$AA@ @ 0x003CECA4
// match: ??_C@_0BK@CKOEDEDJ@GetGlobalRegister_AsFloat?$AA@ @ 0x003CECC0
// match: ??_C@_0BI@GJHBEPEC@GetGlobalRegister_AsInt?$AA@ @ 0x003CECDC
// match: ??_C@_0BC@KCPCHABL@GetMatrixFromName?$AA@ @ 0x003CECF4
// match: ??_C@_0BD@BKEGBPJB@GetMatrixFromAIObj?$AA@ @ 0x003CED08
// match: ??_C@_0BK@CKOKPLNL@SetProceduralRollOnSpline?$AA@ @ 0x003CED1C
// match: ??_C@_0BG@LOCBEBLL@SetSplineOffsetMatrix?$AA@ @ 0x003CED38
// match: ??_C@_0BG@PEFFAEFO@SetSplineOffsetXYZIJK?$AA@ @ 0x003CED50
// match: ??_C@_0BD@BGCCFCDH@SetSplineOffsetXYZ?$AA@ @ 0x003CED68
// match: ??_C@_0BH@EOGDPGIO@SetGimpVehicleRotSpeed?$AA@ @ 0x003CED7C
// match: ??_C@_0BI@HMBGCLFP@SetGimpVehicleMoveSpeed?$AA@ @ 0x003CED94
// match: ??_C@_0BI@NLLGOEJ@SetGimpVehicleFireState?$AA@ @ 0x003CEDAC
// match: ??_C@_0BI@CALOCMO@SetGimpVehicleMoveState?$AA@ @ 0x003CEDC4
// match: ??_C@_0BL@HHNAFFMJ@PlayerStealthMessageActive?$AA@ @ 0x003CEDDC
// match: ??_C@_0BM@KCKNEFNF@GetMyTriggerVectorComponent?$AA@ @ 0x003CEDF8
// match: ??_C@_0BD@DLKABBHP@GetMyTriggerMetric?$AA@ @ 0x003CEE14
// match: ??_C@_0BG@FJPNGIGB@IsWithinRangeOfObject?$AA@ @ 0x003CEE28
// match: ??_C@_0CB@BMDKCNOC@GetDistanceFromCurrentCoverPoint@ @ 0x003CEE40
// match: ??_C@_0BG@ICEMMJEA@GetDistanceFromObject?$AA@ @ 0x003CEE64
// match: ??_C@_0BC@JMOGDIKP@SetUpdateCallBack?$AA@ @ 0x003CEE7C
// match: ??_C@_0BL@CPBODGKG@DistanceToEnemyDeadOrAlive?$AA@ @ 0x003CEE90
// match: ??_C@_0BA@MLHKDECI@DistanceToEnemy?$AA@ @ 0x003CEEAC
// match: ??_C@_0BG@CCGCIADE@DistanceToDestination?$AA@ @ 0x003CEEBC
// match: ??_C@_0M@HPFOIBHO@GetAIAction?$AA@ @ 0x003CEED4
// match: ??_C@_0BF@JMFPNKGB@GetAngularYDiffToObj?$AA@ @ 0x003CEEE0
// match: ??_C@_0BJ@PLPOCFHF@EnableVehicleCoverPoints?$AA@ @ 0x003CEEF8
// match: ??_C@_0BL@LEJNPNA@IsDefendAreaSelectedBetter?$AA@ @ 0x003CEF14
// match: ??_C@_0CD@EOLLINBC@OccupyDefendAreaCoverPointSelect@ @ 0x003CEF30
// match: ??_C@_0CA@IBMIMIFD@OccupyVehicleCoverpointSelected?$AA@ @ 0x003CEF54
// match: ??_C@_0O@JHKPHJHG@GetEntityType?$AA@ @ 0x003CEF74
// match: ??_C@_0BK@PPOCDGNA@SetCoverPointSearchRadius?$AA@ @ 0x003CEF84
// match: ??_C@_0BI@HPFGFDFC@GetCoverPointSearchType?$AA@ @ 0x003CEFA0
// match: ??_C@_0BI@GJDLLCDA@SetCoverPointSearchType?$AA@ @ 0x003CEFB8
// match: ??_C@_0BL@NNAJCIO@GetVehicleCoverPointSearch?$AA@ @ 0x003CEFD0
// match: ??_C@_0BL@DCOFFCJO@SetVehicleCoverPointSearch?$AA@ @ 0x003CEFEC
// match: ??_C@_0BE@FKJMNJMM@GetCoverPointSearch?$AA@ @ 0x003CF008
// match: ??_C@_0BE@PELHJJLA@SetCoverPointSearch?$AA@ @ 0x003CF01C
// match: ??_C@_0CB@PLEKHCAN@SetCurrentEntityFollowedOnSpline@ @ 0x003CF030
// match: ??_C@_0BJ@JDIJBINN@SetCurrentEntityFollowed?$AA@ @ 0x003CF054
// match: ??_C@_0BJ@OKJMGDNP@UnRegisterEntityFollowed?$AA@ @ 0x003CF070
// match: ??_C@_0BH@HGMFEFFH@RegisterEntityFollowed?$AA@ @ 0x003CF08C
// match: ??_C@_0BD@NEPCKHBI@SetVehicleToFollow?$AA@ @ 0x003CF0A4
// match: ??_C@_0CF@ENHEKHMI@GetVehicleAIObjFromVehicleCoverP@ @ 0x003CF0B8
// match: ??_C@_0BH@BBIIDKPN@ClearVehicleCoverPoint?$AA@ @ 0x003CF0E0
// match: ??_C@_0BF@PBACNID@SetVehicleCoverPoint?$AA@ @ 0x003CF0F8
// match: ??_C@_0L@DEJAMIEF@Breakpoint?$AA@ @ 0x003CF110
// match: ??_C@_0O@GAEBNGGM@SetHudVisible?$AA@ @ 0x003CF11C
// match: ??_C@_0BJ@EHIJKLLJ@SetAlarmPathNodeOccupied?$AA@ @ 0x003CF12C
// match: ??_C@_0BG@CPGKALHK@GetClosestAlarmObject?$AA@ @ 0x003CF148
// match: ??_C@_0BF@EDGMPIHP@GetClosestAlarmPoint?$AA@ @ 0x003CF160
// match: ??_C@_0BE@CIMIGJAK@DisableAnimBlending?$AA@ @ 0x003CF178
// match: ??_C@_0BC@IKPOHOI@GetPlayerAIObject?$AA@ @ 0x003CF18C
// match: ??_C@_0BA@MGFIBGAG@GetPlayerEntity?$AA@ @ 0x003CF1A0
// match: ??_C@_0BD@OJOGIBGE@EnableFrustumCheck?$AA@ @ 0x003CF1B0
// match: ??_C@_0BA@PBFDILCE@ResetCameraZoom?$AA@ @ 0x003CF1C4
// match: ??_C@_0BM@ENIODEB@SetCameraSplinePathFromName?$AA@ @ 0x003CF1D4
// match: ??_C@_0CD@COPENKOE@SetCameraAlignTargetFromNamedPoi@ @ 0x003CF1F0
// match: ??_C@_0O@CJDLPJHK@SetCameraMode?$AA@ @ 0x003CF214
// match: ??_C@_0N@FCEAIBFB@RedSquareHax?$AA@ @ 0x003CF224
// match: ??_C@_0O@GOLCKIFJ@SetActionItem?$AA@ @ 0x003CF234
// match: ??_C@_0N@PGBLFOHL@SetThrobbing?$AA@ @ 0x003CF244
// match: ??_C@_09GOCOBNPE@IsAlerted?$AA@ @ 0x003CF254
// match: ??_C@_0L@DGHPPBNM@SetAlerted?$AA@ @ 0x003CF260
// match: ??_C@_0N@LLLCJPDM@IsValidAIObj?$AA@ @ 0x003CF26C
// match: ??_C@_0BC@JOCNJLN@SetFireAtNoTarget?$AA@ @ 0x003CF27C
// match: ??_C@_0L@ELKIJKEK@GetPosture?$AA@ @ 0x003CF290
// match: ??_C@_0L@FFIHCNAD@SetPosture?$AA@ @ 0x003CF29C
// match: ??_C@_0BB@FCJPLNDF@GetPlayerPosture?$AA@ @ 0x003CF2A8
// match: ??_C@_0BB@DGMGADIH@SetPlayerPosture?$AA@ @ 0x003CF2BC
// match: ??_C@_0BM@LNDKAPPL@GetCollisionDistanceToPoint?$AA@ @ 0x003CF2D0
// match: ??_C@_0BC@OCEOPKFL@CanPotentiallySee?$AA@ @ 0x003CF2EC
// match: ??_C@_06HNPEGMND@CanSee?$AA@ @ 0x003CF300
// match: ??_C@_0BE@NOKBJDGD@ShouldITurnToTarget?$AA@ @ 0x003CF308
// match: ??_C@_0BK@BNPBBMJH@ShouldITurnToTurnLocation?$AA@ @ 0x003CF31C
// match: ??_C@_0BB@DAHDPBGD@ShouldITurnToPos?$AA@ @ 0x003CF338
// match: ??_C@_0BK@LPLIIFFD@SetTurnLocationOverrideTo?$AA@ @ 0x003CF34C
// match: ??_C@_0BC@OADEFNIH@SetTurnLocationTo?$AA@ @ 0x003CF368
// match: ??_C@_09LKMPJPAJ@CanTurnTo?$AA@ @ 0x003CF37C
// match: ??_C@_0BG@CFBAKIOP@CanTurnToTurnLocation?$AA@ @ 0x003CF388
// match: ??_C@_0BP@LDOGPIAE@GetHierarchyPositionZFromAIObj?$AA@ @ 0x003CF3A0
// match: ??_C@_0BP@CKAEJOAF@GetHierarchyPositionYFromAIObj?$AA@ @ 0x003CF3C0
// match: ??_C@_0BP@OLIKEBMF@GetHierarchyPositionXFromAIObj?$AA@ @ 0x003CF3E0
// match: ??_C@_0BG@PPFOGPEF@GetPositionZFromAIObj?$AA@ @ 0x003CF400
// match: ??_C@_0BG@GGLMAJEE@GetPositionYFromAIObj?$AA@ @ 0x003CF418
// match: ??_C@_0BG@KHDCNGIE@GetPositionXFromAIObj?$AA@ @ 0x003CF430
// match: ??_C@_07KIJFBNDA@GetTeam?$AA@ @ 0x003CF448
// match: ??_C@_0BE@KCMANDJ@SetVisionMultiplier?$AA@ @ 0x003CF450
// match: ??_C@_0CH@MBJKKOEC@GetWorldYawAngleToTargetFrompPat@ @ 0x003CF464
// match: ??_C@_0BM@DLKGHHNI@GetLocalYawAngleToPathPoint?$AA@ @ 0x003CF48C
// match: ??_C@_0BH@JLLHBMME@TakeCheckpointSnapshot?$AA@ @ 0x003CF4A8
// match: ??_C@_0BE@EJEPNBDK@SetStartingSections?$AA@ @ 0x003CF4C0
// match: ??_C@_0BG@GIKEDPMM@GetCheckPointRegister?$AA@ @ 0x003CF4D4
// match: ??_C@_0BG@JNPCOGIN@SetCheckPointRegister?$AA@ @ 0x003CF4EC
// match: ??_C@_0BF@KOKAILAN@IsLevelSectionLoaded?$AA@ @ 0x003CF504
// match: ??_C@_0BO@MDPEJEOJ@SetObjectiveLookaheadDistance?$AA@ @ 0x003CF51C
// match: ??_C@_0BE@GKIDOKMC@SetDefaultClumpBank?$AA@ @ 0x003CF53C
// match: ??_C@_0BC@GCNDJHMD@IsClumpBankLoaded?$AA@ @ 0x003CF550
// match: ??_C@_0BF@FODJEJB@RequestClumpBankLoad?$AA@ @ 0x003CF564
// match: ??_C@_0BA@MDACBJLA@KillHelpMessage?$AA@ @ 0x003CF57C
// match: ??_C@_0BF@FFGBAPCN@ClearAllHelpMessages?$AA@ @ 0x003CF58C
// match: ??_C@_0BD@PPKBIKEN@DisplayHelpMessage?$AA@ @ 0x003CF5A4
// match: ??_C@_0BI@OJKNIEGH@SetAttackStandHoldCount?$AA@ @ 0x003CF5B8
// match: ??_C@_0BM@NIPFCEDK@ClearAllSubObjectiveTargets?$AA@ @ 0x003CF5D0
// match: ??_C@_0BI@LGDFFHPM@ClearSubObjectiveTarget?$AA@ @ 0x003CF5EC
// match: ??_C@_0BG@PJCNDIKK@AddSubObjectiveTarget?$AA@ @ 0x003CF604
// match: ??_C@_0BH@FIPFNBDH@SetObjectiveSplinePath?$AA@ @ 0x003CF61C
// match: ??_C@_0BM@PIGHIDCG@EnableObjectiveTargetSystem?$AA@ @ 0x003CF634
// match: ??_C@_0P@KCCBADFP@PrintObjective?$AA@ @ 0x003CF650
// match: ??_C@_0BD@NIJFACJJ@SetObjectiveTarget?$AA@ @ 0x003CF660
// match: ??_C@_0BF@HLJPGBME@SetObjectiveNagTimer?$AA@ @ 0x003CF674
// match: ??_C@_0BL@MMFAINIO@SetDecrementCounterMessage?$AA@ @ 0x003CF68C
// match: ??_C@_0BL@IACCDAFD@SetIncrementCounterMessage?$AA@ @ 0x003CF6A8
// match: ??_C@_0P@JCAAAAMI@SetFailMessage?$AA@ @ 0x003CF6C4
// match: ??_C@_0BD@DHGCBJEF@SetCompleteMessage?$AA@ @ 0x003CF6D4
// match: ??_C@_0BD@FILHIMMD@SetActivateMessage?$AA@ @ 0x003CF6E8
// match: ??_C@_0BH@KGHHDEJB@ModifyObjectiveCounter?$AA@ @ 0x003CF6FC
// match: ??_C@_0BE@FHBHENIN@SetObjectiveCounter?$AA@ @ 0x003CF714
// match: ??_C@_0BE@PJDMANPB@GetObjectiveCounter?$AA@ @ 0x003CF728
// match: ??_C@_0BE@DCBPJML@ClearObjectiveFlags?$AA@ @ 0x003CF73C
// match: ??_C@_0BC@CHPLNMAK@SetObjectiveFlags?$AA@ @ 0x003CF750
// match: ??_C@_0BC@CPAFHBE@GetObjectiveFlags?$AA@ @ 0x003CF764
// match: ??_C@_0BA@NMDPGOPO@RemoveObjective?$AA@ @ 0x003CF778
// match: ??_C@_0N@FCKCGBNC@AddObjective?$AA@ @ 0x003CF788
// match: ??_C@_0BE@INGEOPPG@GetDefendAreaRadius?$AA@ @ 0x003CF798
// match: ??_C@_0BA@DIMNCEMO@ClearDefendArea?$AA@ @ 0x003CF7AC
// match: ??_C@_0CF@MJBHMGLF@SetDefendAreaCylinderCurrentPosi@ @ 0x003CF7BC
// match: ??_C@_0BG@CJOEAEDG@SetDefendAreaCylinder?$AA@ @ 0x003CF7E4
// match: ??_C@_0BN@BFDBCEFM@SetDefendAreaCurrentPosition?$AA@ @ 0x003CF7FC
// match: ??_C@_0O@HJCAHICH@SetDefendArea?$AA@ @ 0x003CF81C
// match: ??_C@_0CC@MDBPHMKF@SetupDefendAreaAnchorPosGotoPoin@ @ 0x003CF82C
// match: ??_C@_0BJ@DKPGPOFO@SetupDefendAreaGotoPoint?$AA@ @ 0x003CF850
// match: ??_C@_0BJ@NCPAKIEL@IsTargetWithinDefendArea?$AA@ @ 0x003CF86C
// match: ??_C@_0BI@DCPOOBNC@IsPointWithinDefendArea?$AA@ @ 0x003CF888
// match: ??_C@_0BD@FINCIPDL@IsWithinDefendArea?$AA@ @ 0x003CF8A0
// match: ??_C@_0BH@BKKPKJIO@DoesSceneHaveTranstion?$AA@ @ 0x003CF8B4
// match: ??_C@_0BN@LKDLNHNA@GetLastPerformanceTypePlayed?$AA@ @ 0x003CF8CC
// match: ??_C@_0BH@OEJAFPIJ@StopCurrentPerformance?$AA@ @ 0x003CF8EC
// match: ??_C@_0BN@IEBMKDDD@PlayCurrentSceneAtNamedPoint?$AA@ @ 0x003CF904
// match: ??_C@_0BI@KPAEIMMF@DoesNameHaveOrientation?$AA@ @ 0x003CF924
// match: ??_C@_0BG@NLDNEADJ@GetTransitionDistance?$AA@ @ 0x003CF93C
// match: ??_C@_0BE@DJDAKENH@SetPlayerBumpRadius?$AA@ @ 0x003CF954
// match: ??_C@_0BA@GEPPEAKJ@RequestSaveGame?$AA@ @ 0x003CF968
// match: ??_C@_0CB@NCMLBFNC@PlayFacialAnimationOnNamedEntity@ @ 0x003CF978
// match: ??_C@_0BE@EEDOMGJM@PlayFacialAnimation?$AA@ @ 0x003CF99C
// match: ??_C@_0BE@DOFGOGKI@SetRestartAnimGroup?$AA@ @ 0x003CF9B0
// match: ??_C@_0O@HAGCDHCM@LoadAnimGroup?$AA@ @ 0x003CF9C4
// match: ??_C@_0O@CHDNHDGF@LoadSoundBank?$AA@ @ 0x003CF9D4
// match: ??_C@_0BE@HBBIJJNF@GetDistanceFromTank?$AA@ @ 0x003CF9E4
// match: ??_C@_0BL@JOLKDGBD@GetPlayerDistanceFromPoint?$AA@ @ 0x003CF9F8
// match: ??_C@_0BF@CCGIEBF@GetDistanceFromPoint?$AA@ @ 0x003CFA14
// match: ??_C@_0BH@OKEGPNPP@GetDistanceFromGrenade?$AA@ @ 0x003CFA2C
// match: ??_C@_0BD@GNJKAFIJ@IsThreatenedByTank?$AA@ @ 0x003CFA44
// match: ??_C@_0BF@ILFLFCFO@CanIDiveAwayFromTank?$AA@ @ 0x003CFA58
// match: ??_C@_0BF@LHJOAPNA@EnableColorCodedName?$AA@ @ 0x003CFA70
// match: ??_C@_0P@EMCGBGOI@GetContactType?$AA@ @ 0x003CFA88
// match: ??_C@_0BK@PFPLAMFD@SetMoveOutOfWayFattyPoint?$AA@ @ 0x003CFA98
// match: ??_C@_0BH@KKGEGBMC@CanGetPointFromGrenade?$AA@ @ 0x003CFAB4
// match: ??_C@_0BH@BBJIBLNJ@CanGetCoverFromGrenade?$AA@ @ 0x003CFACC
// match: ??_C@_0BA@PBHAFGPG@PlayDiveToPoint?$AA@ @ 0x003CFAE4
// match: ??_C@_0BA@CNFMNJMN@CanIDiveForward?$AA@ @ 0x003CFAF4
// match: ??_C@_0BI@MAPNBHML@CanIDiveAwayFromGrenade?$AA@ @ 0x003CFB04
// match: ??_C@_09HONHKNIB@CanIShoot?$AA@ @ 0x003CFB1C
// match: ??_C@_0BJ@NACFLMGA@GetTargetsCanShootStatus?$AA@ @ 0x003CFB28
// match: ??_C@_0P@CCMFMAAM@FinishedGoGoGo?$AA@ @ 0x003CFB44
// match: ??_C@_0P@IKDLLJFC@DidIJustGoGoGo?$AA@ @ 0x003CFB54
// match: ??_C@_0BI@KDAIFPPO@FoundPointPathForGoGoGo?$AA@ @ 0x003CFB64
// match: ??_C@_0O@KMNPEFOD@DisableGoGoGo?$AA@ @ 0x003CFB7C
// match: ??_C@_0BD@DGKLJNEA@EnableGrenadeHints?$AA@ @ 0x003CFB8C
// match: ??_C@_0BM@JBIDJABF@EnableCanShootCheckMessages?$AA@ @ 0x003CFBA0
// match: ??_C@_0BB@MCBDIDEI@SetPointGoodToGo?$AA@ @ 0x003CFBBC
// match: ??_C@_0BC@GPMADAGG@SetSplineGoodToGo?$AA@ @ 0x003CFBD0
// match: ??_C@_0BN@LEBHOFBH@SetSplineMovementByAnimation?$AA@ @ 0x003CFBE4
// match: ??_C@_0BL@NFBJNKAD@GetSplineIncrementFromName?$AA@ @ 0x003CFC04
// match: ??_C@_0BD@PBMLJMOG@GetSplineIncrement?$AA@ @ 0x003CFC20
// match: ??_C@_0BD@LOBKKAO@SetSplineIncrement?$AA@ @ 0x003CFC34
// match: ??_C@_0BK@IMGOAKKI@GetSplinePositionFromName?$AA@ @ 0x003CFC48
// match: ??_C@_0BC@HAGOKMHL@SetSplinePosition?$AA@ @ 0x003CFC64
// match: ??_C@_0BL@HIAJDOBE@GetSplinePositionZFromName?$AA@ @ 0x003CFC78
// match: ??_C@_0BL@JDDOIFBH@GetSplinePositionYFromName?$AA@ @ 0x003CFC94
// match: ??_C@_0BL@HMPMOOCJ@GetSplinePositionXFromName?$AA@ @ 0x003CFCB0
// match: ??_C@_0BD@HNNJEFCO@GetSplinePositionZ?$AA@ @ 0x003CFCCC
// match: ??_C@_0BD@FGPEBGON@GetSplinePositionY?$AA@ @ 0x003CFCE0
// match: ??_C@_0BD@EPOPCHKM@GetSplinePositionX?$AA@ @ 0x003CFCF4
// match: ??_C@_0BA@MJINOKF@GetSplineLength?$AA@ @ 0x003CFD08
// match: ??_C@_0CF@NDKPPODG@GetClosestPositionFromPlayerOnSp@ @ 0x003CFD18
// match: ??_C@_0BL@IEECLFAC@GetClosestPositionOnSpline?$AA@ @ 0x003CFD40
// match: ??_C@_0BC@NBJOCKG@DivorceSplinePath?$AA@ @ 0x003CFD5C
// match: ??_C@_0BF@CGEGBDB@SetSplineEndPosition?$AA@ @ 0x003CFD70
// match: ??_C@_0BG@HDLBBPHH@SetSplinePathFromName?$AA@ @ 0x003CFD88
// match: ??_C@_0BF@CAKCNAPP@HasDefaultSplinePath?$AA@ @ 0x003CFDA0
// match: ??_C@_0M@NOAFHIJD@BlockFacing?$AA@ @ 0x003CFDB8
// match: ??_C@_0BL@EKCLFGHD@AttachRingMountGunToGunner?$AA@ @ 0x003CFDC4
// match: ??_C@_0BO@OMEBEAKJ@DontWaitForNoRenderToDeleteMe?$AA@ @ 0x003CFDE0
// match: ??_C@_0BI@DMALCINO@GetPreferredAttackRange?$AA@ @ 0x003CFE00
// match: ??_C@_0M@NKHAPCMM@SetTankHFOV?$AA@ @ 0x003CFE18
// match: ??_C@_0M@NFGOCEEP@GetTankHFOV?$AA@ @ 0x003CFE24
// match: ??_C@_0BO@JFBCKIHC@ClearRestrictedTankTargetZone?$AA@ @ 0x003CFE30
// match: ??_C@_0BM@GGCGHNFK@SetRestrictedTankTargetZone?$AA@ @ 0x003CFE50
// match: ??_C@_0BB@HGIIPEAC@GetRidingVehicle?$AA@ @ 0x003CFE6C
// match: ??_C@_0BC@EMFMFEBA@NamedEntityExists?$AA@ @ 0x003CFE80
// match: ??_C@_0BP@JALCIPON@Vehicle_GetVehicleEntityHandle?$AA@ @ 0x003CFE94
// match: ??_C@_0CE@FLHEOANO@Vehicle_DecrementIncomingRiderCo@ @ 0x003CFEB4
// match: ??_C@_0CE@CAKPPKBG@Vehicle_IncrementIncomingRiderCo@ @ 0x003CFED8
// match: ??_C@_0BM@HHKJMHA@FlakVehicle_ClearCrewMember?$AA@ @ 0x003CFEFC
// match: ??_C@_0CA@FOEFGJEB@FlakVehicle_SetCrewMemberStatus?$AA@ @ 0x003CFF18
// match: ??_C@_0BK@BGPLLFDP@FlakVehicle_GetCrewMember?$AA@ @ 0x003CFF38
// match: ??_C@_0BK@GJOFAGEI@FlakVehicle_SetCrewMember?$AA@ @ 0x003CFF54
// match: ??_C@_0BM@GBHIOGNO@Vehicle_DecrementRiderCount?$AA@ @ 0x003CFF70
// match: ??_C@_0BM@HNNOHLFP@Vehicle_IncrementRiderCount?$AA@ @ 0x003CFF8C
// match: ??_C@_0BC@GIMDPKCG@Vehicle_AllowMove?$AA@ @ 0x003CFFA8
// match: ??_C@_0BE@JDNGLOL@Vehicle_AllowAttack?$AA@ @ 0x003CFFBC
// match: ??_C@_0CA@OGDOBMPF@TeleportNamedObjectToNamedPoint?$AA@ @ 0x003CFFD0
// match: ??_C@_0BG@JHLONBMF@TeleportToNamedObject?$AA@ @ 0x003CFFF0
// match: ??_C@_0CF@PLBKFJBG@SetTaskCommand_TeleportToAttachP@ @ 0x003D0008
// match: ??_C@_0CB@ILLMBGPD@SetTaskCommand_TurnToAttachPoint@ @ 0x003D0030
// match: ??_C@_0BP@LMHGGMOF@SetTaskCommand_GoToAttachPoint?$AA@ @ 0x003D0054
// match: ??_C@_0CA@FAPHNHJK@RequestAIAction_AttackFromCover?$AA@ @ 0x003D0074
// match: ??_C@_0BN@JKKAHDLH@RequestAIAction_PursueTarget?$AA@ @ 0x003D0094
// match: ??_C@_0P@DPOGPFIL@ReturnNegGodID?$AA@ @ 0x003D00B4
// match: ??_C@_0P@GMNKIBCC@CompareGodalls?$AA@ @ 0x003D00C4
// match: ??_C@_04IJMLHKMM@Sqrt?$AA@ @ 0x003D00D4
// match: ??_C@_03LCFCCKMA@Abs?$AA@ @ 0x003D00DC
// match: ??_C@_04CCLFAABG@Fabs?$AA@ @ 0x003D00E0
// match: ??_C@_06CNBGENLI@Modulo?$AA@ @ 0x003D00E8
// match: ??_C@_09IINFOFCD@BitRShift?$AA@ @ 0x003D00F0
// match: ??_C@_09LPDEACLA@BitLShift?$AA@ @ 0x003D00FC
// match: ??_C@_06OBLNEDKN@BitNot?$AA@ @ 0x003D0108
// match: ??_C@_05BKBNAGEF@BitOr?$AA@ @ 0x003D0110
// match: ??_C@_06PCNOCLJN@BitAnd?$AA@ @ 0x003D0118
// match: ??_C@_0CC@CEENCGMA@RequestAIAction_RetreatFromTarge@ @ 0x003D0120
// match: ??_C@_0BI@PMGPNMLA@GivePlayerInventoryItem?$AA@ @ 0x003D0144
// match: ??_C@_0BH@FEONKBKJ@IsPlayerWeaponStreamed?$AA@ @ 0x003D015C
// match: ??_C@_0BM@JLHICODN@RequestToStreamPlayerWeapon?$AA@ @ 0x003D0174
// match: ??_C@_0BD@HIJGGBJO@RemovePlayerWeapon?$AA@ @ 0x003D0190
// match: ??_C@_0P@CLAONIGF@GivePlayerAmmo?$AA@ @ 0x003D01A4
// match: ??_C@_0BA@POCJNBNL@SetPlayerWeapon?$AA@ @ 0x003D01B4
// match: ??_C@_0BF@HFOCHCKN@TurnCrosshairOnorOff?$AA@ @ 0x003D01C4
// match: ??_C@_0BI@HPMDILGC@TurnPlayerWeaponOnorOff?$AA@ @ 0x003D01DC
// match: ??_C@_0BD@GLHPFOCN@ShouldIMeleeAttack?$AA@ @ 0x003D01F4
// match: ??_C@_0BI@LMGJED@ShouldIDoTheAssaultWalk?$AA@ @ 0x003D0208
// match: ??_C@_0BF@DEJGCCPL@ShouldIThrowAGrenade?$AA@ @ 0x003D0220
// match: ??_C@_0M@DDBEPDEO@DropGrenade?$AA@ @ 0x003D0238
// match: ??_C@_0BG@DMGLOEFI@DoIHaveAGrenadeInHand?$AA@ @ 0x003D0244
// match: ??_C@_0BA@IAJMFNCB@DoIHaveGrenades?$AA@ @ 0x003D025C
// match: ??_C@_0BI@ELELLJLJ@SetAdvancedShotLocation?$AA@ @ 0x003D026C
// match: ??_C@_0BG@BIJJFLCB@ForceMyWeaponToReload?$AA@ @ 0x003D0284
// match: ??_C@_0BE@ICENLBPJ@IsMyWeaponOutOfAmmo?$AA@ @ 0x003D029C
// match: ??_C@_0BF@MEPPNJLE@GetMyWeaponGroupType?$AA@ @ 0x003D02B0
// match: ??_C@_0BD@EOPNIEBM@SetBuddyHealthType?$AA@ @ 0x003D02C8
// match: ??_C@_0P@FEFCKLCE@SetPlayerBuddy?$AA@ @ 0x003D02DC
// match: ??_C@_09DDCGOILE@SetPickup?$AA@ @ 0x003D02EC
// match: ??_C@_0BN@ILBPDFCJ@CheckAttackPostureTransition?$AA@ @ 0x003D02F8
// match: ??_C@_0BC@EKBFAIJC@GetDodgeDirection?$AA@ @ 0x003D0318
// match: ??_C@_0M@FOMJFHHP@IsNameValid?$AA@ @ 0x003D032C
// match: ??_C@_0BG@COHLCNJA@SetupMatchOrientation?$AA@ @ 0x003D0338
// match: ??_C@_0BJ@IHKFPAMG@GetOrientationZFromAIObj?$AA@ @ 0x003D0350
// match: ??_C@_0BJ@BOEHJGMH@GetOrientationYFromAIObj?$AA@ @ 0x003D036C
// match: ??_C@_0BJ@NPMJEJAH@GetOrientationXFromAIObj?$AA@ @ 0x003D0388
// match: ??_C@_0BI@JDGKIIJO@GetOrientationZFromName?$AA@ @ 0x003D03A4
// match: ??_C@_0BI@HIFNDDJN@GetOrientationYFromName?$AA@ @ 0x003D03BC
// match: ??_C@_0BI@JHJPFIKD@GetOrientationXFromName?$AA@ @ 0x003D03D4
// match: ??_C@_0P@HFLANKOC@SetupGotoPoint?$AA@ @ 0x003D03EC
// match: ??_C@_0BM@MCFCAEPJ@GetOffsetPositionZFromAIObj?$AA@ @ 0x003D03FC
// match: ??_C@_0BM@FLLAGCPI@GetOffsetPositionYFromAIObj?$AA@ @ 0x003D0418
// match: ??_C@_0BM@JKDOLNDI@GetOffsetPositionXFromAIObj?$AA@ @ 0x003D0434
// match: ??_C@_0BF@GPDMKJNG@GetPositionZFromName?$AA@ @ 0x003D0450
// match: ??_C@_0BF@IEALBCNF@GetPositionYFromName?$AA@ @ 0x003D0468
// match: ??_C@_0BF@GLMJHJOL@GetPositionXFromName?$AA@ @ 0x003D0480
// match: ??_C@_0BC@MMMFKDGK@GetEntityFromName?$AA@ @ 0x003D0498
// match: ??_C@_0BA@CNAMOOEN@GetTerrainAngle?$AA@ @ 0x003D04AC
// match: ??_C@_0O@OFBMDJMM@GetTurnAmount?$AA@ @ 0x003D04BC
// match: ??_C@_0M@HJLAJOB@SetTurnMode?$AA@ @ 0x003D04CC
// match: ??_C@_0N@BJOPDNPK@SetHeadTrack?$AA@ @ 0x003D04D8
// match: ??_C@_0BF@EPHBKGIN@FireWeaponContinuous?$AA@ @ 0x003D04E8
// match: ??_C@_0BB@PLBJDLBO@FireWeaponXTimes?$AA@ @ 0x003D0500
// match: ??_C@_0BC@IMLLDACH@GetEntityToFollow?$AA@ @ 0x003D0514
// match: ??_C@_0BC@KJLALLDJ@SetEntityToFollow?$AA@ @ 0x003D0528
// match: ??_C@_0BA@NLJFCHJA@SetFiveWayBlend?$AA@ @ 0x003D053C
// match: ??_C@_0BG@NMBAPNOE@SetCrewAttachPosition?$AA@ @ 0x003D054C
// match: ??_C@_0CK@JLDNIGDB@GetAttachPointOrientationZFromNa@ @ 0x003D0564
// match: ??_C@_0CK@MIKHNNLF@GetAttachPointOrientationYFromNa@ @ 0x003D0590
// match: ??_C@_0CK@EPABBGPG@GetAttachPointOrientationXFromNa@ @ 0x003D05BC
// match: ??_C@_0BP@CIEGPEKO@GetAttachPointZFromNamedEntity?$AA@ @ 0x003D05E8
// match: ??_C@_0BP@HLNMKPCK@GetAttachPointYFromNamedEntity?$AA@ @ 0x003D0608
// match: ??_C@_0BP@PMHKGEGJ@GetAttachPointXFromNamedEntity?$AA@ @ 0x003D0628
// match: ??_C@_0BJ@EHDCLANK@Custom_SetAnimatedObject?$AA@ @ 0x003D0648
// match: ??_C@_0BB@EICDPFIE@Custom_SetObject?$AA@ @ 0x003D0664
// match: ??_C@_0BE@BBDLLDPB@Custom_SendMessages?$AA@ @ 0x003D0678
// match: ??_C@_0BC@GCJKNMIP@Custom_GetSceneID?$AA@ @ 0x003D068C
// match: ??_C@_0BH@LOMHFOEH@Custom_GetStartMessage?$AA@ @ 0x003D06A0
// match: ??_C@_0BD@PPBJEFGH@GetWakeUpMessageID?$AA@ @ 0x003D06B8
// match: ??_C@_0BG@FBLBEEBE@GetTaskReturnRegister?$AA@ @ 0x003D06CC
// match: ??_C@_0O@INPHMHMD@PG_ForcedFire?$AA@ @ 0x003D06E4
// match: ??_C@_0BC@MJFDNIOB@PG_EnableLOSCheck?$AA@ @ 0x003D06F4
// match: ??_C@_0BB@OLJFJOHM@PG_TargetDefault?$AA@ @ 0x003D0708
// match: ??_C@_0BG@GPDIDEDE@PG_EnableFiringStages?$AA@ @ 0x003D071C
// match: ??_C@_0BE@DFACCNDH@PG_TargetNamedPoint?$AA@ @ 0x003D0734
// match: ??_C@_0P@BAFGGGMB@PG_TargetPoint?$AA@ @ 0x003D0748
// match: ??_C@_0BN@PNJELNCI@PG_TargetNamedObjectByScript?$AA@ @ 0x003D0758
// match: ??_C@_0BI@OMHEIAKC@PG_TargetObjectByScript?$AA@ @ 0x003D0778
// match: ??_C@_0BF@CDHGJFB@PG_DetatchFromParent?$AA@ @ 0x003D0790
// match: ??_C@_0BL@PINBLNEE@PG_SetParentAndAttachPoint?$AA@ @ 0x003D07A8
// match: ??_C@_0BJ@LEBBJFLJ@PG_SetSplinePathFromName?$AA@ @ 0x003D07C4
// match: ??_C@_0CB@LKKEKLJE@PG_ManipulateProjectileGenerator@ @ 0x003D07E0
// match: ??_C@_0P@GMDONFEL@PZ_SetUserData?$AA@ @ 0x003D0804
// match: ??_C@_0O@CPCEBKJC@PZ_Manipulate?$AA@ @ 0x003D0814
// match: ??_C@_0BJ@MPBPIFA@DropGrenadeAtLocationXYZ?$AA@ @ 0x003D0824
// match: ??_C@_0L@GMEBLHMJ@DropPickup?$AA@ @ 0x003D0840
// match: ??_C@_0P@GMDHFNLF@SetPlayerState?$AA@ @ 0x003D084C
// match: ??_C@_0BD@NOLIOCKK@LockPlayerMovement?$AA@ @ 0x003D085C
// match: ??_C@_09PEMGNEEO@PlaySound?$AA@ @ 0x003D0870
// match: ??_C@_0BE@KAAPEHNP@ChangeCCESSPoolSize?$AA@ @ 0x003D087C
// match: ??_C@_0BJ@LKGNFKBL@SetCCESSPoolManagerState?$AA@ @ 0x003D0890
// match: ??_C@_0BI@KCDJHKEE@SetNumSpawnableEntities?$AA@ @ 0x003D08AC
// match: ??_C@_0BE@JLLKBCDE@SetCCESSPoolManager?$AA@ @ 0x003D08C4
// match: ??_C@_0BI@ONFCODNG@ToggleCCESSPoolCreation?$AA@ @ 0x003D08D8
// match: ??_C@_0BJ@NJCNNLEF@UnregisterTimerByMessage?$AA@ @ 0x003D08F0
// match: ??_C@_0O@EGAHGMFM@RegisterTimer?$AA@ @ 0x003D090C
// match: ??_C@_0BH@BCCKLEJO@SwapToDestroyedVersion?$AA@ @ 0x003D091C
// match: ??_C@_0BH@NKAMGMJN@ClearCCESSPoolTriggers?$AA@ @ 0x003D0934
// match: ??_C@_0BJ@OMAINJJH@SpecialCCESSPoolCreation?$AA@ @ 0x003D094C
// match: ??_C@_0BA@BEFBCJAF@DestroyParticle?$AA@ @ 0x003D0968
// match: ??_C@_0L@BOGAGK@SendFlying?$AA@ @ 0x003D0978
// match: ??_C@_0CP@EJNMNNPC@AnimatedBGEntityMountedWeaponGet@ @ 0x003D0984
// match: ??_C@_0CM@EGMPFDNM@AnimatedBGEntityAttachPlayerToMo@ @ 0x003D09B4
// match: ??_C@_0BP@LCNJBMKF@AttachPlayerToAnimatedBGEntity?$AA@ @ 0x003D09E0
// match: ??_C@_0BI@KBIBMJDF@SetAnimatedBGEntityType?$AA@ @ 0x003D0A00
// match: ??_C@_0BF@LOIGLOK@SetDoorPathNodeState?$AA@ @ 0x003D0A18
// match: ??_C@_0BH@JNALABFN@SetCollisionNotifyFlag?$AA@ @ 0x003D0A30
// match: ??_C@_0M@HBNFOBBI@SetDeadFlag?$AA@ @ 0x003D0A48
// match: ??_C@_0O@NDLEJCGE@GetStartState?$AA@ @ 0x003D0A54
// match: ??_C@_0O@BEGKHKBG@ForceManeuver?$AA@ @ 0x003D0A64
// match: ??_C@_0BA@OJFCDAJI@SuggestManeuver?$AA@ @ 0x003D0A74
// match: ??_C@_0BL@BGCGFCAF@IsPathBlockedWhileStrafing?$AA@ @ 0x003D0A84
// match: ??_C@_0O@NAJJAPBA@IsPathBlocked?$AA@ @ 0x003D0AA0
// match: ??_C@_0BF@HEBOPPBD@UnRegisterAStarCheck?$AA@ @ 0x003D0AB0
// match: ??_C@_0BD@OLMIJALF@RegisterAStarCheck?$AA@ @ 0x003D0AC8
// match: ??_C@_0BG@ODLEIIOA@SetAllowTargetLOSLoss?$AA@ @ 0x003D0ADC
// match: ??_C@_0BM@NFFBJLBL@GetNumberOfObjectsInTrigger?$AA@ @ 0x003D0AF4
// match: ??_C@_0BH@HNEDEKNE@IsNamedEntityInTrigger?$AA@ @ 0x003D0B10
// match: ??_C@_0BK@PLPHOFOE@SetTriggerProximityChecks?$AA@ @ 0x003D0B28
// match: ??_C@_0BE@JGJGLHLF@SetTriggerCollision?$AA@ @ 0x003D0B44
// match: ??_C@_0BC@PGLFKKEF@SetEngineAttitude?$AA@ @ 0x003D0B58
// match: ??_C@_0M@MPDILAEM@GetAttitude?$AA@ @ 0x003D0B6C
// match: ??_C@_0O@DINEMCJN@GetSuppressed?$AA@ @ 0x003D0B78
// match: ??_C@_0M@DOFPPKEP@AllowFiring?$AA@ @ 0x003D0B88
// match: ??_C@_0BB@POOJMKPC@InfiniteAmmoClip?$AA@ @ 0x003D0B94
// match: ??_C@_09NFFBPPPO@SetFiring?$AA@ @ 0x003D0BA8
// match: ??_C@_0BD@LNNNLMPM@SetEntityCollision?$AA@ @ 0x003D0BB4
// match: ??_C@_0M@CDFFBJMG@SetNoRender?$AA@ @ 0x003D0BC8
// match: ??_C@_0BI@JOKOBCKH@SetEnvironmentCollision?$AA@ @ 0x003D0BD4
// match: ??_C@_0N@OIJGAPCI@SetCollision?$AA@ @ 0x003D0BEC
// match: ??_C@_0P@KNJGFEIN@RandRangeFloat?$AA@ @ 0x003D0BFC
// match: ??_C@_09DLOLLLBC@RandRange?$AA@ @ 0x003D0C0C
// match: ??_C@_0BA@GLBBCEKE@GetUniqueNumber?$AA@ @ 0x003D0C18
// match: ??_C@_0BB@JMBCNEEJ@DetachFromEntity?$AA@ @ 0x003D0C28
// match: ??_C@_0P@IPJCIIDH@AttachToEntity?$AA@ @ 0x003D0C3C
// match: ??_C@_0BC@FLAGBMK@SoundStillPlaying?$AA@ @ 0x003D0C4C
// match: ??_C@_0N@LIPNBAL@RenderFadeIn?$AA@ @ 0x003D0C60
// match: ??_C@_0O@OJJCPJOG@RenderFadeOut?$AA@ @ 0x003D0C70
// match: ??_C@_0BE@HPELHGAP@FadeSubstreamVolume?$AA@ @ 0x003D0C80
// match: ??_C@_0BH@JNCHAMM@StartPrimedAudioStream?$AA@ @ 0x003D0C94
// match: ??_C@_0BB@KJOADIFA@PrimeAudioStream?$AA@ @ 0x003D0CAC
// match: ??_C@_0CB@CBEFEJN@EfuncPlayIndexSoundOnNamedEntity@ @ 0x003D0CC0
// match: ??_C@_0BE@PPIMNFOO@EfuncPlayIndexSound?$AA@ @ 0x003D0CE4
// match: ??_C@_0CJ@BNOPINAA@EfuncPlaySoundAndFacialAnimOnNam@ @ 0x003D0CF8
// match: ??_C@_0BM@JMGPEKAA@EfuncPlaySoundOnNamedEntity?$AA@ @ 0x003D0D24
// match: ??_C@_0BM@EAAKGOCF@EfuncPlaySoundAndFacialAnim?$AA@ @ 0x003D0D40
// match: ??_C@_0P@OCHCDOAO@EfuncPlaySound?$AA@ @ 0x003D0D5C
// match: ??_C@_0BG@OOJIADHG@EnableNamedCoverPoint?$AA@ @ 0x003D0D6C
// match: ??_C@_0BE@GEHLDIN@EnableNamedPathNode?$AA@ @ 0x003D0D84
// match: ??_C@_0BH@LPMPJFAN@DisableNamedCoverPoint?$AA@ @ 0x003D0D98
// match: ??_C@_0BG@HGJANHAP@EnableEndLevelTrigger?$AA@ @ 0x003D0DB0
// match: ??_C@_0BF@GGKBNOB@QuitAndLoadNextLevel?$AA@ @ 0x003D0DC8
// match: ??_C@_09MHFMFDMH@QuitLevel?$AA@ @ 0x003D0DE0
// match: ??_C@_0N@OKGNEGNI@GetGameFrame?$AA@ @ 0x003D0DEC
// match: ??_C@_0N@OMMMCGHH@RestartLevel?$AA@ @ 0x003D0DFC
// match: ??_C@_0BC@LCHDBEKE@StopRidingVehicle?$AA@ @ 0x003D0E0C
// match: ??_C@_0M@PLJNMBBM@RideVehicle?$AA@ @ 0x003D0E20
// match: ??_C@_0BE@HDFOLJBC@RotateMyOrientation?$AA@ @ 0x003D0E2C
// match: ??_C@_0BB@BIFPDBMJ@SetMyOrientation?$AA@ @ 0x003D0E40
// match: ??_C@_0O@CNFFBCPF@SetMyPosition?$AA@ @ 0x003D0E54
// match: ??_C@_0BI@BFCPENOO@SetMyDistanceFromTarget?$AA@ @ 0x003D0E64
// match: ??_C@_0P@DCOBJMOF@IsFacingTarget?$AA@ @ 0x003D0E7C
// match: ??_C@_0N@KJNLFGEJ@CanSeeTarget?$AA@ @ 0x003D0E8C
// match: ??_C@_0BL@FBJKIDCI@SetConnectedCornerOccupied?$AA@ @ 0x003D0E9C
// match: ??_C@_0BK@JFHHLFFB@IsConnectedCornerOccupied?$AA@ @ 0x003D0EB8
// match: ??_C@_0BC@MJIFCNL@IsConnectedCorner?$AA@ @ 0x003D0ED4
// match: ??_C@_0BH@DANDJBFM@IsCoverSafeFromGrenade?$AA@ @ 0x003D0EE8
// match: ??_C@_0BA@FHIIBIPK@ClearCoverPoint?$AA@ @ 0x003D0F00
// match: ??_C@_0BH@DGNHHJGG@SetArrivedAtCoverPoint?$AA@ @ 0x003D0F10
// match: ??_C@_0BG@EDFMOGFO@SetCoverPointFromName?$AA@ @ 0x003D0F28
// match: ??_C@_0O@BGGFEEBD@SetCoverPoint?$AA@ @ 0x003D0F40
// match: ??_C@_0BC@GLLFANGP@GetCoverPointType?$AA@ @ 0x003D0F50
// match: ??_C@_0BH@MEDMPHBA@GetCoverPointPeekFlags?$AA@ @ 0x003D0F64
// match: ??_C@_0BM@OMNINMNF@OrientToCoverPointImmediate?$AA@ @ 0x003D0F7C
// match: ??_C@_0BD@CODHAAAC@OrientToCoverPoint?$AA@ @ 0x003D0F98
// match: ??_C@_0BC@CMNBCOCP@GetCollisionWidth?$AA@ @ 0x003D0FAC
// match: ??_C@_0BF@PBAHBBDM@GetVelocityMagnitude?$AA@ @ 0x003D0FC0
// match: ??_C@_0O@BKOIPFI@ScaleVelocity?$AA@ @ 0x003D0FD8
// match: ??_C@_0M@IKABEOO@SetVelocity?$AA@ @ 0x003D0FE8
// match: ??_C@_0BG@FEEEINJM@SetNoFallThroughWorld?$AA@ @ 0x003D0FF4
// match: ??_C@_0BK@NDLDDLF@SetJiggleReactionOnEntity?$AA@ @ 0x003D100C
// match: ??_C@_0BP@LODDMBHL@SetJiggleReactionOnNamedEntity?$AA@ @ 0x003D1028
// match: ??_C@_0BG@GLCDNIEJ@ClearCollideWithFlags?$AA@ @ 0x003D1048
// match: ??_C@_0BE@PCMGMONL@SetCollideWithFlags?$AA@ @ 0x003D1060
// match: ??_C@_0BP@IADMHJNP@SetGroundCollisionNotification?$AA@ @ 0x003D1074
// match: ??_C@_0BN@IDFIEIOP@SetWallCollisionNotification?$AA@ @ 0x003D1094
// match: ??_C@_0BM@EGNOGNFG@SetEnvCollisionNotification?$AA@ @ 0x003D10B4
// match: ??_C@_0L@OJBLNBAH@SetGravity?$AA@ @ 0x003D10D0
// match: ??_C@_0BJ@MPIDFLJO@SetVehicleWeaponDisabled?$AA@ @ 0x003D10DC
// match: ??_C@_0BE@IIOGKLBA@VehicleSetGimpLevel?$AA@ @ 0x003D10F8
// match: ??_C@_0BE@MIODOOCC@VehicleGetDeathTask?$AA@ @ 0x003D110C
// match: ??_C@_0BK@OKLGJMDN@VehicleDisableTurretTrack?$AA@ @ 0x003D1120
// match: ??_C@_0BJ@BHMGLPNK@VehicleEnableTurretTrack?$AA@ @ 0x003D113C
// match: ??_C@_0BC@LDGFENNJ@VehicleFireWeapon?$AA@ @ 0x003D1158
// match: ??_C@_0BG@OEDONCFB@VehicleSecondaryPitch?$AA@ @ 0x003D116C
// match: ??_C@_0BF@CNBIPPPO@VehicleSecondaryTurn?$AA@ @ 0x003D1184
// match: ??_C@_0BD@KIFHBIHG@VehicleSetSteering?$AA@ @ 0x003D119C
// match: ??_C@_0CB@HPCAJCHK@SoldierTrigger_GetMyVehiclesName@ @ 0x003D11B0
// match: ??_C@_0CA@DBBAHOAO@SoldierEntity_GetMyVehiclesName?$AA@ @ 0x003D11D4
// match: ??_C@_0BJ@EIICODHG@VehicleTrigger_GetMyName?$AA@ @ 0x003D11F4
// match: ??_C@_0BF@GBOPAOGK@VehicleEnablePhysics?$AA@ @ 0x003D1210
// match: ??_C@_0BA@CIPIMOAB@VehicleSetBrake?$AA@ @ 0x003D1228
// match: ??_C@_0BD@PBLMHLPB@VehicleGetVelocity?$AA@ @ 0x003D1238
// match: ??_C@_0BD@PIEBBMPD@VehicleSetThrottle?$AA@ @ 0x003D124C
// match: ??_C@_0BJ@CANDGMFB@VehicleShowMountedWeapon?$AA@ @ 0x003D1260
// match: ??_C@_0BI@KELNFACB@VehicleGetMountedWeapon?$AA@ @ 0x003D127C
// match: ??_C@_0CG@MAHBIPKE@VehicleMountedWeaponGetAttachedE@ @ 0x003D1294
// match: ??_C@_0BF@HJILNADN@VehicleSetHatchState?$AA@ @ 0x003D12BC
// match: ??_C@_0BF@GJFGDEK@VehicleGetHatchState?$AA@ @ 0x003D12D4
// match: ??_C@_0BG@CAAEIIFF@VehicleSetCruiseSpeed?$AA@ @ 0x003D12EC
// match: ??_C@_0BD@DLEKPHJO@VehicleSetMaxSpeed?$AA@ @ 0x003D1304
// match: ??_C@_0BG@CPFOIBKL@VehicleSetMaxThrottle?$AA@ @ 0x003D1318
// match: ??_C@_0BB@PHAKHJBO@VehicleSetEngine?$AA@ @ 0x003D1330
// match: ??_C@_0BN@HKLPILKC@PlayerEnterVehicleTransition?$AA@ @ 0x003D1344
// match: ??_C@_0BM@NAPHLCLN@PlayerExitVehicleTransition?$AA@ @ 0x003D1364
// match: ??_C@_0BI@GHHBOEGB@VehicleGetPlayerPosture?$AA@ @ 0x003D1380
// match: ??_C@_0BK@IJDOFMMG@VehicleGetPlayerPassenger?$AA@ @ 0x003D1398
// match: ??_C@_0BJ@OAPGMJPG@VehicleGetAttachedEntity?$AA@ @ 0x003D13B4
// match: ??_C@_0BN@BMLEMPCO@VehicleAttachPlayerPassenger?$AA@ @ 0x003D13D0
// match: ??_C@_0CD@LPDEFCGD@VehicleAttachEntityToMountedWeap@ @ 0x003D13F0
// match: ??_C@_0BE@JLBJBGBP@VehicleAttachEntity?$AA@ @ 0x003D1414
// match: ??_C@_0BD@MJDPKGMH@VehicleInProximity?$AA@ @ 0x003D1428
// match: ??_C@_0BM@BGFOHOLF@CrossProductVectorComponent?$AA@ @ 0x003D143C
// match: ??_C@_0BC@PAIDMHOK@DotProductVectors?$AA@ @ 0x003D1458
// match: ??_C@_0P@OLCNHALP@SetDamageLevel?$AA@ @ 0x003D146C
// match: ??_C@_0P@CFDDIKJD@GetDamageLevel?$AA@ @ 0x003D147C
// match: ??_C@_0BB@NIOPBJFO@GetDestructionID?$AA@ @ 0x003D148C
// match: ??_C@_0BD@HBMIDADA@IncrementHitPoints?$AA@ @ 0x003D14A0
// match: ??_C@_0N@CNDABMOH@SetHitPoints?$AA@ @ 0x003D14B4
// match: ??_C@_0N@FJIONAKL@GetHitPoints?$AA@ @ 0x003D14C4
// match: ??_C@_0N@BGDNBAOP@SetAIControl?$AA@ @ 0x003D14D4
// match: ??_C@_0N@GCIDNMKD@GetAIControl?$AA@ @ 0x003D14E4
// match: ??_C@_0CA@PFFIKAMJ@SetFireAndMovementPointFromName?$AA@ @ 0x003D14F4
// match: ??_C@_0CJ@LHBONHHM@SetFireAndMovementExclusionEnemy@ @ 0x003D1514
// match: ??_C@_0BH@KLEDMHIC@DisableFireAndMovement?$AA@ @ 0x003D1540
// match: ??_C@_0BK@IACBMKML@ClearFireAndMovementPoint?$AA@ @ 0x003D1558
// match: ??_C@_0BB@BLOGCPAM@SetManeuverState?$AA@ @ 0x003D1574
// match: ??_C@_0BA@NECFAMBI@SetManeuverType?$AA@ @ 0x003D1588
// match: ??_C@_0BA@OGDDHOAB@GetManeuverType?$AA@ @ 0x003D1598
// match: ??_C@_0O@BCHLNGOM@GetTargetType?$AA@ @ 0x003D15A8
// match: ??_C@_0BG@KJKIIEEA@GetAttackStandPosture?$AA@ @ 0x003D15B8
// match: ??_C@_0BB@PIADPLBL@GetTargetPosture?$AA@ @ 0x003D15D0
// match: ??_C@_0O@PMJOIGGO@ClearMyTarget?$AA@ @ 0x003D15E4
// match: ??_C@_0M@LJLCBIGI@SetMyTarget?$AA@ @ 0x003D15F4
// match: ??_C@_0M@LGKMMOOL@GetMyTarget?$AA@ @ 0x003D1600
// match: ??_C@_0BE@OHPCOOPH@GetSceneActionCount?$AA@ @ 0x003D160C
// match: ??_C@_0BB@HMMFEAPL@PlayCurrentScene?$AA@ @ 0x003D1620
// match: ??_C@_0O@NFOMGCDL@SetSceneValue?$AA@ @ 0x003D1634
// match: ??_C@_0BC@DLEIFOLL@GetSceneActionMsg?$AA@ @ 0x003D1644
// match: ??_C@_0BF@EFFEOIII@FindAStarPathToPoint?$AA@ @ 0x003D1658
// match: ??_C@_0BI@PNNBBDJ@FindAStarPathToPathNode?$AA@ @ 0x003D1670
// match: ??_C@_0BF@JLFNNFEL@FindAStarPathToAIObj?$AA@ @ 0x003D1688
// match: ??_C@_0L@CLKNNAOC@SetAIParam?$AA@ @ 0x003D16A0
// match: ??_C@_0M@EHLAIBN@ClearAIFlag?$AA@ @ 0x003D16AC
// match: ??_C@_09FBDMEMJN@GetAIFlag?$AA@ @ 0x003D16B8
// match: ??_C@_09HPHJGNAP@SetAIFlag?$AA@ @ 0x003D16C4
// match: ??_C@_09KEHCAL@GetAIMode?$AA@ @ 0x003D16D0
// match: ??_C@_09COOBFDJJ@SetAIMode?$AA@ @ 0x003D16DC
// match: ??_C@_0P@CGPKFIEC@SetSquadLeader?$AA@ @ 0x003D16E8
// match: ??_C@_0P@OIOEKCGO@GetSquadLeader?$AA@ @ 0x003D16F8
// match: ??_C@_0BE@JCLHKMLH@CreateExplosionZone?$AA@ @ 0x003D1708
// match: ??_C@_0BJ@NNEHOGAP@SetRenderPartStateByName?$AA@ @ 0x003D171C
// match: ??_C@_0BD@NNEBBPPI@GetRenderPartState?$AA@ @ 0x003D1738
// match: ??_C@_0BD@CHGLCJBA@SetRenderPartState?$AA@ @ 0x003D174C
// match: ??_C@_0BD@CFAEHDCM@EnableWeaponRender?$AA@ @ 0x003D1760
// match: ??_C@_0BH@CMCDGADL@SwitchToDestroyedClump?$AA@ @ 0x003D1774
// match: ??_C@_0BE@ILOFDBHJ@KillParticleSpawner?$AA@ @ 0x003D178C
// match: ??_C@_0BF@MHIOHAOD@SpawnParticleSpawner?$AA@ @ 0x003D17A0
// match: ??_C@_0BI@OHKOCAPI@SpawnParticleAtPosition?$AA@ @ 0x003D17B8
// match: ??_C@_0O@FLLMINP@SpawnParticle?$AA@ @ 0x003D17D0
// match: ??_C@_0BI@JMIFGNFB@PlayParticleSystemAtXYZ?$AA@ @ 0x003D17E0
// match: ??_C@_0BE@CAHIMIBM@GetNumberOfRestarts?$AA@ @ 0x003D17F8
// match: ??_C@_0N@FBKMIBPI@IHaveATarget?$AA@ @ 0x003D180C
// match: ??_C@_0BB@OGJDLKHB@DistanceToTarget?$AA@ @ 0x003D181C
// match: ??_C@_0BL@INPMJKL@UnregisterDistanceCheckPtr?$AA@ @ 0x003D1830
// match: ??_C@_0BI@IPEJNHGG@UnregisterDistanceCheck?$AA@ @ 0x003D184C
// match: ??_C@_0BJ@JCPPDED@RegisterDistanceCheckMsg?$AA@ @ 0x003D1864
// match: ??_C@_0BG@FHPGGEGB@RegisterDistanceCheck?$AA@ @ 0x003D1880
// match: ??_C@_0BL@KFDONFBF@GetWeaponIsBoltActionRifle?$AA@ @ 0x003D1898
// match: ??_C@_0BI@GGHAHIMI@GetWeaponsRunMeleeRange?$AA@ @ 0x003D18B4
// match: ??_C@_0BK@PMGEEINF@GetWeaponsLungeMeleeRange?$AA@ @ 0x003D18CC
// match: ??_C@_0BK@GHPGDIOI@GetWeaponsStandMeleeRange?$AA@ @ 0x003D18E8
// match: ??_C@_0CC@NEILNIEF@GetWeaponsTooCloseForComfortRang@ @ 0x003D1904
// match: ??_C@_0BH@OENCAPHD@GetWeaponsMinLongRange?$AA@ @ 0x003D1928
// match: ??_C@_0BI@GIBGBMPA@OverrideNPCGrenadeTimer?$AA@ @ 0x003D1940
// match: ??_C@_0BF@CLABNAJN@SetGrenadeThrowPoint?$AA@ @ 0x003D1958
// match: ??_C@_0BI@GEPGKPOI@CancelGrenadeThrowPoint?$AA@ @ 0x003D1970
// match: ??_C@_0BJ@HILPHKMN@GetWeaponsMinMediumRange?$AA@ @ 0x003D1988
// match: ??_C@_0P@KHDJJBMF@GetVisionRange?$AA@ @ 0x003D19A4
// match: ??_C@_0M@GEIPHDIB@TimeToTicks?$AA@ @ 0x003D19B4
// match: ??_C@_0L@OJIMMHGM@CreateTank?$AA@ @ 0x003D19C0
// match: ??_C@_0M@JIHKJJIA@DestroySelf?$AA@ @ 0x003D19CC
// match: ??_C@_0O@OMFNAMNA@CreateMyChild?$AA@ @ 0x003D19D8
// match: ??_C@_0M@PADBKGKN@AssertValue?$AA@ @ 0x003D19E8
// match: ??_C@_0BA@CBGMBFCL@GetEntityHandle?$AA@ @ 0x003D19F4
// match: ??_C@_0BF@FNPMEBPM@GetMyAIObjectPointer?$AA@ @ 0x003D1A04
// match: ??_C@_0BL@FKPEJKGD@GetThisStateMachinePointer?$AA@ @ 0x003D1A1C
// match: ??_C@_0M@LBKDNJEL@SetSceneMap?$AA@ @ 0x003D1A38
// match: ??_C@_0O@GOIEHDDA@SetStarStatus?$AA@ @ 0x003D1A44
// match: ??_C@_0BE@JKDMHAAN@DisablePerformances?$AA@ @ 0x003D1A54
// match: ??_C@_0BG@DLGHHONA@MountedWeaponReloaded?$AA@ @ 0x003D1A68
// match: ??_C@_0BP@GELOKNGB@ResetNPCMountedWeaponAimMatrix?$AA@ @ 0x003D1A80
// match: ??_C@_0L@LPEBFAMO@DetachProp?$AA@ @ 0x003D1AA0
// match: ??_C@_0N@CFDHLKCA@AttachPropEx?$AA@ @ 0x003D1AAC
// match: ??_C@_0L@GHKBGFK@AttachProp?$AA@ @ 0x003D1ABC
// match: ??_C@_0BE@JMPONACD@SetMyMMGYawAndPitch?$AA@ @ 0x003D1AC8
// match: ??_C@_0CD@PPKNAMMG@SetMyMMGToFireEvenIfICantSeeTarg@ @ 0x003D1ADC
// match: ??_C@_0BM@PEKGFABN@IsPlayerUsingAMountedWeapon?$AA@ @ 0x003D1B00
// match: ??_C@_0BJ@KIJEAMHI@AreWeUsingAMountedWeapon?$AA@ @ 0x003D1B1C
// match: ??_C@_0BI@DOFNAIJD@DetachFromMountedWeapon?$AA@ @ 0x003D1B38
// match: ??_C@_0BG@KAMCDIK@AttachToMountedWeapon?$AA@ @ 0x003D1B50
// match: ??_C@_0M@CAJGBEFI@SnapToCover?$AA@ @ 0x003D1B68
// match: ??_C@_0BD@NCOFBFNP@WillTransitionPlay?$AA@ @ 0x003D1B74
// match: ??_C@_0BL@OHENOKGO@GotoPointUsingRegistration?$AA@ @ 0x003D1B88
// match: ??_C@_0BH@LDDEONFM@GetMyMMGMaxPauseLength?$AA@ @ 0x003D1BA4
// match: ??_C@_0BH@JEIPIKGN@GetMyMMGMinPauseLength?$AA@ @ 0x003D1BBC
// match: ??_C@_0BH@BPPFADLK@GetMyMMGMaxBurstLength?$AA@ @ 0x003D1BD4
// match: ??_C@_0BH@DIEOGEIL@GetMyMMGMinBurstLength?$AA@ @ 0x003D1BEC
// match: ??_C@_0CG@DDLPOPEN@PlayCoverPointRegistrationPerfor@ @ 0x003D1C04
// match: ??_C@_0BJ@LPCNGEGB@PlayPickUpMMGPerformance?$AA@ @ 0x003D1C2C
// match: ??_C@_0BK@NFNDHMKK@PlayAlarmCrankPerformance?$AA@ @ 0x003D1C48
// match: ??_C@_0BL@HODONGLL@PlaySpecialIdlePerformance?$AA@ @ 0x003D1C64
// match: ??_C@_0BH@KJLCOLLB@PlayCurrentPerformance?$AA@ @ 0x003D1C80
// match: ??_C@_0BM@OMDEEBEB@PlayHitDeathAnimDefaultData?$AA@ @ 0x003D1C98
// match: ??_C@_0BB@JENOFDD@PlayHitDeathAnim?$AA@ @ 0x003D1CB4
// match: ??_C@_0BB@COCJHICP@SetMyWidthHeight?$AA@ @ 0x003D1CC8
// match: ??_C@_0N@PBKBHKC@SetFadeLevel?$AA@ @ 0x003D1CDC
// match: ??_C@_0L@DFDPMPLD@SetFadeOut?$AA@ @ 0x003D1CEC
// match: ??_C@_0BM@OADBMHGA@GetPrimaryAnimationDuration?$AA@ @ 0x003D1CF8
// match: ??_C@_0BD@PANAJKCN@GetLastHitLocation?$AA@ @ 0x003D1D14
// match: ??_C@_0BB@DHDOLJIM@SetPerformanceID?$AA@ @ 0x003D1D28
// match: ??_C@_0BJ@LGEPIEJP@RestoreMyTriggerPosition?$AA@ @ 0x003D1D3C
// match: ??_C@_0BF@LEMLGEGH@SetMyTriggerPosition?$AA@ @ 0x003D1D58
// match: ??_C@_0BH@NIEEKGH@SetMyTriggerActionIcon?$AA@ @ 0x003D1D70
// match: ??_C@_0BE@CCOADEEK@GetMyTriggerPointer?$AA@ @ 0x003D1D88
// match: ??_C@_0BE@HCIDMHCN@GetPerformanceValue?$AA@ @ 0x003D1D9C
// match: ??_C@_0BP@HLNHBILO@SetSpecialIdlePerformanceValue?$AA@ @ 0x003D1DB0
// match: ??_C@_0BJ@EKNDADBL@SetupAssassinationValues?$AA@ @ 0x003D1DD0
// match: ??_C@_0BB@PDKOKAEI@SetHitDeathValue?$AA@ @ 0x003D1DEC
// match: ??_C@_0BE@NMKIIHFB@SetPerformanceValue?$AA@ @ 0x003D1E00
// match: ??_C@_0BC@HKOCJLBI@SetPerformanceMap?$AA@ @ 0x003D1E14
// match: ??_C@_0BF@ELPBLKJH@SetPriorityCollision?$AA@ @ 0x003D1E28
// match: ??_C@_0BC@FLNNLFCC@SetRenderPriority?$AA@ @ 0x003D1E40
// match: ??_C@_0P@LPEEKKFA@SetEntityScale?$AA@ @ 0x003D1E54
// match: ??_C@_0L@PPIHBBPA@SetFogType?$AA@ @ 0x003D1E64
// match: ??_C@_0BA@KMDJKGGP@SetClipDistance?$AA@ @ 0x003D1E70
// match: ??_C@_0P@MGOLLCEO@SetFogDistance?$AA@ @ 0x003D1E80
// match: ??_C@_0O@ENJFDJJP@SetMotionBlur?$AA@ @ 0x003D1E90
// match: ??_C@_0M@OPMDHEOL@PlayerShock?$AA@ @ 0x003D1EA0
// match: ??_C@_09EAHPBKGI@TimeScale?$AA@ @ 0x003D1EAC
// match: ??_C@_0BA@FKKIFFPB@ControllerShake?$AA@ @ 0x003D1EB8
// match: ??_C@_0M@FPBOOCGP@CameraShake?$AA@ @ 0x003D1EC8
// match: ??_C@_0O@KBCBFCIH@CreateSoldier?$AA@ @ 0x003D1ED4
// match: ??_C@_0N@OGAMMJPI@CreateThread?$AA@ @ 0x003D1EE4
// match: ??_C@_0L@NHDMDOFB@PrintFloat?$AA@ @ 0x003D1EF4
// match: ??_C@_08EKFFFALG@PrintInt?$AA@ @ 0x003D1F00
// match: ??_C@_0O@EGOJIAGP@Script?5Assert?$AA@ @ 0x003D1F0C
// match: ??_C@_09NBGNFLAG@Print?5Int?$AA@ @ 0x003D1F1C
// match: ??_C@_0M@KECLNCFJ@Print?5Float?$AA@ @ 0x003D1F28
// match: ??_C@_0BP@BIPFDHGD@No?5matching?5performance?5found?$CB?$AA@ @ 0x003D1F34
// match: __real@40c90fdb @ 0x003D1F54
// match: ??_C@_0BO@GPHACEEH@GameWeapons?$CLWeapons?$CLMark2Frag?$AA@ @ 0x003D1F58
// match: ??_C@_0CF@PGPEODNH@GameWeapons?$CLWeapons?$CLStielhandgre@ @ 0x003D1F78
// match: __real@408f400000000000 @ 0x003D1FA0
// match: ??_C@_0BP@HAEMNPFK@Set?5flag?5?$CFx?0?5flag?5field?5now?5?$CFx?$AA@ @ 0x003D1FA8
// match: ??_C@_0CB@JLOJANBO@Clear?5flag?5?$CFx?0?5flag?5field?5now?5?$CFx@ @ 0x003D1FC8
// match: __real@43e10000 @ 0x003D1FEC
// match: __real@4852f000 @ 0x003D1FF0
// match: __real@44ca4ec5 @ 0x003D1FF4
// match: ??_C@_0BK@NLDKKJNA@This?5entity?5has?5no?5wings?$CB?$AA@ @ 0x003D1FF8
// match: ??_C@_0O@DHECLDDF@TaskCompleted?$AA@ @ 0x003D2014
// match: ??_C@_0BL@KBFGGEJC@SetTaskCommand_TurnToPoint?$AA@ @ 0x003D2024
// match: ??_C@_0BP@BFPLINEM@SetTaskCommand_TeleportToPoint?$AA@ @ 0x003D2040
// match: ??_C@_0M@KKDLFCOJ@SetIncoming?$AA@ @ 0x003D2060
// match: __real@3f7fff58 @ 0x003D206C
// match: __real@bf7fff58 @ 0x003D2070
// match: ??_C@_06BJBFBFHM@0x?$CF08x?$AA@ @ 0x003D2074
// match: __real@42040000 @ 0x003D207C
// match: ??_C@_0BJ@OLJGFNIA@No?5matching?5Scene?5found?$CB?$AA@ @ 0x003D2080
// match: ??_C@_0DG@ICCPMINH@StartPrimedAudioStream?3?5Invalid?5@ @ 0x003D209C
// match: ??_C@_0DG@DINHIFI@PrimeAudioStream?3Invalid?5Voice?5T@ @ 0x003D20D4
// match: ??_C@_0DM@CMNDMMCO@PrimeAudioStream?3?5Alias?50x?$CFx?0?50x@ @ 0x003D210C
// match: ??_C@_0DF@OICGHOAF@PrimeAudioStream?3?5God?5Asset?50x?$CFx@ @ 0x003D2148
// match: ??_C@_0KJ@NODDCKJI@EfuncPlaySound?3?5Error?$CB?5This?5God?5@ @ 0x003D2180
// match: ??_C@_0EC@GHAPMKMI@EfuncPlaySound?3?5Error?$CB?5This?5Soun@ @ 0x003D2230
// match: ??_C@_0LG@DPFLDGOM@EfuncPlaySoundOnNamedEntity?3?5Err@ @ 0x003D2278
// match: ??_C@_0HM@LPGKNII@EfuncPlayIndexSound?3?5WARNING?$CB?5En@ @ 0x003D2330
// match: ??_C@_0JN@LFGFNOKF@EfuncPlayIndexSound?3?5WARNING?$CB?5En@ @ 0x003D23B0
// match: ??_C@_0FE@EMKJOLBD@EfuncPlayIndexSound?3?5Error?$CB?5This@ @ 0x003D2450
// match: ??_C@_0IJ@IGICDPKP@EfuncPlayIndexSoundOnNamedEntity@ @ 0x003D24A8
// match: ??_C@_0KK@ILGLKOKB@EfuncPlayIndexSoundOnNamedEntity@ @ 0x003D2538
// match: ??_C@_0GB@JJCDPEDO@EfuncPlayIndexSoundOnNamedEntity@ @ 0x003D25E8
// match: __real@0000000000000000 @ 0x003D2650
// match: ??_C@_0P@BGMHHHHB@0x?$CF08x?0?50x?$CF08x?$AA@ @ 0x003D2658
// match: __real@3f5db22d @ 0x003D2668
// match: ??_C@_0EC@PJKLDHJE@Attempting?5to?5set?5the?5camera?5ali@ @ 0x003D2670
// match: ??_C@_0N@MNNEHJFD@IHaveArrived?$AA@ @ 0x003D26B4
// match: ??_C@_0DL@LKEKDAMP@Attempting?5to?5set?5the?5camera?5spl@ @ 0x003D26C4
// match: ??_C@_0EP@OLOOEPEJ@GetDistanceFromCurrentCoverPoint@ @ 0x003D2700
// match: __ehhandler$?sub_4AB90@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B394
// match: __ehhandler$?sub_4AB90@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B39C
// match: __ehhandler$?sub_4B490@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B3B8
// match: __ehhandler$?sub_4B490@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B3C0
// match: __ehhandler$?sub_509C0@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B3DC
// match: __ehhandler$?sub_509C0@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B3E4
// match: __ehhandler$?sub_50AE0@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B400
// match: __ehhandler$?sub_50AE0@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B408
// match: __ehhandler$?sub_54640@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B424
// match: __ehhandler$?sub_54640@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B42C
// match: __ehhandler$?sub_542E0@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B448
// match: __ehhandler$?sub_542E0@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B450
// match: __ehhandler$?sub_547E0@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B46C
// match: __ehhandler$?sub_547E0@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B474
// match: __ehhandler$?sub_508A0@@YAXIPAUtype_44350@@@Z>1>8 @ 0x0041B490
// match: __ehhandler$?sub_508A0@@YAXIPAUtype_44350@@@Z>1 @ 0x0041B498
// match: .CRT$XCU+0 @ 0x00426DA0
// match: ?String1@@3PAUtype_4276E0@@A @ 0x004276E0
// match: ?flt_428A08@@3MA @ 0x00428A08
// match: ?flt_428A0C@@3MA @ 0x00428A0C
// match: ?flt_428A10@@3MA @ 0x00428A10
// match: ?flt_428A14@@3MA @ 0x00428A14
// match: ?flt_428A18@@3MA @ 0x00428A18
// match: ?flt_428A1C@@3MA @ 0x00428A1C
// match: ?flt_428A20@@3MA @ 0x00428A20
// match: ?flt_428A24@@3MA @ 0x00428A24
// match: ?dword_428A28@@3MA @ 0x00428A28
// match: ?dword_428A2C@@3HA @ 0x00428A2C

// match: _$E2 @ 0x00309940
// match: sub_441B0 @ 0x000441B0
// sp-match: sub_441B0 @ 0x00033050

// The function of the command named arg_0 (any case), 0 for none.
type_4276E0_fn sub_441B0(const RwChar *arg_0)
{
    RwInt32 var_4;

    SCRIPT_CHECK(arg_0 != 0);
    var_4 = 0;
    while (String1[var_4].unk_00 != 0) {
        if (_strcmpi(String1[var_4].unk_00, arg_0) == 0)
            return String1[var_4].unk_04;
        var_4++;
    }
    return 0;
}

#ifdef CODFH_DRAW_TRIGGERS
// (port/src/debug/trigtools.cpp: the VM tab's log: a failed script check, with the running
// script's place; and the scripts' prints with their values, which the release build drops)
void TrigWebScriptPrint(type_67620 *pScript, const RwChar *pszWhat, type_44350 *pCall, RwInt32 nFloat);
#endif
#ifndef CODFH_SP // single player defines it in include/types/type_44350.h

// match: sub_44220 @ 0x00044220
// sp-match: sub_44220 @ 0x00032F30
// The script debugger's hook: with arg_0 clear, looks up what the debugged
// script's object is running (for a breakpoint to show).
void sub_44220(bool arg_0)
{
    type_67620 *stk_18;
    type_3DF8D8 *l14;
    RwInt32 var_10;
    RwUInt8 *ebp_C;
    type_712B0 *v8;
    type_3D2E7C *var_4;

#ifdef CODFH_DRAW_TRIGGERS
    if (arg_0 == 0)
        TrigWebScriptCheck();
#endif
    if (arg_0 == 0 && dword_449328 != 0) {
        stk_18 = dword_449328;
        var_4 = stk_18->vf_024();
        if (var_4 != 0) {
            v8 = var_4->sub_712B0();
            if (v8 != 0) {
                var_10 = 0;
                ebp_C = 0;
                if (v8->unk_28.unk_00 != 0 || v8->unk_28.unk_04 != 0) {
                    l14 = sub_198800(&v8->unk_28);
                    if (l14 != 0)
                        var_10 = l14->unk_14;
                }
                if (v8->unk_60 != 0)
                    ebp_C = v8->unk_60;
            }
        }
    }
}
#endif

// An inline single player calls out of line (SP 0x77949, 0x9EC5B); this file emits the copy:
// sp-match: ?is_blocked@AIData@@QAEHXZ @ 0x00032F80

// match: sub_442D0 @ 0x000442D0
// sp-match: sub_442D0 @ 0x000330E0
// "AssertValue": reports "Script Assert" when its argument is 0.
void sub_442D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    RwInt32 var_4;

    local_8 = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    if (var_4 == 0) {
        sub_6B060(local_8, "Script Assert", 0);
        SCRIPT_CHECK(var_4 != 0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_44350 @ 0x00044350
// sp-match: sub_44350 @ 0x00032EA0
// Ends the call arg_0: pops its arguments and pushes its results from arg_4.
void sub_44350(type_44350 *arg_0, void *arg_4)
{
    if (arg_4 != 0) {
        dword_449318 -= arg_0->unk_0C - arg_0->unk_14;
        memcpy(dword_449318 - arg_0->unk_14, arg_4, arg_0->unk_14 * sizeof(RwInt32));
    } else {
        dword_449318 -= arg_0->unk_0C;
    }
}

// match: sub_443C0 @ 0x000443C0
// sp-match: sub_443C0 @ 0x00033170
// "PrintInt".
void sub_443C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
#ifdef CODFH_DRAW_TRIGGERS
    TrigWebScriptPrint(var_4, "PrintInt", arg_4, 0);
#endif
    sub_6B060(var_4, "Print Int", 0);
    sub_44350(arg_4, 0);
}

// match: sub_44400 @ 0x00044400
// sp-match: sub_44400 @ 0x000331B0
// "PrintFloat".
void sub_44400(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
#ifdef CODFH_DRAW_TRIGGERS
    TrigWebScriptPrint(var_4, "PrintFloat", arg_4, 1);
#endif
    sub_6B060(var_4, "Print Float", 0);
    sub_44350(arg_4, 0);
}

// match: sub_44440 @ 0x00044440
// sp-match: sub_44440 @ 0x000331F0
// "BitAnd".
void sub_44440(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = local_8 & varC;
    sub_44350(arg_4, &var_4);
}

// match: sub_444C0 @ 0x000444C0
// sp-match: sub_444C0 @ 0x00033250
// "BitOr".
void sub_444C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = local_8 | varC;
    sub_44350(arg_4, &var_4);
}

// match: sub_44540 @ 0x00044540
// sp-match: sub_44540 @ 0x000332B0
// "BitNot".
void sub_44540(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = ~local_8;
    sub_44350(arg_4, &var_4);
}

// match: sub_44590 @ 0x00044590
// sp-match: sub_44590 @ 0x00033310
// "BitLShift".
void sub_44590(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = local_8 << varC;
    sub_44350(arg_4, &var_4);
}

// match: sub_44610 @ 0x00044610
// sp-match: sub_44610 @ 0x00033370
// "BitRShift".
void sub_44610(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = local_8 >> varC;
    sub_44350(arg_4, &var_4);
}

// match: sub_44690 @ 0x00044690
// sp-match: sub_44690 @ 0x000333D0
// "Modulo".
void sub_44690(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = local_8 % varC;
    sub_44350(arg_4, &var_4);
}

// match: sub_44710 @ 0x00044710
// sp-match: sub_44710 @ 0x00033430
// "Fabs".
void sub_44710(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwReal var_4;

    local_8 = *(RwReal *)&SCRIPT_ARG(arg_4, 1);
    var_4 = (RwReal)fabs(local_8);
    sub_44350(arg_4, &var_4);
}

// match: sub_44770 @ 0x00044770
// sp-match: sub_44770 @ 0x00033490
// "Sqrt".
void sub_44770(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwReal var_4;

    local_8 = *(RwReal *)&SCRIPT_ARG(arg_4, 1);
    var_4 = (RwReal)sqrt(local_8);
    sub_44350(arg_4, &var_4);
}

// match: sub_447D0 @ 0x000447D0
// sp-match: sub_447D0 @ 0x000334F0
// "Abs".
void sub_447D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    var_4 = abs(var_4);
    sub_44350(arg_4, &var_4);
}

// match: sub_44820 @ 0x00044820
// sp-match: sub_44820 @ 0x00033550
// "CreateThread": starts a thread (its two arguments) on the object's thread
// manager and returns its id.
void sub_44820(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    RwInt32 l10;
    type_6EE50_thread *local_C;
    type_67620 *lv_8;
    type_6EE50 *var_4;

    l10 = SCRIPT_ARG(arg_4, 1);
    var18 = SCRIPT_ARG(arg_4, 2);
    lv_8 = sub_67620(arg_0);
    SCRIPT_CHECK(lv_8->vf_030() != 0);
    var_4 = lv_8->vf_030();
    local_C = ((type_6EE50_thread *)((type_3D2DB8 *)var_4)->sub_6EE50(l10, var18));
    SCRIPT_CHECK(local_C != 0);
    var_1C = local_C->unk_04;
    stk_14 = var_1C;
    sub_44350(arg_4, &stk_14);
}

// match: sub_44900 @ 0x00044900
// sp-match: sub_44900 @ 0x00033660
// "CreateSoldier": unless game flag 21 is set, creates a soldier for the
// object's entity (sub_134B40); returns 0.
void sub_44900(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3D2E7C *ebp_C;
    RwInt32 v8;
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    if (!RWS::DebugSwitches::GetSwitch(0x15)) {
        ebp_C = var_4->vf_024();
        var_10 = ebp_C->unk_10;
        sub_134B40(var_10);
    }
    v8 = 0;
    sub_44350(arg_4, &v8);
}

// match: sub_44970 @ 0x00044970
// sp-match: sub_44970 @ 0x000336E0
// "CreateTank": likewise with a tank (sub_155470).
void sub_44970(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3D2E7C *ebp_C;
    RwInt32 v8;
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    if (!RWS::DebugSwitches::GetSwitch(0x15)) {
        ebp_C = var_4->vf_024();
        var_10 = ebp_C->unk_10;
        sub_155470((type_712B0 *)var_10);
    }
    v8 = 0;
    sub_44350(arg_4, &v8);
}

// match: sub_449E0 @ 0x000449E0
// sp-match: sub_449E0 @ 0x00033760
// "ControllerShake": its last argument in seconds.
void sub_449E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt16 var_10;
    RwInt16 ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = SCRIPT_ARG(arg_4, 2);
    var_10 = SCRIPT_ARGT<RwInt16>(arg_4, 3);
    ebp_C = (RwInt16)(SCRIPT_ARGT<RwReal>(arg_4, 4) * 60.0f);
    unk_4B9308.sub_EED30(var_4, v8, var_10, ebp_C);
    sub_44350(arg_4, 0);
}

// match: sub_44AD0 @ 0x00044AD0
// sp-match: sub_44AD0 @ 0x000337D0
// "CameraShake": shakes player 0's camera, its second argument in seconds
// and its third per second.
void sub_44AD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwReal var_10;
    type_10F710 *ebp_C;
    RwReal v8;
    RwReal var_4;

    v8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10 = SCRIPT_ARGT<RwReal>(arg_4, 2) * 60.0f;
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 3) / 60.0f;
    ebp_C = (type_10F710 *)sub_1745A0(0);
    if (ebp_C != 0) {
        l14 = ebp_C->unk_2110.sub_D4910();
        if (l14 != 0)
            ((type_3DD948 *)l14)->sub_175E50(v8, var_10, var_4);
    }
    sub_44350(arg_4, 0);
}

// match: sub_44BB0 @ 0x00044BB0
// sp-match: sub_44BB0 @ 0x00033870
// "TimeScale": slows time to its second argument (per second) while its
// first is 0.2f's bit pattern, else restores it.
void sub_44BB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
#ifdef CODFH_SP // single player compares the first argument as a real with 0.2f (SP 0x33870: fucompp)
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 2) * 60.0f;
    if (var_4 == 0.2f) {
#else
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 2) * 60.0f;
    if (var_4 == 0x3E4CCCCD) {
#endif
        if (dword_4B87DC != 3)
            dword_4B87DC = 1;
        if (dword_4B87DC != 3 && dword_4B87DC != 4)
            dword_42928C = local_8;
    } else if (dword_4B87DC != 3) {
        dword_4B87DC = 0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_44C70 @ 0x00044C70
// sp-match: sub_44C70 @ 0x00033910
// "PlayerShock".
void sub_44C70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_10F710 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_8 = (type_10F710 *)sub_1745A0(var_4);
    if (local_8 != 0)
        local_8->sub_1109A0(varC, 1.0f);
    sub_44350(arg_4, 0);
}

// match: sub_44D00 @ 0x00044D00
// sp-match: sub_44D00 @ 0x00033970
// "RenderFadeOut": fades the screen out over arg 1 seconds, unless one of
// the game's pause and menu bits (1, 2, 3, 5, 6, 7 of dword_4B86F8) is set.
void sub_44D00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_4;

    // The argument goes through the FPU (fld/fstp), which a float copy does
    // not give; a round trip through RwDouble does.
    var_4 = (RwReal)(RwDouble)SCRIPT_ARGT<RwReal>(arg_4, 1);
    if (!((dword_4B86F8 >> 6) & 1) && !((dword_4B86F8 >> 5) & 1) && !((dword_4B86F8 >> 7) & 1)
        && !((dword_4B86F8 >> 2) & 1) && !((dword_4B86F8 >> 1) & 1) && !((dword_4B86F8 >> 3) & 1))
    {
        sub_124EE0(var_4, 1);
    }
    sub_44350(arg_4, 0);
}

// match: sub_44DA0 @ 0x00044DA0
// sp-match: sub_44DA0 @ 0x000339B0
// "RenderFadeIn": fades the screen in over arg 1 seconds.
void sub_44DA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_4;

    var_4 = (RwReal)(RwDouble)SCRIPT_ARGT<RwReal>(arg_4, 1);
    sub_124EE0(var_4, 0);
    sub_44350(arg_4, 0);
}

// match: sub_44DF0 @ 0x00044DF0
// sp-match: sub_44DF0 @ 0x000339F0
// "SetMotionBlur": its second and third arguments in seconds, as frames
// below 256.
void sub_44DF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    RwReal var_10;
    RwReal ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1) & 0xFF;
    var_10 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_4 = (RwInt32)(var_10 * 60.0f) & 0xFF;
    l14 = (RwInt32)(ebp_C * 60.0f) & 0xFF;
    sub_128C20(v8, (RwReal)var_4, (RwReal)l14);
    sub_44350(arg_4, 0);
}

// match: sub_44ED0 @ 0x00044ED0
// sp-match: sub_44ED0 @ 0x00033A90
// "TimeToTicks": its argument in seconds as whole frames.
void sub_44ED0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = (RwReal)(RwInt32)(var_4 * 60.0f);
    sub_44350(arg_4, &local_8);
}

// match: sub_44F30 @ 0x00044F30
// sp-match: sub_44F30 @ 0x00033B00
// "SetFogDistance".
void sub_44F30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwReal var_4;

    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 1) * 100.0f;
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2) * 60.0f;
    sub_128C80(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_44FC0 @ 0x00044FC0
// sp-match: sub_44FC0 @ 0x00033B60
// "SetClipDistance".
void sub_44FC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwReal var_4;

    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 1) * 100.0f;
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2) * 60.0f;
    sub_128CD0(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_45050 @ 0x00045050
// sp-match: sub_45050 @ 0x00033BC0
// "SetFogType": 1 to 3, else 0.
void sub_45050(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    switch (var_4) {
    default:
        dword_4CF450 = 0;
        break;
    case 1:
        dword_4CF450 = 1;
        break;
    case 2:
        dword_4CF450 = 2;
        break;
    case 3:
        dword_4CF450 = 3;
    }
    sub_44350(arg_4, 0);
}

type_3D3548 *sub_45170(RwUInt32 arg_0);

// match: sub_450E0 @ 0x000450E0
// sp-match: sub_450E0 @ 0x00033C50
// "SetRenderPriority": 0 to 2.
void sub_450E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK2(local_8 >= 0 && local_8 <= 2);
    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        var_4->unk_29C = local_8;
    sub_44350(arg_4, 0);
}

// match: sub_45170 @ 0x00045170
// sp-match: sub_45170 @ 0x00032FA0
// The entity of the object arg_0 (its type_3D2E7C's sub_71300).
type_3D3548 *sub_45170(RwUInt32 arg_0)
{
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_024() != 0);
    SCRIPT_CHECK(var_4->vf_024()->sub_71300() != 0);
    return var_4->vf_024()->sub_71300();
}

// match: sub_451E0 @ 0x000451E0
// sp-match: sub_451E0 @ 0x00033CE0
// "SetPriorityCollision".
void sub_451E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_45170(arg_0);
    if (local_8 != 0) {
        SCRIPT_CHECK2(local_8->vf_008() != 0 || local_8->vf_024() != 0);
        local_8->vf_1AC(var_4);
    }
    sub_44350(arg_4, 0);
}

// match: sub_45280 @ 0x00045280
// sp-match: sub_45280 @ 0x00033D80
// "SetEntityScale": scales the entity, its animations, its size and its
// atomics' bounding spheres.
void sub_45280(RwUInt32 arg_0, type_44350 *arg_4)
{
    RpAtomic *var_10;
    type_7C8D0 *ebp_C;
    type_3D3548 *v8;
    RwReal var_4;

    {
        // A local the image reserves and never uses, ahead of var_18 and
        // var_1C (block scopes take slots in source order).
        RwInt32 unused_0;
    }
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    v8 = sub_45170(arg_0);
    if (v8 != 0) {
        ebp_C = v8->unk_284;
        if (ebp_C != 0)
            ebp_C->unk_28 = var_4;
        if (v8->vf_008() != 0) {
            type_3D3548 *var_18 = v8->vf_008();

            ebp_C = var_18->unk_28C;
            if (ebp_C != 0)
                ebp_C->unk_28 = var_4;
        }
        if (v8->vf_024() != 0) {
            type_3DDB98 *var_1C = v8->vf_024();

            ebp_C = var_1C->unk_28C;
            if (ebp_C != 0)
                ebp_C->unk_28 = var_4;
        }
        v8->unk_4C = var_4 * v8->unk_4C;
        v8->unk_48 = var_4 * v8->unk_48;
        v8->unk_80 = var_4;
        var_10 = v8->Clump_ResolvePrimaryAtomic();
        if (var_10 != 0)
            var_10->boundingSphere.radius = var_4 * var_10->boundingSphere.radius;
        var_10 = v8->unk_250.unk_08;
        if (var_10 != 0) {
            var_10->boundingSphere.radius = var_4 * var_10->boundingSphere.radius;
            var_10->boundingSphere.center.y = v8->unk_48 * 0.5f;
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_453F0 @ 0x000453F0
// sp-match: sub_453F0 @ 0x00033E80
// "CreateMyChild": unless game flag 21 is set, the handle of the trigger's
// child entity (0 without one).
void sub_453F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_1C;
    type_3D2E7C *var18;
    type_3D3548 *stk_14;
    RwUInt32 l10;
    type_712B0 *local_C;
    type_67620 *lv_8;
    type_3D2E7C *var_4;

    l10 = 0;
    lv_8 = sub_67620(arg_0);
    var_4 = lv_8->vf_024();
    SCRIPT_CHECK(var_4 != 0);
    local_C = var_4->sub_712B0();
    if (!RWS::DebugSwitches::GetSwitch(0x15)) {
        stk_14 = local_C->vf_020();
        if (stk_14 != 0) {
            var18 = stk_14->vf_098();
            if (var18 != 0) {
                var_1C = var18->unk_04;
                l10 = var_1C;
            }
        }
    }
    sub_44350(arg_4, &l10);
}

// match: sub_454A0 @ 0x000454A0
// sp-match: sub_454A0 @ 0x00033F60
// "DestroySelf": frees the entity and ends the object with the argument.
void sub_454A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    type_3D3548 *var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_67620(arg_0);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK2(v8 != 0);
    var_4 = sub_45170(arg_0);
    sub_F12A0(var_4, 0);
    v8->sub_71100(var_10);
    sub_44350(arg_4, 0);
}

// match: sub_45540 @ 0x00045540
// sp-match: sub_45540 @ 0x00034000
// "GetPrimaryAnimationDuration": 0 without one.
void sub_45540(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_7C8D0 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    var_4 = 0.0f;
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK2(local_8 != 0);
    varC = local_8->unk_284;
    if (varC != 0)
        var_4 = varC->sub_7C8D0();
    sub_44350(arg_4, &var_4);
}

// match: sub_455A0 @ 0x000455A0
// sp-match: sub_455A0 @ 0x000340B0
// "SetFadeOut".
void sub_455A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK2(local_8 != 0);
    local_8->sub_D3910(var_4, 1);
    sub_44350(arg_4, 0);
}

// match: sub_45610 @ 0x00045610
// sp-match: sub_45610 @ 0x00034140
// "SetFadeLevel".
void sub_45610(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // shape: the level read as a real and passed as its bits (SP 0x34140: fld/fstp)
    RwReal local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK2(var_4 != 0);
    var_4->sub_D39F0(*(RwInt32 *)&local_8);
#else
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK2(var_4 != 0);
    var_4->sub_D39F0(local_8);
#endif
    sub_44350(arg_4, 0);
}

// match: sub_45680 @ 0x00045680
// sp-match: sub_45680 @ 0x000341D0
// "SetMyWidthHeight".
void sub_45680(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    RwReal local_8;
    type_3D3548 *var_4;

    varC = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK2(var_4 != 0);
    var_4->unk_4C = varC;
    var_4->unk_48 = local_8;
    sub_44350(arg_4, 0);
}

// match: sub_45720 @ 0x00045720
// sp-match: sub_45720 @ 0x00034270
// "GetMyTriggerPointer".
void sub_45720(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_712B0 *local_8;
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_024() != 0);
    local_8 = var_4->vf_024()->sub_712B0();
    SCRIPT_CHECK(local_8 != 0);
    varC = local_8->unk_3C;
    sub_44350(arg_4, &varC);
}

// match: sub_457A0 @ 0x000457A0
// sp-match: sub_457A0 @ 0x00034360
// "GetMyTriggerMetric": metric 0 to 2 of the trigger.
void sub_457A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    RwInt32 v8;
    RwReal var_4;

    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    var_10 = ebp_C->vf_024()->sub_712B0();
    SCRIPT_CHECK(var_10 != 0);
    v8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(v8 >= 0 && v8 <= 2);
    var_4 = 0.0f;
    switch (v8) {
    case 0:
        var_4 = var_10->unk_48;
        break;
    case 1:
        var_4 = var_10->unk_4C;
        break;
    case 2:
        var_4 = var_10->unk_50;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_458A0 @ 0x000458A0
// sp-match: sub_458A0 @ 0x000344D0
// "GetMyTriggerVectorComponent": component arg 2 (x, y, z) of the row arg 1
// (at, right, up) of its trigger's matrix, orthonormalised.
void sub_458A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_712B0 *var_8;
    RwV3d *var_C;
    RwReal var_10;
    RwInt32 var_14;
    RwInt32 var_18;
    RwMatrix var_60;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_024() != 0);
    var_8 = var_4->vf_024()->sub_712B0();
    SCRIPT_CHECK(var_8 != 0);
    var_C = 0;
    var_10 = 0.0f;
    var_14 = SCRIPT_ARG(arg_4, 1);
    var_18 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(var_14 >= 0 && var_14 <= 2);
    SCRIPT_CHECK(var_18 >= 0 && var_18 <= 2);
    var_60 = *(RwMatrix *)var_8->unk_60;
    RwMatrixOrthoNormalize(&var_60, &var_60);
    switch (var_14)
    {
    case 0:
        var_C = &var_60.at;
        break;
    case 1:
        var_C = &var_60.right;
        break;
    case 2:
        var_C = &var_60.up;
        break;
    }
    switch (var_18)
    {
    case 0:
        var_10 = var_C->x;
        break;
    case 1:
        var_10 = var_C->y;
        break;
    case 2:
        var_10 = var_C->z;
        break;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_45A50 @ 0x00045A50
// sp-match: sub_45A50 @ 0x000346E0
// "SetMyTriggerActionIcon".
void sub_45A50(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 ebp_9;
    type_712B0 *local_8;
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_024() != 0);
    ebp_9 = SCRIPT_ARGT<RwUInt8>(arg_4, 1);
    local_8 = var_4->vf_024()->sub_712B0();
    SCRIPT_CHECK(local_8 != 0);
    local_8->sub_BBF80(ebp_9);
    sub_44350(arg_4, 0);
}

// match: sub_45AF0 @ 0x00045AF0
// sp-match: sub_45AF0 @ 0x000347C0
// "SetMyTriggerPosition": each coordinate is checked nonzero.
void sub_45AF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal l14;
    type_712B0 *var_10;
    type_67620 *ebp_C;
    RwReal v8;
    RwReal var_4;

    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    v8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    l14 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    SCRIPT_CHECK(v8 != 0.0f);
    SCRIPT_CHECK(var_4 != 0.0f);
    SCRIPT_CHECK(l14 != 0.0f);
    var_10 = ebp_C->vf_024()->sub_712B0();
    SCRIPT_CHECK(var_10 != 0);
    var_10->sub_BE710(v8, var_4, l14);
    sub_44350(arg_4, 0);
}

// match: sub_45C60 @ 0x00045C60
// sp-match: sub_45C60 @ 0x000349B0
// "RestoreMyTriggerPosition".
void sub_45C60(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *local_8;
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_024() != 0);
    local_8 = var_4->vf_024()->sub_712B0();
    SCRIPT_CHECK(local_8 != 0);
    local_8->sub_BE810();
    sub_44350(arg_4, 0);
}

// match: sub_45CD0 @ 0x00045CD0
// sp-match: sub_45CD0 @ 0x00034A70
// "DotProductVectors": of its first three arguments and its last three.
void sub_45CD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d var_1C;
    RwV3d local_10;
    RwReal var_4;

    local_10.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_10.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_10.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_1C.x = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_1C.y = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_1C.z = SCRIPT_ARGT<RwReal>(arg_4, 6);
    var_4 = RwV3dDotProduct(&local_10, &var_1C);
    sub_44350(arg_4, &var_4);
}

// match: sub_45E00 @ 0x00045E00
// sp-match: sub_45E00 @ 0x00034B10
// "CrossProductVectorComponent": component 0 to 2 (its seventh argument) of
// the cross product of its first three arguments and the next three.
void sub_45E00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d bp_2C;
    RwV3d ebp_20;
    RwV3d lv_14;
    RwInt32 local_8;
    RwReal var_4;

    lv_14.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    lv_14.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    lv_14.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    ebp_20.x = SCRIPT_ARGT<RwReal>(arg_4, 4);
    ebp_20.y = SCRIPT_ARGT<RwReal>(arg_4, 5);
    ebp_20.z = SCRIPT_ARGT<RwReal>(arg_4, 6);
    RwV3dCrossProduct(&bp_2C, &lv_14, &ebp_20);
    local_8 = SCRIPT_ARG(arg_4, 7);
    SCRIPT_CHECK(local_8 >= 0 && local_8 <= 2);
    switch (local_8) {
    case 0:
        var_4 = bp_2C.x;
        break;
    case 1:
        var_4 = bp_2C.y;
        break;
    case 2:
        var_4 = bp_2C.z;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_45FD0 @ 0x00045FD0
// sp-match: sub_45FD0 @ 0x00034C50
// "GetThisStateMachinePointer": the object's handle.
void sub_45FD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_4;

    var_4 = arg_0;
    sub_44350(arg_4, &var_4);
}

// match: sub_45FF0 @ 0x00045FF0
// sp-match: sub_45FF0 @ 0x00034CA0
// "GetMyAIObjectPointer": the object's type_3D2E7C's handle.
void sub_45FF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D2E7C *local_8;
    RwUInt32 var_4;

    varC = sub_67620(arg_0);
    local_8 = varC->vf_024();
    var_4 = local_8->get_unk_04();
    sub_44350(arg_4, &var_4);
}

// match: sub_46040 @ 0x00046040
// sp-match: sub_46040 @ 0x00048890
// "GetEntityHandle": the id of the entity the object under the key (its
// argument, two slots) holds, for an object with flag 2; 0 when the entity
// is gone.
void sub_46040(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 stk_18;
    RwInt32 l14;
    type_3DFEEC *var_10;
    type_3D3548 *ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        var_10 = (type_3DFEEC *)var_4;
        ebp_C = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
        if (ebp_C != 0) {
            l14 = ebp_C->unk_384;
            if ((var_10->unk_10 & 2) != 0)
                sub_44350(arg_4, &l14);
            else
                SCRIPT_CHECK(0);
        } else {
            stk_18 = 0;
            sub_44350(arg_4, &stk_18);
        }
    } else {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_46120 @ 0x00046120
// sp-match: sub_46120 @ 0x00034D00
// "GetTaskReturnRegister".
void sub_46120(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    RwInt32 local_8;
    type_46120 *var_4;

    varC = sub_67620(arg_0);
    var_4 = varC->vf_034();
    SCRIPT_CHECK(var_4 != 0);
    local_8 = var_4->get_unk_120();
    sub_44350(arg_4, &local_8);
}

// match: sub_46180 @ 0x00046180
// sp-match: sub_46180 @ 0x00034DA0
// "GetWakeUpMessageID".
void sub_46180(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    RwInt32 local_8;
    type_46120 *var_4;

    varC = sub_67620(arg_0);
    var_4 = varC->vf_034();
    SCRIPT_CHECK(var_4 != 0);
    local_8 = var_4->get_unk_11C();
    sub_44350(arg_4, &local_8);
}

// match: sub_461E0 @ 0x000461E0
// sp-match: sub_461E0 @ 0x00034E40
// "SetPerformanceValue": value arg 2 at index arg 1 of the entity's
// performance values.
void sub_461E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_08C(0, 0);
    var_10[v8] = (RwUInt8)var_4;
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46280 @ 0x00046280
// sp-match: sub_46280 @ 0x00034EA0
// "SetHitDeathValue".
void sub_46280(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt8 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_0F0();
    var_10[v8] = (RwInt8)var_4;
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46320 @ 0x00046320
// sp-match: sub_46320 @ 0x00034F00
// "SetSpecialIdlePerformanceValue".
void sub_46320(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_08C(0, 1);
    var_10[v8] = (RwUInt8)var_4;
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_463C0 @ 0x000463C0
// sp-match: sub_463C0 @ 0x00034F60
// "SetupAssassinationValues": fills the entity's hit-death values (for an
// entity of the vf_008 or vf_024 subclass).
void sub_463C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwUInt8 *ebp_C;
    RwInt8 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    v8 = 0;
    if (var_4 != 0 && var_4->vf_008() != 0)
        v8 = var_4->vf_0F0();
    else if (var_4 != 0 && var_4->vf_024() != 0)
        v8 = var_4->vf_0F0();
    if (v8 != 0) {
        ebp_C = var_4->vf_08C(1, 0);
        v8[0] = ebp_C[3];
        v8[1] = (RwUInt8)var_4->vf_0AC();
        v8[2] = (RwInt8)(RpRandom() % 9);
        v8[3] = 1;
        v8[4] = (RwInt8)(RpRandom() % 4);
        v8[5] = v8[4];
        for (var_10 = 0; var_10 < 6; var_10++)
            v8[var_10 + 6] = 1;
        var_4->vf_178(-1);
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_464F0 @ 0x000464F0
// sp-match: sub_464F0 @ 0x00035020
// "GetPerformanceValue": the value at index arg 1.
void sub_464F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = -1;
    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_08C(0, 0);
    var_4 = var_10[v8];
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46570 @ 0x00046570
// sp-match: sub_46570 @ 0x000350A0
// "SetPerformanceMap": plays the performance dword_4B92FC finds in the map
// with the id arg 1.
void sub_46570(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *var_1C;
    type_6D380 *var18;
    type_ED340 *stk_14;
    RwInt32 l10;
    type_4CFE30 *local_C;
    type_3D3548 *lv_8;
    RwInt16 var_4;

    l10 = SCRIPT_ARG(arg_4, 1);
    if (l10 >= 0 && l10 < 2000)
        local_C = dword_4CFE30[l10];
    else
        local_C = 0;
    SCRIPT_CHECK((var_1C = local_C->unk_1A0) != 0);
    lv_8 = sub_45170(arg_0);
    var18 = lv_8->vf_090();
    SCRIPT_CHECK(var18 != 0);
    stk_14 = dword_4B92FC;
    SCRIPT_CHECK(stk_14 != 0);
    var_4 = stk_14->sub_ED340(lv_8, var_1C, 0, 0);
    if (var_4 != -1)
        ((type_3D2CD0 *)var18)->sub_6D380(var_4, 0, 0, 0, 0, 0, 0, 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46680 @ 0x00046680
// sp-match: sub_46680 @ 0x00035200
// "SetPerformanceID": plays the performance with the id arg 1 (none for -1).
void sub_46680(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_6D380 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_45170(arg_0);
    varC = local_8->vf_090();
    SCRIPT_CHECK2(varC != 0);
    if (var_4 != -1)
        ((type_3D2CD0 *)varC)->sub_6D380(var_4, 0, 0, 0, 0, 0, 0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_46720 @ 0x00046720
// sp-match: sub_46720 @ 0x000352B0
// "PlayHitDeathAnim": plays the hit-death performance of the map with the id
// arg 1; 1 when there is one.
void sub_46720(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *local_24;
    type_6D380 *local_20;
    RwInt16 var_1C;
    RwInt32 var18;
    type_4CFE30 *stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    type_ECDA0 *lv_8;
    RwInt32 var_4;

    var18 = SCRIPT_ARG(arg_4, 1);
    if (var18 >= 0 && var18 < 2000)
        stk_14 = dword_4CFE30[var18];
    else
        stk_14 = 0;
    local_24 = stk_14->unk_1A0;
    l10 = sub_45170(arg_0);
    local_20 = l10->vf_090();
    lv_8 = dword_4B92D4;
    local_C = (l10->vf_174() <= 0) + 6;
    var_1C = lv_8->sub_ECDA0(l10, local_24, local_C, 0);
    if (var_1C != -1) {
        ((type_3D2CD0 *)local_20)->sub_6D380(var_1C, 0, 0, 0, 1, 1, 0, 0);
        local_20->unk_144 = 2;
        var_4 = 1;
    } else {
        var_4 = 0;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46840 @ 0x00046840
// sp-match: sub_46840 @ 0x000353B0
// "PlayHitDeathAnimDefaultData": plays the hit-death performance for a
// soldier's or a type_3DDB98's own hit-death values (with its performance
// values' bytes 2 and 3 when none matches them), keeping the partner
// performance in unk_7E2 or unk_672; 0 when there is none.
void sub_46840(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_6D380 *var_10;
    RwInt16 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->vf_090();
    SCRIPT_CHECK(var_10 != 0);
    var_4 = 1;
    ebp_C = -1;
    if ((v8->unk_2C & 0x3FFFFF0) == 0x20) {
        type_3DAFC8 *var_1C = (type_3DAFC8 *)v8;
        type_ECDA0 *var_14 = dword_4B92D4;
        RwInt32 var_18 = (v8->vf_174() <= 0) + 6;
        RwUInt8 *l20;
        type_46840_30 var_30;

        ebp_C = var_14->sub_ECDA0(var_1C, var_1C->vf_0F0(), var_18, 0);
        var_1C->unk_7E2 = var_14->sub_ECDA0(var_1C, var_1C->vf_0F0(), var_18, 1);
        if (ebp_C == -1) {
            l20 = var_1C->vf_08C(1, 0);
            var_30 = *(type_46840_30 *)var_1C->vf_0F0();
            var_30.unk_00[2] = l20[2];
            var_30.unk_00[3] = l20[3];
            ebp_C = var_14->sub_ECDA0(var_1C, &var_30, var_18, 0);
            var_1C->unk_7E2 = var_14->sub_ECDA0(var_1C, &var_30, var_18, 1);
        }
    } else if ((v8->unk_2C & 0x3FFFFF0) == 0x200000) { // not an address: entity kind bits
        type_3DDB98 *local_3C = (type_3DDB98 *)v8;
        type_ECDA0 *var_34 = dword_4B92D4;
        RwInt32 var_38 = (local_3C->vf_174() <= 0) + 6;
        RwUInt8 *bp_40;
        type_46840_30 stk_4C;

        ebp_C = var_34->sub_ECDA0(local_3C, local_3C->vf_0F0(), var_38, 0);
        local_3C->unk_672 = var_34->sub_ECDA0(local_3C, local_3C->vf_0F0(), var_38, 1);
        if (ebp_C == -1) {
            bp_40 = local_3C->vf_08C(1, 0);
            stk_4C = *(type_46840_30 *)local_3C->vf_0F0();
            stk_4C.unk_00[2] = bp_40[2];
            stk_4C.unk_00[3] = bp_40[3];
            ebp_C = var_34->sub_ECDA0(local_3C, &stk_4C, var_38, 0);
            local_3C->unk_672 = var_34->sub_ECDA0(local_3C, &stk_4C, var_38, 1);
        }
    } else {
        SCRIPT_CHECK(0);
    }
    if (ebp_C != -1) {
        ((type_3D2CD0 *)var_10)->sub_6D380(ebp_C, 0, 0, 0, 1, 1, 0, 0);
        var_10->unk_144 = 2;
    } else {
        ((type_3D2CD0 *)var_10)->sub_6DDF0(0, 0);
        var_4 = 0;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46B50 @ 0x00046B50
// sp-match: sub_46B50 @ 0x000356D0
// "GetLastHitLocation": -1 unless the entity is of the vf_008 subclass.
void sub_46B50(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt8 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = -1;
    if (local_8->vf_008() != 0) {
        varC = local_8->vf_008()->vf_0F0();
        var_4 = varC[2];
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46BC0 @ 0x00046BC0
// sp-match: sub_46BC0 @ 0x00056740
// "PlayCurrentPerformance".
void sub_46BC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = sub_45170(arg_0);
    var_4->vf_088(0);
    sub_47F90(local_8, var_4, 0, 0, 0, 0, 0);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46C20 @ 0x00046C20
// sp-match: sub_46C20 @ 0x000567A0
// "PlaySpecialIdlePerformance".
void sub_46C20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = sub_45170(arg_0);
    var_4->vf_088(1);
    sub_47F90(local_8, var_4, 0, 0, 0, 0, 0);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46C80 @ 0x00046C80
// sp-match: sub_46C80 @ 0x00056800
// "PlayCoverPointRegistrationPerformance": at the AI object's cover point,
// facing its direction, when it has one.
void sub_46C80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d fp_24;
    RwV3d stk_18;
    AIData *ebp_C;
    type_67620 *v8;
    type_3D3548 *var_4;

    v8 = sub_67620(arg_0);
    var_4 = sub_45170(arg_0);
    ebp_C = var_4->vf_120();
    if (ebp_C != 0 && ebp_C->get_unk_F60() != 0) {
        ebp_C->sub_22C80(ebp_C->get_unk_F60(), &stk_18, &fp_24);
        var_4->vf_088(0);
        sub_47F90(v8, var_4, &fp_24, &stk_18, 0, 1, 0);
    } else {
        var_4->vf_088(0);
        sub_47F90(v8, var_4, 0, 0, 0, 0, 0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46D60 @ 0x00046D60
// sp-match: sub_46D60 @ 0x00035750
// "SnapToCover": moves and turns the entity onto its AI object's cover point;
// at a mounted weapon's node (kind 0x11) a soldier also mounts the weapon it
// holds, with the result.
void sub_46D60(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    type_3DAFC8 *var_10;
    type_F8350 *ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    v8 = sub_45170(arg_0);
    var_4 = 0;
    if (v8 != 0) {
        ebp_C = v8->vf_120()->get_unk_F60();
        if (ebp_C != 0) {
            v8->vf_0C0(&ebp_C->unk_10);
            v8->vf_0D4(&ebp_C->unk_1C);
            if (ebp_C->unk_04 == 0x11) {
                var_10 = v8->vf_008();
                if (var_10 != 0) {
                    l14 = var_10->unk_618.sub_D4910();
                    SCRIPT_CHECK(l14 != 0);
                    if (l14 != 0)
                        var_4 = var_10->sub_13F590(1);
                }
            }
        }
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46E40 @ 0x00046E40
// sp-match: sub_46E40 @ 0x00035820
// "AreWeUsingAMountedWeapon": a soldier's flag unk_61C, or 1 for a player
// in the mounted weapon posture (7).
void sub_46E40(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    if (local_8 != 0 && local_8->vf_008() != 0)
        var_4 = local_8->vf_008()->get_unk_61C();
    else if (local_8 != 0 && local_8->vf_00C() != 0 && local_8->vf_00C()->get_unk_19D0() == 7)
        var_4 = 1;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_46EF0 @ 0x00046EF0
// sp-match: sub_46EF0 @ 0x000358C0
// "IsPlayerUsingAMountedWeapon": player 0 in the mounted weapon posture.
void sub_46EF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_8;
    RwInt32 var_4;

    local_8 = (type_10F710 *)sub_1745A0(0);
    var_4 = 0;
    if (local_8 != 0 && local_8->get_unk_19D0() == 7)
        var_4 = 1;
    sub_44350(arg_4, &var_4);
}

// match: sub_46F40 @ 0x00046F40
// sp-match: sub_46F40 @ 0x00035930
// "SetMyMMGToFireEvenIfICantSeeTarget".
void sub_46F40(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    if (var_4 != 0 && var_4->vf_008() != 0) {
        varC = var_4->vf_008()->get_unk_618();
        if (varC != 0)
            varC->unk_4BC = local_8;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_46FE0 @ 0x00046FE0
// sp-match: sub_46FE0 @ 0x000359A0
// "SetMyMMGYawAndPitch": sets the yaw (arg 2) and pitch (arg 3) of the
// mounted weapon of the entity with the handle arg 1 (else of the caller's
// entity): a soldier's, or the player's through unk_210C.
void sub_46FE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *stk_18;
    RwInt32 l14;
    RwReal var_10;
    type_3D3548 *ebp_C;
    RwReal v8;
    type_3DC9B0 *var_4;

    var_4 = 0;
    l14 = SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    v8 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    ebp_C = sub_D5CF0(l14);
    if (ebp_C == 0)
        ebp_C = sub_45170(arg_0);
    if (ebp_C != 0) {
        if (ebp_C->vf_008() != 0) {
            var_4 = ebp_C->vf_008()->get_unk_618();
        } else if (ebp_C->vf_00C() != 0) {
            stk_18 = ebp_C->vf_00C();
            if (stk_18->unk_1B28 != 0 && stk_18->unk_210C.sub_D4910() != 0)
                var_4 = stk_18->unk_210C.sub_D4910()->vf_028();
        }
    }
    if (var_4 != 0) {
        var_4->unk_3BC = var_10;
        var_4->unk_3B8 = v8;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_47150 @ 0x00047150
// sp-match: sub_47150 @ 0x00035A90
// "GetMyMMGMinBurstLength": 0 without a mounted weapon.
void sub_47150(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0.0f;
    if (local_8 != 0 && local_8->vf_008() != 0) {
        varC = local_8->vf_008()->get_unk_618();
        if (varC != 0)
            var_4 = varC->sub_16B5C0();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_471D0 @ 0x000471D0
// sp-match: sub_471D0 @ 0x00035B20
// "GetMyMMGMaxBurstLength".
void sub_471D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0.0f;
    if (local_8 != 0 && local_8->vf_008() != 0) {
        varC = local_8->vf_008()->get_unk_618();
        if (varC != 0)
            var_4 = varC->sub_16B620();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_47250 @ 0x00047250
// sp-match: sub_47250 @ 0x00035BB0
// "GetMyMMGMinPauseLength".
void sub_47250(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0.0f;
    if (local_8 != 0 && local_8->vf_008() != 0) {
        varC = local_8->vf_008()->get_unk_618();
        if (varC != 0)
            var_4 = varC->sub_16B680();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_472D0 @ 0x000472D0
// sp-match: sub_472D0 @ 0x00035C40
// "GetMyMMGMaxPauseLength".
void sub_472D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0.0f;
    if (local_8 != 0 && local_8->vf_008() != 0) {
        varC = local_8->vf_008()->get_unk_618();
        if (varC != 0)
            var_4 = varC->sub_16B6E0();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_47350 @ 0x00047350
// sp-match: sub_47350 @ 0x00035CD0
// "MountedWeaponReloaded": reloads the entity with the handle arg 1 when it
// is a mounted weapon (flag 0x80000 of unk_2C).
void sub_47350(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = (type_3DC9B0 *)sub_D5CF0(var_4);
    if ((local_8->unk_2C >> 19) & 1)
        local_8->sub_16A660();
    sub_44350(arg_4, 0);
}

// match: sub_473C0 @ 0x000473C0
// sp-match: sub_473C0 @ 0x00035D20
// "AttachToMountedWeapon": mounts the soldier on the entity with the handle
// arg 1, when it has a cover point or its unk_624 entity is of the vf_010
// subclass.
void sub_473C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    {
        // Six locals the image reserves and never uses, ahead of var_28
        // (block scopes take slots in source order).
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    varC = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_D5CF0(local_8);
    if (varC != 0 && varC->vf_008() != 0 && var_4 != 0) {
        AIData *var_28 = varC->vf_120();

        if (var_28->get_unk_F60() != 0
            || (varC->vf_008()->unk_624.sub_D4910() != 0
                && varC->vf_008()->unk_624.sub_D4910()->vf_010() != 0)) {
            varC->vf_008()->sub_13F4D0(var_4);
            varC->vf_008()->sub_13F590(1);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_474E0 @ 0x000474E0
// sp-match: sub_474E0 @ 0x00035DF0
// "DetachFromMountedWeapon": of a soldier or the player.
void sub_474E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0 && var_4->vf_008() != 0)
        var_4->vf_008()->sub_13F590(0);
    else if (var_4 != 0 && var_4->vf_00C() != 0)
        var_4->vf_00C()->sub_10FB70();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_47560 @ 0x00047560
// sp-match: sub_47560 @ 0x00035E60
// "AttachProp": attaches the entity of the object under the key arg 1 (two
// slots; a kind 0x2E object with flag 2) to a soldier or the vf_024
// subclass; with no key, detaches the prop as "DetachProp" does.
void sub_47560(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *var_1C;
    type_3DF8D8 *var18;
    type_3D3548 *stk_14;
    RwFrame *l10;
    type_3D3548 *local_C;
    type_3D3548 *lv_8;
    type_3DF8D8_04 *var_4;

    lv_8 = sub_45170(arg_0);
    SCRIPT_CHECK(lv_8 != 0);
    {
        // A local the image reserves and never uses (as in "DetachProp").
        RwInt32 unused_0;
    }
    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    if (var_4 == 0) {
        local_C = lv_8->vf_1F8(0);
        if (local_C != 0) {
            l10 = local_C->get_unk_340();
            RwFrameOrthoNormalize(l10);
        }
        lv_8->vf_1FC(0, 0);
        lv_8->set_unk_364(0, -1);
    } else {
        var18 = sub_198800(var_4);
        SCRIPT_CHECK(var18 != 0);
        SCRIPT_CHECK(var18->vf_008() == 0x2E);
        var_1C = (type_3DFEEC *)var18;
        SCRIPT_CHECK((var_1C->unk_10 & 2) != 0);
        stk_14 = ((type_D48D0 *)&var_1C->unk_24_id)->sub_D4910();
        // The image reserves slots for three checks' locals here, not five:
        // the last two call the hook directly (as in "AttachPropEx").
        sub_44220(stk_14 != 0);
        sub_44220(lv_8->vf_008() != 0 || lv_8->vf_024() != 0);
        lv_8->vf_1FC(stk_14, 0);
        lv_8->set_unk_364(0, 400);
    }
    sub_44350(arg_4, 0);
}


// match: sub_47700 @ 0x00047700
// sp-match: sub_47700 @ 0x000360A0
// "DetachProp": straightens the prop's frame and detaches it.
void sub_47700(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwFrame *varC;
    type_3D3548 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    local_8 = var_4->vf_1F8(0);
    if (local_8 != 0) {
        varC = local_8->get_unk_340();
        RwFrameOrthoNormalize(varC);
    }
    var_4->vf_1FC(0, 0);
    var_4->set_unk_364(0, -1);
    sub_44350(arg_4, 0);
}

// match: sub_477A0 @ 0x000477A0
// sp-match: sub_477A0 @ 0x00036140
// "AttachPropEx": "AttachProp" with arg 2 in unk_36C rather than 400 in
// unk_364.
void sub_477A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *local_20;
    type_3DF8D8 *var_1C;
    type_3D3548 *var18;
    RwFrame *stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    type_3DF8D8_04 *var_4;

    lv_8 = sub_45170(arg_0);
    SCRIPT_CHECK(lv_8 != 0);
    {
        // A local the image reserves and never uses (as in "DetachProp").
        RwInt32 unused_0;
    }
    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_C = SCRIPT_ARG(arg_4, 2);
    if (var_4 == 0) {
        l10 = lv_8->vf_1F8(0);
        if (l10 != 0) {
            stk_14 = l10->get_unk_340();
            RwFrameOrthoNormalize(stk_14);
        }
        lv_8->vf_1FC(0, 0);
        lv_8->set_unk_36C(0, -1);
    } else {
        var_1C = sub_198800(var_4);
        SCRIPT_CHECK(var_1C != 0);
        SCRIPT_CHECK(var_1C->vf_008() == 0x2E);
        local_20 = (type_3DFEEC *)var_1C;
        SCRIPT_CHECK((local_20->unk_10 & 2) != 0);
        var18 = ((type_D48D0 *)&local_20->unk_24_id)->sub_D4910();
        // The image reserves slots for three checks' locals here, not four:
        // the last calls the hook directly (as in "AttachProp").
        sub_44220(var18 != 0);
        lv_8->vf_1FC(var18, 0);
        lv_8->set_unk_36C(0, local_C);
    }
    sub_44350(arg_4, 0);
}

// match: sub_47930 @ 0x00047930
// sp-match: sub_47930 @ 0x00036330
// "WillTransitionPlay": whether a set exists for the entity's weapon class,
// its hit-death byte (vf_0AC) and arg 1 (sub_6D0A0); 0 without a performance
// player.
void sub_47930(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    v8 = sub_45170(arg_0);
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_4 = 0;
    SCRIPT_CHECK2(v8 != 0);
    if (v8 != 0 && v8->vf_090() != 0) {
        var_10 = -1;
        if (v8->vf_008() != 0)
            var_10 = v8->vf_008()->unk_3E0.sub_15F0A0();
        // The image calls vf_090 again here and drops the result.
        v8->vf_090();
        var_4 = sub_6D0A0(var_10, v8->vf_0AC(), ebp_C, 0);
    }
    sub_44350(arg_4, &var_4);
}

// sub_47A20 ("PlayPickUpMMGPerformance") and sub_47C20
// ("PlayAlarmCrankPerformance") stay binary (docs/units.md).

// match: sub_47A20 @ 0x00047A20
// sp-match: sub_47A20 @ 0x000568B0
// "PlayPickUpMMGPerformance": makes the mounted weapon at its AI object's
// path node (sub_16A380), else the one on the vehicle it rides (unk_624), its
// soldier's weapon (sub_13F4D0) and plays the current performance at the
// weapon's tag matrix (sub_16A3B0).
void sub_47A20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D3548 *var_8;
    type_3DC9B0 *var_C;
    type_3DAFC8 *var_10;
    AIData *var_14;
    type_F8350 *var_18;
    RwMatrix var_70;

    var_4 = sub_67620(arg_0);
    var_8 = sub_45170(arg_0);
    SCRIPT_CHECK(var_8->vf_008() != 0);
    var_C = 0;
    var_10 = var_8->vf_008();
    var_14 = var_10->vf_120();
    var_18 = var_14->unk_F60;
    if (var_18)
    {
        var_C = (type_3DC9B0 *)sub_16A380(var_18);
    }
    else if (var_8->vf_008()->unk_624.sub_D4910()
             && var_8->vf_008()->unk_624.sub_D4910()->vf_010()
             && var_8->vf_008()->unk_624.sub_D4910()->vf_010()->vf_2C4())
    {
        var_C = var_8->vf_008()->unk_624.sub_D4910()->vf_010()->vf_2C4()->vf_028();
    }
    else
    {
        SCRIPT_CHECK(var_18 != 0);
    }
    SCRIPT_CHECK(var_C != 0);
    if (var_C)
    {
        var_8->vf_008()->sub_13F4D0(var_C);
        var_C->sub_16A3B0(&var_70, 1, 0);
        var_8->vf_088(0);
        sub_47F90(var_4, var_8, &var_70.pos, &var_70.at, 1, 0, 1);
    }
    sub_44350(arg_4, 0);
}

// match: sub_47C20 @ 0x00047C20
// sp-match: sub_47C20 @ 0x00056AE0
// "PlayAlarmCrankPerformance": plays the current performance at the nearest
// kind-15 path node (sub_F7E80) within 2000 units, facing the node's
// orientation.
void sub_47C20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D3548 *var_8;
    type_F8350 *var_6C;
#ifndef CODFH_SP
    RwMatrix var_E0;
#endif

    var_4 = sub_67620(arg_0);
    var_8 = sub_45170(arg_0);
    SCRIPT_CHECK(var_8->vf_008() != 0);
    type_154C0_1048 var_68;
    var_68.unk_04 = *var_8->sub_CD550();
    var_68.unk_10 = 2000.0f;
    var_68.unk_00 = 0;
    var_68.unk_18 = sub_F7E80(15);
    var_68.unk_1C = 0;
    sub_F8970(&var_68, 1, 0);
    if (var_68.unk_34)
    {
        var_6C = var_68.unk_34;
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules the matrix stores as SP 0x56AE0 does
        RwMatrix var_E0;
#endif
        RtQuatConvertToMatrix(&var_6C->unk_1C, &var_E0);
        var_8->vf_088(0);
        sub_47F90(var_4, var_8, &var_6C->unk_10, &var_E0.at, 1, 0, 0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_47F00 @ 0x00047F00
// sp-match: sub_47F00 @ 0x00036440
// "ResetNPCMountedWeaponAimMatrix": of the soldier's mounted weapon, while
// it uses one.
void sub_47F00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC9B0 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4->vf_008() != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    if (var_4->vf_008()->get_unk_61C() != 0) {
        local_8 = var_4->vf_008()->get_unk_618();
        if (local_8 != 0)
            local_8->sub_168F40();
    }
    sub_44350(arg_4, 0);
}

// match: sub_47F90 @ 0x00047F90
// sp-match: sub_47F90 @ 0x000364E0
// Plays the object arg_0's entity arg_4's current performance (at the point
// *arg_8 facing *arg_C when given; "PlayCurrentPerformance" and the like),
// unless vf_0A8 holds it: the one dword_4B92FC finds for its performance
// values and a selector, unk_358, else unk_354, else built from a soldier's
// or type_3DDB98's flags and its unk_3E0's sub_15EE90. Reports and stops
// when none matches.
void sub_47F90(type_67620 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwV3d *arg_C,
               RwInt32 arg_10, RwInt32 arg_14, RwInt32 arg_18)
{
    RwUInt8 *var_1C;
    type_6D380 *var18;
    type_ED340 *stk_14;
    RwInt16 l10;
    type_3DAFC8 *local_C;
    type_3DDB98 *lv_8;
    RwInt32 var_4;

    var_4 = 0;
    local_C = 0;
    lv_8 = 0;
    if (arg_4->vf_0A8() == 0) {
        var18 = arg_4->vf_090();
        var_1C = arg_4->vf_08C(1, 0);
        SCRIPT_CHECK(var18 != 0);
        SCRIPT_CHECK(var_1C != 0);
        stk_14 = dword_4B92FC;
        SCRIPT_CHECK(stk_14 != 0);
        if (arg_4->get_unk_358() != 0) {
            var_4 = arg_4->unk_358;
        } else if (arg_4->get_unk_354() != 0) {
            var_4 = arg_4->unk_354;
        } else {
            local_C = arg_4->vf_008();
            if (local_C != 0) {
                var_4 = ((local_C->unk_2C >> 3) & 1) * 8 + (local_C->unk_2C & 1) * 4
                    + local_C->unk_3E0.sub_15EE90();
            } else {
                lv_8 = arg_4->vf_024();
                if (lv_8 != 0)
                    var_4 = ((lv_8->unk_2C >> 3) & 1) * 8 + (lv_8->unk_2C & 1) * 4
                        + lv_8->unk_3E0.sub_15EE90();
            }
        }
        l10 = stk_14->sub_ED340(arg_4, var_1C, var_4, 0);
        if (l10 != -1) {
            ((type_3D2CD0 *)var18)->sub_6D380(l10, arg_8, arg_C, arg_10, 0, 0, arg_14, arg_18);
            var18->unk_144 = 1;
        } else {
            sub_6B060(arg_0, "No matching performance found!", 0);
            ((type_3D2CD0 *)var18)->sub_6DDF0(0, 0);
        }
    }
}

// match: sub_48170 @ 0x00048170
// sp-match: sub_48170 @ 0x000366A0
// "StopCurrentPerformance".
void sub_48170(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_6D380 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        local_8 = var_4->vf_090();
        if (local_8 != 0)
            local_8->unk_128 = 1;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_481C0 @ 0x000481C0
// sp-match: sub_481C0 @ 0x000366E0
// "DisablePerformances".
void sub_481C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    var_4->vf_0A4(local_8);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48230 @ 0x00048230
// sp-match: sub_48230 @ 0x00036730
// "SetStarStatus": the entity's first performance selector (sub_47F90).
void sub_48230(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    var_4->unk_358 = local_8;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48290 @ 0x00048290
// sp-match: sub_48290 @ 0x00036780
// "SetFiveWayBlend": turns blend arg 2 (0 and 1 a soldier's, 2 the
// entity's type_3DA6C0's) on or off (arg 1); turning it on also sets the
// object's unk_129 when its kind (vf_014) is 1, with unk_124 for blends 0
// and 1.
void sub_48290(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_20;
    type_67620 *var_1C;
    type_67620 *var18;
    type_3DA6C0 *stk_14;
    RwInt32 l10;
    type_3D3548 *local_C;
    RwInt32 lv_8;
    type_3DAFC8 *var_4;

    lv_8 = SCRIPT_ARG(arg_4, 1);
    l10 = SCRIPT_ARG(arg_4, 2);
    local_C = sub_45170(arg_0);
    SCRIPT_CHECK(local_C != 0);
    var_4 = local_C->vf_008();
#ifdef CODFH_SP // single player has only the soldier's two blends, and checks the soldier (SP 0x36780)
    SCRIPT_CHECK(var_4 != 0);
    switch (l10) {
    case 0:
        if (var_4 != 0) {
            var_4->sub_139550(lv_8 != 0);
            if (lv_8 != 0) {
                var18 = sub_67620(arg_0);
                SCRIPT_CHECK(var18 != 0);
                if (var18 != 0 && var18->vf_014() == 1) {
                    var18->set_unk_129(1);
                    var18->unk_124 = 0.13333334f;
                }
            }
        }
        break;
    case 1:
        if (var_4 != 0) {
            var_4->sub_13A340(lv_8 != 0);
            if (lv_8 != 0) {
                var_1C = sub_67620(arg_0);
                SCRIPT_CHECK(var_1C != 0);
                if (var_1C != 0 && var_1C->vf_014() == 1) {
                    var_1C->set_unk_129(1);
                    var_1C->unk_124 = 0.13333334f;
                }
            }
        }
        break;
    }
#else
    stk_14 = local_C->vf_01C();
    switch (l10) {
    case 0:
        if (var_4 != 0) {
            var_4->sub_139550(lv_8 != 0);
            if (lv_8 != 0) {
                var18 = sub_67620(arg_0);
                SCRIPT_CHECK(var18 != 0);
                if (var18 != 0 && var18->vf_014() == 1) {
                    var18->set_unk_129(1);
                    var18->unk_124 = 0.13333334f;
                }
            }
        }
        break;
    case 1:
        if (var_4 != 0) {
            var_4->sub_13A340(lv_8 != 0);
            if (lv_8 != 0) {
                var_1C = sub_67620(arg_0);
                SCRIPT_CHECK(var_1C != 0);
                if (var_1C != 0 && var_1C->vf_014() == 1) {
                    var_1C->set_unk_129(1);
                    var_1C->unk_124 = 0.13333334f;
                }
            }
        }
        break;
    case 2:
        if (stk_14 != 0) {
            ((type_3D32F8 *)stk_14)->sub_76860(lv_8 != 0);
            if (lv_8 != 0) {
                local_20 = sub_67620(arg_0);
                SCRIPT_CHECK(local_20 != 0);
                if (local_20 != 0 && local_20->vf_014() == 1)
                    local_20->set_unk_129(1);
            }
        }
    }
#endif
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_484B0 @ 0x000484B0
// sp-match: sub_484B0 @ 0x000368C0
// "SetHeadTrack": turns a soldier's head tracking on or off (arg 1) at the
// rate arg 2.
void sub_484B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    RwReal ebp_C;
    RwInt32 v8;
    type_3DAFC8 *var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10 = sub_45170(arg_0);
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->vf_008();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_1340D0(v8 != 0, 1, ebp_C);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48570 @ 0x00048570
// sp-match: sub_48570 @ 0x000369B0
// "SetTurnMode": turns the entity's animation level towards its AI object's
// point unk_500 when flag 30 of unk_49C is set, else towards its target
// point unk_4F0, led along unk_50C by up to flt_428A08 units (flt_428A0C
// of that per unit of distance).
void sub_48570(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwV3d local_58;
    RwV3d stk_4C;
    RwV3d lv_40;
    RwReal v34;
    RwV3d v30;
#endif
    RwV3d *slot_24;
#ifndef CODFH_SP
    RwV3d v20;
#endif
    RwV3d *stk_14;
    RwV3d *l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    type_7C8D0 *var_4;

    lv_8 = sub_45170(arg_0);
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = lv_8->unk_284;
    if (var_4 != 0) {
        local_C = lv_8->vf_120();
        SCRIPT_CHECK(local_C != 0);
        if (local_C != 0) {
            if ((local_C->unk_49C >> 30) & 1) {
                stk_14 = &RwFrameGetLTM(lv_8->get_unk_340())->pos;
                l10 = &local_C->unk_500;
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares the branches' slots (SP 0x369B0 frame 0x30)
                RwV3d v20;

#endif
                RwV3dSub(&v20, l10, stk_14);
                v20.y = 0.0f;
                RwV3dNormalize(&v20, &v20);
                var_4->sub_7A0A0(&v20);
            } else {
                slot_24 = local_C->unk_4F0;
                if (slot_24 != 0) {
#ifdef CODFH_SP // shape: block-scoped (SP 0x369B0 frame 0x30)
                    RwV3d local_58;
                    RwV3d stk_4C;
                    RwV3d lv_40;
                    RwReal v34;
                    RwV3d v30;

#endif
                    local_58 = RwFrameGetLTM(lv_8->get_unk_340())->pos;
                    RwV3dSub(&stk_4C, slot_24, &local_58);
                    v34 = 0.0f;
                    stk_4C.y = 0.0f;
                    if (RwV3dDotProduct(&stk_4C, &stk_4C) > 0.0001f)
                        v34 = RwV3dLength(&stk_4C);
                    v34 = v34 * flt_428A0C;
                    if (v34 > 1.0f)
                        v34 = 1.0f;
                    lv_40 = local_C->unk_50C;
                    lv_40.y = 0.0f;
                    RwV3dScale(&v30, &lv_40, flt_428A08 * v34);
                    RwV3dAdd(&v30, &v30, slot_24);
                    RwV3dSub(&v30, &v30, &local_58);
                    var_4->sub_7A0A0(&v30);
                }
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48800 @ 0x00048800
// sp-match: sub_48800 @ 0x00036C20
// "GetTurnAmount": the angle of the entity's animation's turn, in whole
// degrees from 0 to 360 (0 without an animation).
void sub_48800(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwReal v8;
    type_7C8D0 *var_4;

    v8 = 0.0f;
    var_10 = 0;
    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->unk_284;
    if (var_4 != 0) {
        v8 = atan2(var_4->unk_1A0, var_4->unk_1A8) * 2.0f;
        v8 = v8 * 360.0f / 6.2831855f;
        if (v8 < 0.0f)
            v8 = v8 + 360.0f;
    }
    var_10 = (RwInt32)v8;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_488D0 @ 0x000488D0
// sp-match: sub_488D0 @ 0x00036D00
// "GetTerrainAngle": the slope of the ground under the entity along its
// facing, in whole degrees from 0 to 359 (from the normal of the triangle
// found 50 above its position, crossed with its right vector); 0 over no
// ground.
void sub_488D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d local_58;
    RwV3d stk_4C;
    type_92430 lv_40;
    RwV3d l14;
    RwInt32 v8;
    type_3D3548 *var_4;

    v8 = 0;
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    stk_4C = *var_4->sub_CD550();
    stk_4C.y = stk_4C.y + 50.0f;
    l14 = *var_4->sub_CDBE0();
    sub_92430(&stk_4C, &lv_40, 30.0f);
    if (lv_40.unk_00 != 0) {
        sub_16E740(lv_40.unk_00, lv_40.unk_20, &lv_40.unk_14);
        RwV3dCrossProduct(&local_58, &l14, &lv_40.unk_14);
        RwV3dNormalize(&local_58, &local_58);
        v8 = ((RwInt32)(asin(local_58.y) * 57.295776f) + 360) % 360;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_48A10 @ 0x00048A10
// sp-match: sub_48A10 @ 0x00036E90
// "SetSceneMap": plays the scene performance dword_4B9300 finds for the map
// with the id arg 1.
void sub_48A10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt8 *var_1C;
    type_4CFE30 *var18;
    type_6D380 *stk_14;
    type_ED850 *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt16 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    if (local_C >= 0 && local_C < 2000)
        var18 = dword_4CFE30[local_C];
    else
        var18 = 0;
    SCRIPT_CHECK((var_1C = var18->unk_1A0) != 0);
    lv_8 = sub_45170(arg_0);
    stk_14 = lv_8->vf_090();
    SCRIPT_CHECK(stk_14 != 0);
    l10 = dword_4B9300;
    SCRIPT_CHECK(l10 != 0);
    var_4 = l10->sub_ED850(var_1C, 0);
    if (var_4 != -1)
        ((type_3D2CD0 *)stk_14)->sub_6D380(var_4, 0, 0, 0, 0, 0, 0, 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48B10 @ 0x00048B10
// sp-match: sub_48B10 @ 0x00036FE0
// "GetSceneActionMsg": the message of the scene action arg 1.
void sub_48B10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    varC = var_4->vf_0E4(local_8);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &varC);
}

// match: sub_48B80 @ 0x00048B80
// sp-match: sub_48B80 @ 0x00037060
// "SetSceneValue": value arg 2 at index arg 1.
void sub_48B80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    varC = sub_45170(arg_0);
    varC->vf_0EC(local_8, var_4);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48C10 @ 0x00048C10
// sp-match: sub_48C10 @ 0x00056D40
// "PlayCurrentScene".
void sub_48C10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    sub_48EE0(local_8, var_4, 0, 0, 0);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_48C70 @ 0x00048C70
// sp-match: sub_48C70 @ 0x00056DC0
// "PlayCurrentSceneAtNamedPoint": at the point (vf_00C) of the object under
// the key arg 1 (two slots; of kind 0x2C to 0x2E), facing its direction
// (vf_010, else the entity's own facing).
void sub_48C70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8 *local_24;
    RwV3d *local_20;
    type_3DF8D8_04 *var_1C;
    type_67620 *var18;
    RwV3d *stk_14;
    type_3D3548 *l10;
    type_3DF8D8 *local_C;
    RwBool lv_8;
    RwInt32 var_4;

    local_20 = 0;
    stk_14 = 0;
    var18 = sub_67620(arg_0);
    l10 = sub_45170(arg_0);
    SCRIPT_CHECK(l10 != 0);
    var_1C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_C = sub_198800(var_1C);
    var_4 = local_C->vf_008();
    lv_8 = local_C != 0 && (var_4 == 0x2E || var_4 == 0x2D || var_4 == 0x2C);
    if (lv_8 != 0) {
        local_24 = local_C;
        local_20 = local_24->vf_00C();
        if (local_20 != 0) {
            stk_14 = local_24->vf_010();
            if (stk_14 == 0)
                stk_14 = l10->sub_CD5A0();
        }
    } else {
        // This check reserves no slots.
        sub_44220(0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_48EE0(var18, l10, local_20, stk_14, 1);
    sub_44350(arg_4, 0);
}

// match: sub_48DA0 @ 0x00048DA0
// sp-match: sub_48DA0 @ 0x000370C0
// "GotoPointUsingRegistration": plays the current performance at the AI
// object's point unk_5B0, set to (arg 1, arg 2, arg 3), facing the entity's
// own facing.
void sub_48DA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *var_1C;
    type_67620 *local_18;
    RwV3d *local_14;
    type_3D3548 *local_10;
    RwV3d var_C;

    var_1C = 0;
    local_14 = 0;
    local_10 = sub_45170(arg_0);
    local_18 = sub_67620(arg_0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    *local_10->vf_120()->get_unk_5B0() = var_C;
    if ((var_1C = local_10->vf_120()->get_unk_5B0()) != 0)
        local_14 = local_10->sub_CD5A0();
    else
        SCRIPT_CHECK(0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_47F90(local_18, local_10, var_1C, local_14, 1, 0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_48EE0 @ 0x00048EE0
// sp-match: sub_48EE0 @ 0x000371D0
// Plays the object arg_0's entity arg_4's current scene performance, the one
// dword_4B9300 finds for its scene's map entry (vf_0E0), which may also give
// its performance values' byte 2; bit 0 of its unk_280 object's flags is set
// unless both a point and a direction are given. Reports when none matches.
void sub_48EE0(type_67620 *arg_0, type_3D3548 *arg_4, RwV3d *arg_8, RwV3d *arg_C,
               RwInt32 arg_10)
{
    RwInt32 var_1C;
    RwUInt8 *var18;
    RwUInt8 *stk_14;
    RwInt16 l10;
    type_6D380 *local_C;
    type_ED850 *lv_8;
    RwInt16 var_4;

    SCRIPT_CHECK(arg_4 != 0);
    stk_14 = arg_4->vf_0E0();
    SCRIPT_CHECK(stk_14 != 0);
    local_C = arg_4->vf_090();
    SCRIPT_CHECK(local_C != 0);
    lv_8 = dword_4B9300;
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = lv_8->sub_ED850(stk_14, &l10);
    if (var_4 != -1) {
        var18 = arg_4->vf_08C(1, 0);
        if (var18 != 0 && l10 >= 0)
            var18[2] = (RwUInt8)l10;
        var_1C = 1;
        if (arg_8 != 0 && arg_C != 0)
            var_1C = 0;
        arg_4->set_unk_280_bit0(var_1C != 0);
        ((type_3D2CD0 *)local_C)->sub_6D380(var_4, arg_8, arg_C, arg_10, 0, 0, 0, 0);
        local_C->unk_144 = 3;
    } else {
        sub_6B060(arg_0, "No matching performance found!", 0);
    }
}

// match: sub_49040 @ 0x00049040
// sp-match: sub_49040 @ 0x000373C0
// "GetSceneActionCount".
void sub_49040(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_0E8();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_49080 @ 0x00049080
// sp-match: sub_49080 @ 0x00037420
// "GetVisionRange": the view range, 0 without an entity.
void sub_49080(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    type_3D3548 *var_4;

    local_8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        local_8 = var_4->vf_10C();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_490D0 @ 0x000490D0
// sp-match: sub_490D0 @ 0x00037490
// "GetWeaponsMinMediumRange".
void sub_490D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    type_3D3548 *var_4;

    local_8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        local_8 = var_4->vf_144();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_49120 @ 0x00049120
// sp-match: sub_49120 @ 0x00037500
// "GetWeaponsMinLongRange".
void sub_49120(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    type_3D3548 *var_4;

    local_8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        local_8 = var_4->vf_148();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_49170 @ 0x00049170
// sp-match: sub_49170 @ 0x00037570
// "GetWeaponsTooCloseForComfortRange".
void sub_49170(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    type_3D3548 *var_4;

    local_8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        local_8 = var_4->vf_14C();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_491C0 @ 0x000491C0
// sp-match: sub_491C0 @ 0x000375E0
// "GetWeaponsStandMeleeRange": the weapon's (vf_150) plus flt_428A10 against
// a target with flag 4 of its unk_2C, flt_428A14 against another target, the
// weapon's own without an AI object.
void sub_491C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    AIData *ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    v8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        ebp_C = var_4->vf_120();
        if (ebp_C != 0) {
            var_10 = ebp_C->get_unk_1374();
            if (var_10 != 0) {
                if ((var_10->unk_2C >> 4) & 1)
                    v8 = var_4->vf_150() + flt_428A10;
                else
                    v8 = flt_428A14;
            }
        } else {
            v8 = var_4->vf_150();
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_49270 @ 0x00049270
// sp-match: sub_49270 @ 0x00037690
// "GetWeaponsLungeMeleeRange": as "GetWeaponsStandMeleeRange", with vf_154, flt_428A18 and flt_428A1C.
void sub_49270(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    AIData *ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    v8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        ebp_C = var_4->vf_120();
        if (ebp_C != 0) {
            var_10 = ebp_C->get_unk_1374();
            if (var_10 != 0) {
                if ((var_10->unk_2C >> 4) & 1)
                    v8 = var_4->vf_154() + flt_428A18;
                else
                    v8 = flt_428A1C;
            }
        } else {
            v8 = var_4->vf_154();
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_49320 @ 0x00049320
// sp-match: sub_49320 @ 0x00037740
// "GetWeaponsRunMeleeRange": as "GetWeaponsStandMeleeRange", with vf_158, flt_428A20 and flt_428A24.
void sub_49320(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    AIData *ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    v8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        ebp_C = var_4->vf_120();
        if (ebp_C != 0) {
            var_10 = ebp_C->get_unk_1374();
            if (var_10 != 0) {
                if ((var_10->unk_2C >> 4) & 1)
                    v8 = var_4->vf_158() + flt_428A20;
                else
                    v8 = flt_428A24;
            }
        } else {
            v8 = var_4->vf_158();
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_493D0 @ 0x000493D0
// sp-match: sub_493D0 @ 0x000377F0
// "GetWeaponIsBoltActionRifle".
void sub_493D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = sub_45170(arg_0);
    if (local_8 != 0)
        var_4 = local_8->vf_15C();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_49420 @ 0x00049420
// sp-match: sub_49420 @ 0x00037860
// "GetMyWeaponGroupType": -1 without an entity.
void sub_49420(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = -1;
    local_8 = sub_45170(arg_0);
    if (local_8 != 0)
        var_4 = local_8->vf_160();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_49470 @ 0x00049470
// sp-match: sub_49470 @ 0x000378D0
// "IsMyWeaponOutOfAmmo".
void sub_49470(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = sub_45170(arg_0);
    if (local_8 != 0)
        var_4 = local_8->vf_13C();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_494C0 @ 0x000494C0
// sp-match: sub_494C0 @ 0x00037940
// "ForceMyWeaponToReload".
void sub_494C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0)
        var_4->vf_140();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_49500 @ 0x00049500
// sp-match: sub_49500 @ 0x00037980
// "SetAdvancedShotLocation": a soldier's, with its result (0 for others).
void sub_49500(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = 0;
    varC = sub_45170(arg_0);
    if (varC != 0 && varC->vf_008() != 0)
        local_8 = varC->vf_008()->sub_138D00(var_4);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_49590 @ 0x00049590
// sp-match: sub_49590 @ 0x00037A10
// "DoIHaveGrenades": a soldier's unk_5E0 (0 for other entities).
void sub_49590(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = sub_45170(arg_0);
    if (local_8->vf_008() != 0)
        var_4 = local_8->vf_008()->get_unk_5E0();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_495F0 @ 0x000495F0
// sp-match: sub_495F0 @ 0x00037A90
// "DropGrenadeAtLocationXYZ": drops a grenade (a Stielhandgranate for arg 1
// of 2, else a Mark 2) at (arg 2, arg 3, arg 4), at rest, upright, with the
// fuse arg 5 and arg 6 (per second) from the next of the eight settings in
// dword_439A48.
void sub_495F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_495F0 *var_4;
    RwInt32 var_8;
    RwInt32 var_C;
    RwMatrix var_50;
    RwV3d var_5C;
    type_439A48 *var_60;

    var_4 = 0;
    var_8 = SCRIPT_ARG(arg_4, 1);
    if (var_8 == 2) {
        var_C = 0x402;
        var_4 = (type_495F0 *)sub_198880("GameWeapons+Weapons+Stielhandgrenate");
    } else {
        var_C = 0x401;
        var_4 = (type_495F0 *)sub_198880("GameWeapons+Weapons+Mark2Frag");
    }
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->vf_008() == 5);
    SCRIPT_CHECK(var_4->sub_18F800(&var_4->unk_38) != 0);
    RwMatrixSetIdentityMacro(&var_50);
    var_50.pos.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_50.pos.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_50.pos.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_5C.x = 0.0f;
    var_5C.y = 0.0f;
    var_5C.z = 0.0f;
    dword_439940++;
    dword_439940 &= 7;
    var_60 = &dword_439A48[dword_439940];
    memset(var_60, 0, sizeof(type_439A48));
    var_60->unk_00 = 2;
    var_60->unk_04 = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_60->unk_38 = var_4->sub_18F800(&var_4->unk_38);
    var_60->unk_3C = 1;
    var_60->unk_40 = -1.0f;
    var_60->unk_44 = 0.15f;
    var_60->unk_48 = 0.5f;
    var_60->unk_4C = 200.0f;
    var_60->unk_50 = SCRIPT_ARGT<RwReal>(arg_4, 6) * 60.0f;
    var_60->unk_54 = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_60->unk_58 = var_60->unk_4C;
    var_60->unk_60 = var_60->unk_04;
    var_60->unk_5C = var_60->unk_4C;
    var_60->unk_64 = var_60->unk_04;
    var_60->unk_68 = 50.0f;
    var_60->unk_70 = 3.0f;
    var_60->unk_6C = 10.0f;
    var_60->unk_78 = 1.0f;
    var_60->unk_74 = 10.0f;
    var_60->unk_7C = 2.0f;
    var_60->unk_80 = 10.0f;
    sub_15F2C0(var_C, 0, &var_50, &var_5C, 0, var_60, 0);
    sub_44350(arg_4, 0);
}

// match: sub_49970 @ 0x00049970
// sp-match: sub_49970 @ 0x00037D80
// "DoIHaveAGrenadeInHand": a soldier's; 0 for other entities.
void sub_49970(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = 0;
    local_8 = sub_45170(arg_0);
    if (local_8->vf_008() != 0)
        var_4 = local_8->vf_008()->has_grenade_in_hand();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_49A00 @ 0x00049A00
// sp-match: sub_49A00 @ 0x00037E10
// "DropGrenade": a soldier's.
void sub_49A00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4->vf_008() != 0)
        var_4->vf_008()->sub_136E00();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_49A50 @ 0x00049A50
// sp-match: sub_49A50 @ 0x00037E60
// "ShouldIThrowAGrenade": a soldier's answer for arg 1, unless flag 15 of
// its AI object's unk_49C is set; 0 otherwise.
void sub_49A50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = 0;
    varC = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    if (varC->vf_008() != 0 && ((varC->vf_120()->unk_49C >> 15) & 1) == 0)
        var_4 = varC->vf_008()->sub_136EC0(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_49AF0 @ 0x00049AF0
// sp-match: sub_49AF0 @ 0x00037F00
// "ShouldIDoTheAssaultWalk": 1 for a soldier in a group of context 0 whose
// target is within 1000 of its record distance and not merely possible
// (bit 1 of its record's flags), with flag 1 of its unk_2C, while the
// player's AI object's unk_1394 is past 300, and the target's own record of
// the player is further and not merely possible.
void sub_49AF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_154C0_80 *local_28;
    type_3D410 *local_24;
    type_3DF30 *local_20;
    type_154C0_80 *var_1C;
    AIData *var18;
    type_3D3548 *stk_14;
    type_3D3548 *l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    var_4 = 0;
    lv_8 = sub_45170(arg_0);
    if (lv_8->vf_008() != 0) {
        local_C = lv_8->vf_120();
        l10 = local_C->get_unk_1374();
        if (l10 != 0) {
            stk_14 = sub_1745A0(0);
            var18 = stk_14->vf_120();
            if (local_C->sub_17100() < 1000.0) {
                var_1C = local_C->sub_16ED0(l10, 0);
                if (var_1C != 0 && var18 != 0 && var18->get_unk_1394() > 300.0f) {
                    local_20 = local_C->get_unk_56C();
                    if (local_20 != 0 && (local_24 = &local_20->unk_04) != 0 && local_24->unk_04 == 0
                        && ((var_1C->unk_04 >> 1) & 1) == 0 && (lv_8->unk_2C & 1) != 0
                        && l10->vf_120() != 0) {
                        local_28 = l10->vf_120()->sub_16ED0(sub_1745A0(0), 0);
                        if (local_28 != 0 && local_28->unk_0C > var_1C->unk_0C
                            && ((local_28->unk_04 >> 1) & 1) == 0)
                            var_4 = 1;
                    }
                }
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_49C90 @ 0x00049C90
// sp-match: sub_49C90 @ 0x00038070
// "OverrideNPCGrenadeTimer": a soldier's, arg 1 in seconds.
void sub_49C90(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    if (local_8->vf_008() != 0)
        local_8->vf_008()->set_unk_5FC(var_4 * 60.0f);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_49D10 @ 0x00049D10
// sp-match: sub_49D10 @ 0x000380E0
// "CancelGrenadeThrowPoint": a soldier's.
void sub_49D10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4->vf_008() != 0)
        var_4->vf_008()->set_unk_5F8(0);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// sub_49D70 ("SetGrenadeThrowPoint") stays binary (docs/units.md).

// match: sub_49D70 @ 0x00049D70
// sp-match: sub_49D70 @ 0x00038130
// "SetGrenadeThrowPoint": the point (arg 1, arg 2, arg 3) becomes its
// soldier's grenade throw point (unk_5EC): as given for mode 0 (arg 4), in the
// entity's frame for mode 1, else in its AI object's path node's.
void sub_49D70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    RwReal var_8;
    RwReal var_C;
    RwReal var_10;
    RwInt32 var_14;
    RwV3d var_20;
    RwFrame *var_28;
    RwMatrix *var_2C;
    AIData *var_30;
    type_F8350 *var_34;
#ifndef CODFH_SP
    RwMatrix var_B0;
#endif

    var_4 = sub_45170(arg_0);
    var_8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_14 = SCRIPT_ARG(arg_4, 4);
    if (var_4->vf_008())
    {
        var_20.x = var_8;
        var_20.y = var_C;
        var_20.z = var_10;
        if (var_14 == 0)
        {
        }
        else if (var_14 == 1)
        {
            var_28 = var_4->get_unk_340();
            if (var_28)
            {
                var_2C = RwFrameGetLTM(var_28);
                if (var_2C)
                {
                    sub_1414C0(&var_20, &var_20, var_2C);
                }
            }
        }
        else
        {
            var_30 = var_4->vf_120();
            var_34 = var_30->unk_F60;
            if (var_34)
            {
#ifdef CODFH_SP // shape: block-scoped, so /O2 lays out the frame as SP 0x38130 does
                RwMatrix var_B0;
#endif
                RtQuatConvertToMatrix(&var_34->unk_1C, &var_B0);
                var_B0.pos = var_34->unk_10;
                sub_1414C0(&var_20, &var_20, &var_B0);
            }
        }
        var_4->vf_008()->set_unk_5EC(&var_20);
    }
    sub_44350(arg_4, 0);
}

// match: sub_4A0F0 @ 0x0004A0F0
// sp-match: sub_4A0F0 @ 0x00038390
// "ShouldIMeleeAttack": a soldier's answer for arg 1; 0 for other entities.
void sub_4A0F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = 0;
    varC = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    if (varC->vf_008() != 0)
        var_4 = varC->vf_008()->sub_137200(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4A180 @ 0x0004A180
// sp-match: sub_4A180 @ 0x00038420
// "TurnPlayerWeaponOnorOff".
void sub_4A180(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_10F710 *var_4;

    varC = SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0)
        var_4->sub_10E750(varC, local_8);
    sub_44350(arg_4, 0);
}

// match: sub_4A210 @ 0x0004A210
// sp-match: sub_4A210 @ 0x00038480
// "TurnCrosshairOnorOff".
void sub_4A210(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0)
        var_4->sub_10E880(local_8);
    sub_44350(arg_4, 0);
}

// match: sub_4A270 @ 0x0004A270
// sp-match: sub_4A270 @ 0x000384D0
// "IsPlayerWeaponStreamed": 0 without a player.
void sub_4A270(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = (type_10F710 *)sub_1745A0(0);
    var_4 = 0;
    if (varC != 0)
        var_4 = varC->sub_10E8C0(local_8);
    sub_44350(arg_4, &var_4);
}

// match: sub_4A2E0 @ 0x0004A2E0
// sp-match: sub_4A2E0 @ 0x00038550
// "RequestToStreamPlayerWeapon".
void sub_4A2E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = (type_10F710 *)sub_1745A0(0);
    if (local_8 != 0) {
        local_8->sub_10DA70(var_4);
        local_8->unk_2138 = 0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4A350 @ 0x0004A350
// sp-match: sub_4A350 @ 0x000385B0
// "RemovePlayerWeapon".
void sub_4A350(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    type_10F710 *v8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    ebp_C = SCRIPT_ARG(arg_4, 3);
    v8 = (type_10F710 *)sub_1745A0(0);
    if (v8 != 0) {
        v8->sub_10E9D0(var_4, var_10, ebp_C);
        v8->unk_2138 = 1;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4A420 @ 0x0004A420
// sp-match: sub_4A420 @ 0x00038630
// "GivePlayerInventoryItem": adds arg 2 of the item arg 1 to the player's
// inventory, as the inventory kind its switch gives, and selects it.
void sub_4A420(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    type_10F710 *v8;
    RwInt32 var_4;

    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    v8 = (type_10F710 *)sub_1745A0(0);
    if (v8 != 0) {
        var_10 = -1;
        switch (ebp_C) {
        case 31:
            var_10 = 5;
            break;
        case 33:
            var_10 = 7;
            break;
        case 21:
            var_10 = 2;
            break;
        case 20:
            var_10 = 8;
            break;
        case 22:
            var_10 = 9;
            break;
        case 19:
            var_10 = 10;
            break;
        case 34:
            var_10 = 11;
            break;
        case 38:
            var_10 = 12;
        }
        if (var_10 != -1) {
            v8->unk_21B4.sub_116080(var_10, var_4);
            v8->unk_21B4.sub_115980(var_10);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_4A580 @ 0x0004A580
// sp-match: sub_4A580 @ 0x00038720
// "RegisterDistanceCheck": registers the object for the test arg 1 between
// the distances arg 2 and arg 3 against the target with the handle arg 6;
// the registration's handle.
void sub_4A580(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 local_28;
    type_3D2E7C *local_24;
    RwUInt32 local_20;
    type_67620 *var_1C;
    RwReal var18;
    RwInt32 stk_14;
    RwReal l10;
    alfasched_entry *local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    var_1C = sub_67620(arg_0);
    lv_8 = SCRIPT_ARG(arg_4, 1);
    l10 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var18 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_4 = SCRIPT_ARG(arg_4, 4);
    stk_14 = SCRIPT_ARG(arg_4, 5);
    local_28 = SCRIPT_ARG(arg_4, 6);
    local_24 = (type_3D2E7C *)sub_67620(local_28);
    local_C = (alfasched_entry *)sub_35200(var_1C, l10, var18, lv_8, var_4, stk_14, local_24,
                                         -1, -1);
    local_20 = local_C->unk_00;
    sub_44350(arg_4, &local_20);
}

// match: sub_4A6F0 @ 0x0004A6F0
// sp-match: sub_4A6F0 @ 0x000387F0
// "RegisterDistanceCheckMsg": "RegisterDistanceCheck" with its messages
// (args 2 and 3) and the rest shifted by two.
void sub_4A6F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_30;
    type_3D2E7C *bp_2C;
    RwInt32 local_28;
    RwUInt32 local_24;
    type_67620 *local_20;
    RwReal var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    RwReal l10;
    alfasched_entry *local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    local_20 = sub_67620(arg_0);
    lv_8 = SCRIPT_ARG(arg_4, 1);
    local_28 = SCRIPT_ARG(arg_4, 2);
    var18 = SCRIPT_ARG(arg_4, 3);
    l10 = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_1C = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_4 = SCRIPT_ARG(arg_4, 6);
    stk_14 = SCRIPT_ARG(arg_4, 7);
    var_30 = SCRIPT_ARG(arg_4, 8);
    bp_2C = (type_3D2E7C *)sub_67620(var_30);
    local_C = (alfasched_entry *)sub_35200(local_20, l10, var_1C, lv_8, var_4, stk_14, bp_2C,
                                         local_28, var18);
    local_24 = local_C->unk_00;
    sub_44350(arg_4, &local_24);
}

// match: sub_4A8B0 @ 0x0004A8B0
// sp-match: sub_4A8B0 @ 0x000388E0
// "UnregisterDistanceCheck": all of the object's registrations.
void sub_4A8B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    sub_35330(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_4A8F0 @ 0x0004A8F0
// sp-match: sub_4A8F0 @ 0x00038910
// "UnregisterDistanceCheckPtr": the registration with the handle arg 1.
void sub_4A8F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 local_8;
    alfasched_entry *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (alfasched_entry *)sub_67620(local_8);
    if (var_4 != 0)
        sub_35360(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_4A960 @ 0x0004A960
// sp-match: sub_4A960 @ 0x00038960
// "DistanceToTarget": the target's record distance (unk_0C of sub_16ED0's
// record), else the distance between the entity and its target; 50 without
// a target.
void sub_4A960(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwV3d stk_18;
#endif
    type_154C0_80 *ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    v8 = 50.0f;
    var_4 = sub_45170(arg_0);
    if (var_4->vf_120() != 0 && var_4->vf_120()->get_unk_1374() != 0) {
        ebp_C = var_4->vf_120()->sub_16ED0(var_4->vf_120()->get_unk_1374(), 0);
        if (ebp_C != 0) {
            v8 = ebp_C->unk_0C;
        } else if (var_4->vf_120()->get_unk_1374() != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules its stores as SP 0x38960 does
            RwV3d stk_18;

#endif
            RwV3dSub(&stk_18, var_4->sub_CD550(),
                     var_4->vf_120()->get_unk_1374()->sub_CD550());
            v8 = RwV3dLength(&stk_18);
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_4AB20 @ 0x0004AB20
// sp-match: sub_4AB20 @ 0x00038AF0
// "IHaveATarget".
void sub_4AB20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    if (local_8->vf_120() != 0 && local_8->vf_120()->get_unk_1374() != 0)
        var_4 = 1;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4AB90 @ 0x0004AB90
// match: __ehhandler$?sub_4AB90@@YAXIPAUtype_44350@@@Z-0xB @ 0x002FF800
// match: __ehhandler$?sub_4AB90@@YAXIPAUtype_44350@@@Z @ 0x002FF80B
// sp-match: sub_4AB90 @ 0x00056EF0
// "PlayParticleSystemAtXYZ": spawns the surface particle list of table arg 1
// (0 to 3) at (arg 2, arg 3, arg 4), upright; for the shell and anti-tank
// tables also sets off a blast there (sub_9A960) and, within 500 units of the
// player's trigger volume, shakes the player's view (sub_1109A0).
void sub_4AB90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwMatrix var_50;
    RwV3d *var_54;
    RwInt32 var_58;
    type_10F710 *var_94;
#ifndef CODFH_SP
    RwV3d var_A0;
#endif
    RwReal var_A4;

    RwMatrixSetIdentityMacro(&var_50);
    var_54 = &var_50.up;
    var_54->x = 0.0f;
    var_54->y = 1.0f;
    var_54->z = 0.0f;
    var_58 = SCRIPT_ARG(arg_4, 1);
    var_50.pos.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_50.pos.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_50.pos.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    SCRIPT_CHECK(var_58 >= 0 && var_58 < 4);
    sub_F2750(var_58, 0, &var_50, 0);
    if (var_58 == 2 || var_58 == 1 || var_58 == 3)
    {
        type_4AE70 var_90;

        var_90.unk_00 = 0x804;
        var_90.unk_08 = 0;
        var_90.unk_0C = &var_50;
        var_90.unk_10 = 1000.0f;
        var_90.unk_14 = 1000.0f;
        var_90.unk_18 = 1000.0f;
        var_90.unk_2C = 200.0f;
        sub_9A960(&var_90);
        var_94 = (type_10F710 *)sub_1745A0(0);
        if (var_94)
        {
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules its stores as SP 0x56EF0 does
            RwV3d var_A0;
#endif
            RwV3dSubMacro(&var_A0, &var_50.pos, (RwV3d *)var_94->vf_0C4());
            var_A4 = RwV3dLength((RwV3d *)&var_A0);
            if (var_A4 < 500.0f)
            {
                var_94->sub_1109A0(5.0f, 1.0f);
            }
        }
    }
    sub_44350(arg_4, 0);
}

// match: ??0type_4AE70@@QAE@XZ @ 0x0004AE70
// sp-match: ??0type_4AE70@@QAE@XZ @ 0x00032F00
type_4AE70::type_4AE70()
{
    unk_00 = 0;
    unk_08 = 0;
    unk_0C = 0;
    unk_10 = 0;
    unk_14 = 0;
    unk_18 = 0;
    unk_1C.x = 0;
    unk_1C.y = 0;
    unk_1C.z = 0;
    unk_28 = 0;
    unk_2C = 0;
    unk_30 = 0;
}

// match: sub_4AF10 @ 0x0004AF10
// sp-match: sub_4AF10 @ 0x00038B80
// "SpawnParticleSpawner": sets up a free spawner on the entity with the
// particle systems arg 1 and arg 2 at arg 5 per second (x60 per frame),
// attached at arg 4.
void sub_4AF10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    RwReal var18;
    type_4B9E90 *stk_14;
    type_3D3548 *l10;
    RwReal local_C;
    RwReal lv_8;
    RwInt32 var_4;

    l10 = sub_45170(arg_0);
    stk_14 = sub_F1230();
    local_24 = SCRIPT_ARG(arg_4, 1);
    var_1C = SCRIPT_ARG(arg_4, 2);
    local_C = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_4 = SCRIPT_ARG(arg_4, 4);
    lv_8 = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var18 = SCRIPT_ARGT<RwReal>(arg_4, 6);
    local_20 = SCRIPT_ARG(arg_4, 7);
    stk_14->sub_F0880(local_24, var_1C, lv_8 * 60.0f, local_20);
    stk_14->sub_F0A10(l10, var_4, 1);
    stk_14->unk_2C = var18;
    stk_14->sub_F0AA0(local_C);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4B0B0 @ 0x0004B0B0
// sp-match: sub_4B0B0 @ 0x00038C50
// "KillParticleSpawner": frees the entity.
void sub_4B0B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    sub_F12A0(var_4, 0);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4B0F0 @ 0x0004B0F0
// sp-match: sub_4B0F0 @ 0x00038C80
// "SwitchToDestroyedClump": whether the entity (of the vf_010 subclass) did.
void sub_4B0F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0 && var_4->vf_010() != 0)
        local_8 = var_4->vf_010()->sub_153CB0();
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_4B150 @ 0x0004B150
// sp-match: sub_4B150 @ 0x00038D00
// "EnableWeaponRender": a soldier's or a type_3DDB98's.
void sub_4B150(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (local_8->vf_008() != 0)
        local_8->vf_008()->sub_13F660(varC, var_4);
    if (local_8->vf_024() != 0)
        local_8->vf_024()->sub_17A840(varC, var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4B220 @ 0x0004B220
// sp-match: sub_4B220 @ 0x00038D90
// "SetRenderPartState": shows (arg 2 set) or hides render part arg 1.
void sub_4B220(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwUInt32 var_4;

    ebp_C = sub_45170(arg_0);
    var_10 = SCRIPT_ARG(arg_4, 1);
    v8 = SCRIPT_ARG(arg_4, 2);
    l14 = sub_16E0C0(ebp_C->get_unk_264());
    var_4 = 1 << var_10;
    if (v8 != 0)
        l14 = l14 | var_4;
    else
        l14 = ~var_4 & l14;
    sub_16E080(ebp_C->get_unk_264(), l14);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4B300 @ 0x0004B300
// sp-match: sub_4B300 @ 0x00038E10
// "GetRenderPartState": whether render part arg 1 is shown.
void sub_4B300(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwUInt32 var_4;

    ebp_C = sub_45170(arg_0);
    v8 = 0;
    var_10 = SCRIPT_ARG(arg_4, 1);
    var_4 = 1 << var_10;
    l14 = sub_16E0C0(ebp_C->get_unk_264());
    if ((l14 & var_4) == var_4)
        v8 = 1;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_4B3A0 @ 0x0004B3A0
// sp-match: sub_4B3A0 @ 0x00038EA0
// "SetRenderPartStateByName": shows (arg 2 set) or hides the render part the
// kind-0x2E object under the key arg 1 (two slots) names (its unk_14).
void sub_4B3A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3DF8D8_04 *ebp_C;
    type_3D3548 *v8;
    type_3DF8D8 *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    ebp_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    var_4 = sub_198800(ebp_C);
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->vf_008() == 0x2E);
    sub_16D8C0(v8->get_unk_264(), (const RwChar *)var_4->unk_14, var_10 != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4B490 @ 0x0004B490
// match: __ehhandler$?sub_4B490@@YAXIPAUtype_44350@@@Z-8 @ 0x002FF820
// match: __ehhandler$?sub_4B490@@YAXIPAUtype_44350@@@Z @ 0x002FF828
// sp-match: sub_4B490 @ 0x00038FD0
// "CreateExplosionZone": sets off a blast of kind arg 1 (0x801 for 1, 0x802
// for 2, else 0x804) with the radius arg 2 (100 when not above 0) and
// arg 3 (its unk_2C) at (arg 4, arg 5, arg 6), or at the entity when that
// point is the origin.
void sub_4B490(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_4AE70 var_44;
    RwInt32 var_48;
    RwReal var_4C;
    RwReal var_50;
    RwV3d var_5C;
    type_3D3548 *var_60;
    RwMatrix var_B0;

    var_48 = SCRIPT_ARG(arg_4, 1);
    var_4C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_50 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_5C.x = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_5C.y = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_5C.z = SCRIPT_ARGT<RwReal>(arg_4, 6);
    if (var_5C.x == 0.0f && var_5C.y == 0.0f && var_5C.z == 0.0f) {
        var_60 = sub_45170(arg_0);
        if (var_60 != 0)
            var_5C = *var_60->sub_CD550();
    }
    if (var_4C <= 0.0f)
        var_4C = 100.0f;
    switch (var_48) {
    case 1:
        var_44.unk_00 = 0x801;
        break;
    case 2:
        var_44.unk_00 = 0x802;
        break;
    default:
        var_44.unk_00 = 0x804;
        break;
    }
    RwMatrixSetIdentityMacro(&var_B0);
    var_B0.pos = var_5C;
    var_44.unk_08 = 0;
    var_44.unk_0C = &var_B0;
    var_44.unk_10 = var_4C;
    var_44.unk_14 = var_4C;
    var_44.unk_18 = var_4C;
    var_44.unk_2C = var_50;
    sub_9A960(&var_44);
    sub_44350(arg_4, 0);
}

// match: sub_4B770 @ 0x0004B770
// sp-match: sub_4B770 @ 0x000391B0
// "IsLevelSectionLoaded": whether a live collision-world entry holds
// section arg 1.
void sub_4B770(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_4E5D30 *var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    RwUInt16 var_4;

    var_4 = SCRIPT_ARGT<RwUInt16>(arg_4, 1);
    v8 = 0;
    for (ebp_C = 0; ebp_C < 4; ebp_C++) {
        var_10 = &dword_4E5D30[ebp_C];
        if (var_10->get_unk_00() != 0 && var_10->get_unk_08() == var_4) {
            v8 = 1;
            break;
        }
    }
    sub_44350(arg_4, &v8);
}

// match: sub_4B820 @ 0x0004B820
// sp-match: sub_4B820 @ 0x00039230
// "RequestClumpBankLoad".
void sub_4B820(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_16EEC0(SCRIPT_ARG(arg_4, 1));
    sub_44350(arg_4, 0);
}

// match: sub_4B870 @ 0x0004B870
// sp-match: sub_4B870 @ 0x00039270
// "IsClumpBankLoaded".
void sub_4B870(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = sub_16EE80(SCRIPT_ARG(arg_4, 1));
    sub_44350(arg_4, &var_4);
}

// match: sub_4B8C0 @ 0x0004B8C0
// sp-match: sub_4B8C0 @ 0x000392E0
// "SetDefaultClumpBank".
void sub_4B8C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_429EA8 = var_4;
    sub_44350(arg_4, 0);
}

// match: sub_4B910 @ 0x0004B910
// sp-match: sub_4B910 @ 0x00039310
// "SetCheckPointRegister": sets the register and records the checkpoint
// named by the object under the key dword_4B914C.
void sub_4B910(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8 *var_4;

    dword_4B8780 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800((type_3DF8D8_04 *)&dword_4B914C);
    SCRIPT_CHECK(var_4 != 0);
    sub_EACA0(var_4->sub_197550(0, 0), 2, 1);
    sub_44350(arg_4, 0);
}

// match: sub_4B990 @ 0x0004B990
// sp-match: sub_4B990 @ 0x000393B0
// "GetCheckPointRegister".
void sub_4B990(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_44350(arg_4, &dword_4B8780);
}

// match: sub_4B9B0 @ 0x0004B9B0
// sp-match: sub_4B9B0 @ 0x000393F0
// "SetStartingSections": its four arguments.
void sub_4B9B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10[4];

    var_10[0] = SCRIPT_ARG(arg_4, 1);
    var_10[1] = SCRIPT_ARG(arg_4, 2);
    var_10[2] = SCRIPT_ARG(arg_4, 3);
    var_10[3] = SCRIPT_ARG(arg_4, 4);
    sub_1727E0(var_10);
    sub_44350(arg_4, 0);
}

// match: sub_4BA80 @ 0x0004BA80
// sp-match: sub_4BA80 @ 0x00039460
// "TakeCheckpointSnapshot".
void sub_4BA80(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_D9320();
    sub_44350(arg_4, 0);
}

// sub_4BAA0 ("SpawnParticleAtPosition") stays binary (docs/units.md).

// match: sub_4BAA0 @ 0x0004BAA0
// sp-match: sub_4BAA0 @ 0x00039480
// "SpawnParticleAtPosition": spawns the particle system arg 1 at
// (arg 2, arg 3, arg 4), unrotated.
void sub_4BAA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwMatrix var_40;

    RwMatrixSetIdentityMacro(&var_40);
    var_40.pos.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_40.pos.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_40.pos.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    sub_F2FF0(SCRIPT_ARG(arg_4, 1), &var_40, 0, 1, 0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_4BBE0 @ 0x0004BBE0
// sp-match: sub_4BBE0 @ 0x00039570
// "SpawnParticle": particle system arg 1 at the trigger entity's frame, or
// at the trigger's own matrix without an entity.
void sub_4BBE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    type_3D3548 *var_4;

    ebp_C = sub_67620(arg_0);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    var_4 = v8->sub_71300();
    if (var_4 != 0) {
        RwFrame *var_14 = var_4->get_unk_340();

        if (var_14 != 0)
            sub_F2FF0(SCRIPT_ARG(arg_4, 1), RwFrameGetLTM(var_14), 0, 1, 0, 0);
    } else {
        sub_F2FF0(SCRIPT_ARG(arg_4, 1), (RwMatrix *)var_10->unk_60, 0, 1, 0, 0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_4BCF0 @ 0x0004BCF0
// sp-match: sub_4BCF0 @ 0x00039650
// "DestroyParticle": the trigger's (of kind 0x12).
void sub_4BCF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *varC;
    type_67620 *local_8;
    type_3D2E7C *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = local_8->vf_024();
    SCRIPT_CHECK(var_4 != 0);
    varC = var_4->sub_712B0();
    SCRIPT_CHECK(varC->vf_008() == 0x12);
    ((ParticleTrigger *)varC)->sub_A8F40();
    sub_44350(arg_4, 0);
}

// match: sub_4BD70 @ 0x0004BD70
// sp-match: sub_4BD70 @ 0x00039710
// "SpecialCCESSPoolCreation": the handle of the pool entity's object, 0 when
// none was created.
void sub_4BD70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_1C;
    type_3D2E7C *var18;
    RwUInt32 stk_14;
    type_712B0 *l10;
    type_67620 *local_C;
    type_3D2E7C *lv_8;
    type_3D3548 *var_4;

    stk_14 = 0;
    local_C = sub_67620(arg_0);
    lv_8 = local_C->vf_024();
    SCRIPT_CHECK(lv_8 != 0);
    l10 = lv_8->sub_712B0();
    SCRIPT_CHECK(l10 != 0);
    if (sub_8B4C0(l10, &var_4) != 0) {
        var18 = var_4->vf_098();
        if (var18 != 0) {
            var_1C = var18->unk_04;
            stk_14 = var_1C;
        }
    }
    sub_44350(arg_4, &stk_14);
}

// match: sub_4BE20 @ 0x0004BE20
// sp-match: sub_4BE20 @ 0x00039820
// "ClearCCESSPoolTriggers".
void sub_4BE20(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    sub_8B380(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_4BE70 @ 0x0004BE70
// sp-match: sub_4BE70 @ 0x00039860
// "GetSquadLeader": the handle of its object, 0 without one.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_4BE70(RwUInt32 arg_0, type_44350 *arg_4)
{
    // Six locals the image reserves and never uses.
    RwInt32 bp_2C;
    RwInt32 local_28;
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    RwInt32 var18;
    RwUInt32 stk_14;
    type_3D3548 *l10;
    AIData *local_C;
    RwUInt32 lv_8;
    type_3D3548 *var_4;

    lv_8 = 0;
    var_4 = sub_45170(arg_0);
    local_C = var_4->vf_120();
    if (local_C != 0) {
        l10 = local_C->sub_170C0();
        if (l10 != 0) {
            stk_14 = l10->vf_098()->get_unk_04_d();
            lv_8 = stk_14;
        }
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_4BEF0 @ 0x0004BEF0
// sp-match: sub_4BEF0 @ 0x000398E0
// "SetSquadLeader": makes the entity (arg 1 set) or the player the leader of
// its group.
void sub_4BEF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    type_3DF30 *var_10;
    RwInt32 ebp_C;
    AIData *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    v8 = var_4->vf_120();
    ebp_C = SCRIPT_ARG(arg_4, 1);
    if (v8 != 0) {
        var_10 = v8->get_unk_56C();
        SCRIPT_CHECK(var_10 != 0);
        if (ebp_C != 0) {
            var_10->sub_3E780(var_4);
        } else {
            l14 = sub_1745A0(0);
            var_10->sub_3E780(l14);
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4BFA0 @ 0x0004BFA0
// sp-match: sub_4BFA0 @ 0x00039990
// "SetAIMode": the AI object's answer (sub_17BF0) for mode arg 1; 0 without
// one.
void sub_4BFA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    AIData *ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    v8 = sub_45170(arg_0);
    ebp_C = v8->vf_120();
    var_4 = 0;
    if (ebp_C != 0) {
        var_10 = SCRIPT_ARG(arg_4, 1);
        var_4 = ebp_C->sub_17BF0(var_10);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C020 @ 0x0004C020
// sp-match: sub_4C020 @ 0x00039A20
// "GetAIMode": the AI object's state unk_578, -1 without one.
void sub_4C020(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = -1;
    local_8 = sub_45170(arg_0);
    varC = local_8->vf_120();
    if (varC != 0)
        var_4 = varC->get_unk_578();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C080 @ 0x0004C080
// sp-match: sub_4C080 @ 0x00039A90
// "SetAIFlag": sets flag arg 1 of the AI object's unk_49C and reports it.
void sub_4C080(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwChar var_60[80];
    AIData *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_120();
    if (local_8 != 0) {
        RwUInt32 var_68;
        type_67620 *var_64;

        var_68 = SCRIPT_ARG(arg_4, 1);
        local_8->sub_16D70(var_68);
        sprintf(var_60, "Set flag %x, flag field now %x", var_68, local_8->unk_49C);
        var_64 = sub_67620(arg_0);
        sub_6B060(var_64, var_60, 0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C150 @ 0x0004C150
// sp-match: sub_4C150 @ 0x00039B30
// "GetAIFlag": the AI object's unk_49C flags under the mask arg 1.
void sub_4C150(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_10;
    AIData *ebp_C;
    type_3D3548 *v8;
    RwUInt32 var_4;

    var_4 = 0;
    v8 = sub_45170(arg_0);
    ebp_C = v8->vf_120();
    if (ebp_C != 0) {
        var_10 = SCRIPT_ARG(arg_4, 1);
        var_4 = ebp_C->unk_49C & var_10;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C1D0 @ 0x0004C1D0
// sp-match: sub_4C1D0 @ 0x00039BB0
// "ClearAIFlag": as "SetAIFlag", clearing it.
void sub_4C1D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwChar var_60[80];
    AIData *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_120();
    if (local_8 != 0) {
        RwUInt32 var_68;
        type_67620 *var_64;

        var_68 = SCRIPT_ARG(arg_4, 1);
        local_8->sub_16DD0(var_68);
        sprintf(var_60, "Clear flag %x, flag field now %x", var_68, local_8->unk_49C);
        var_64 = sub_67620(arg_0);
        sub_6B060(var_64, var_60, 0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C2A0 @ 0x0004C2A0
// sp-match: sub_4C2A0 @ 0x00039C50
// "SetAIParam".
void sub_4C2A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        varC = SCRIPT_ARG(arg_4, 1);
        local_8 = SCRIPT_ARG(arg_4, 2);
        var_4->vf_16C(varC, local_8);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C340 @ 0x0004C340
// sp-match: sub_4C340 @ 0x00039CB0
// "SetManeuverType": of the entity's group, for the entity.
void sub_4C340(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    type_3DF30 *var_4;

    ebp_C = sub_45170(arg_0);
    v8 = SCRIPT_ARG(arg_4, 1);
    var_10 = ebp_C->vf_120();
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->get_unk_56C();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_3E990(ebp_C, v8);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C3E0 @ 0x0004C3E0
// sp-match: sub_4C3E0 @ 0x00039D90
// "GetManeuverType": the kind (vf_030) of the maneuver the AI object's
// unk_574 names; -1 without one.
void sub_4C3E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 l14;
    AIData *var_10;
    type_3CE6D0 *ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    v8 = sub_45170(arg_0);
    var_4 = -1;
    var_10 = v8->vf_120();
    SCRIPT_CHECK(var_10 != 0);
    l14 = var_10->get_unk_574();
    ebp_C = sub_3D3E0(l14);
    if (ebp_C != 0)
        var_4 = ebp_C->vf_030();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C460 @ 0x0004C460
// sp-match: sub_4C460 @ 0x00039E50
// "SetManeuverState": the AI object's unk_58.
void sub_4C460(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4->vf_120() != 0)
        var_4->vf_120()->unk_58 = SCRIPT_ARG(arg_4, 1);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C4E0 @ 0x0004C4E0
// sp-match: sub_4C4E0 @ 0x00039EB0
// "GetMyTarget": the handle of the target's object, 0 without one.
void sub_4C4E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 l14;
    type_3D3548 *var_10;
    type_3D2E7C *ebp_C;
    type_3D3548 *v8;
    RwUInt32 var_4;

    v8 = sub_45170(arg_0);
    ebp_C = 0;
    var_4 = 0;
    if (v8 != 0) {
        SCRIPT_CHECK(v8->vf_120() != 0);
        var_10 = v8->vf_120()->get_unk_1374();
        if (var_10 != 0) {
            ebp_C = var_10->vf_098();
            if (ebp_C != 0) {
                l14 = ebp_C->unk_04;
                var_4 = l14;
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C590 @ 0x0004C590
// sp-match: sub_4C590 @ 0x00039F90
// "SetMyTarget": the entity of the object with the handle arg 1, through the
// AI object or, without one, sub_180CA0.
void sub_4C590(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    RwUInt32 ebp_C;
    type_3D3548 *v8;
    type_3D2E7C *var_4;

    v8 = sub_45170(arg_0);
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        var_10 = var_4->sub_71300();
        if (v8 != 0 && var_10 != 0) {
            if (v8->vf_120() != 0)
                v8->vf_120()->sub_18BB0(var_10);
            else if (v8->vf_02C() != 0)
                ((type_3DE0E0 *)v8)->sub_180CA0(var_10);
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C670 @ 0x0004C670
// sp-match: sub_4C670 @ 0x0003A060
// "ClearMyTarget".
void sub_4C670(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        SCRIPT_CHECK(var_4->vf_120() != 0);
        var_4->vf_120()->sub_18BB0(0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C6D0 @ 0x0004C6D0
// sp-match: sub_4C6D0 @ 0x0003A0F0
// "GetEntityToFollow": the handle of its object, 0 without one.
void sub_4C6D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 stk_18;
    type_3D3548 *l14;
    AIData *var_10;
    type_3D2E7C *ebp_C;
    type_3D3548 *v8;
    RwUInt32 var_4;

    v8 = sub_45170(arg_0);
    ebp_C = 0;
    var_4 = 0;
    if (v8 != 0) {
        var_10 = v8->vf_120();
        if (var_10 != 0) {
            l14 = var_10->unk_580.sub_D4910();
            if (l14 != 0) {
                ebp_C = l14->vf_098();
                if (ebp_C != 0) {
                    stk_18 = ebp_C->unk_04;
                    var_4 = stk_18;
                }
            }
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4C770 @ 0x0004C770
// sp-match: sub_4C770 @ 0x0003A180
// "SetEntityToFollow": the entity of the object with the handle arg 1 (none
// for 0), at the distance arg 2.
void sub_4C770(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *stk_18;
    RwUInt32 l14;
    type_3D3548 *var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    type_3D2E7C *var_4;

    var_10 = 0;
    v8 = sub_45170(arg_0);
    l14 = SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_4 = (type_3D2E7C *)sub_67620(l14);
    if (var_4 != 0)
        var_10 = var_4->sub_71300();
    if (v8 != 0) {
        stk_18 = v8->vf_120();
        SCRIPT_CHECK(stk_18 != 0);
        stk_18->unk_580.sub_D48D0(var_10);
        stk_18->unk_58C = ebp_C;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C860 @ 0x0004C860
// sp-match: sub_4C860 @ 0x0003A250
// "FireWeaponXTimes": the AI object's unk_494 (arg 1) and shot count unk_498
// (arg 2).
void sub_4C860(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    ebp_C = sub_45170(arg_0);
    var_10 = SCRIPT_ARG(arg_4, 1);
    v8 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_494 = var_10;
    var_4->unk_498 = v8;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C930 @ 0x0004C930
// sp-match: sub_4C930 @ 0x0003A330
// "FireWeaponContinuous": through a type_3DBC78's vf_2AC or a type_3DE0E0's
// vf_234.
void sub_4C930(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4->vf_010() != 0)
        ((type_3DBC78 *)var_4)->vf_2AC(local_8);
    else if (var_4->vf_02C() != 0)
        ((type_3DE0E0 *)var_4)->vf_234(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4C9E0 @ 0x0004C9E0
// sp-match: sub_4C9E0 @ 0x0003A3E0
// "RequestAIAction_RetreatFromTarget": the AI object's one-shot unk_68.
void sub_4C9E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_68 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CA50 @ 0x0004CA50
// sp-match: sub_4CA50 @ 0x0003A4A0
// "RequestAIAction_PursueTarget": the AI object's unk_6C.
void sub_4CA50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_6C = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CAC0 @ 0x0004CAC0
// sp-match: sub_4CAC0 @ 0x0003A560
// "RequestAIAction_AttackFromCover": sub_28F00.
void sub_4CAC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_28F00();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CB20 @ 0x0004CB20
// sp-match: sub_4CB20 @ 0x0003A620
// "EnableCanShootCheckMessages".
void sub_4CB20(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_19010(ebp_C, var_10);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CBE0 @ 0x0004CBE0
// sp-match: sub_4CBE0 @ 0x0003A700
// "EnableGrenadeHints": on (sub_1FC40) or off (sub_1FC70).
void sub_4CBE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    if (varC != 0)
        var_4->sub_1FC40();
    else
        var_4->sub_1FC70();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CC80 @ 0x0004CC80
// sp-match: sub_4CC80 @ 0x0003A7E0
// "DisableGoGoGo": the AI object's GoGoGo state to -1.
void sub_4CC80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_1A5A0(-1);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CCF0 @ 0x0004CCF0
// sp-match: sub_4CCF0 @ 0x0003A8A0
// "FoundPointPathForGoGoGo": whether the GoGoGo state unk_1430 is 1, moving
// it on to 2.
void sub_4CCF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    AIData *var_4;

    varC = sub_45170(arg_0);
    SCRIPT_CHECK(varC != 0);
    var_4 = varC->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    local_8 = 0;
    if (var_4->get_unk_1430() == 1) {
        var_4->sub_1A5A0(2);
        local_8 = 1;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_4CD80 @ 0x0004CD80
// sp-match: sub_4CD80 @ 0x0003A9A0
// "DidIJustGoGoGo": whether the GoGoGo time unk_1434 is under 60 old.
void sub_4CD80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    AIData *var_4;

    varC = sub_45170(arg_0);
    SCRIPT_CHECK(varC != 0);
    var_4 = varC->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    local_8 = 0;
    if (get_dword_4B87C8() - var_4->get_unk_1434() < 60.0f)
        local_8 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_4CE10 @ 0x0004CE10
// sp-match: sub_4CE10 @ 0x0003AAA0
// "FinishedGoGoGo": stamps the GoGoGo time unk_1434.
void sub_4CE10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_1434 = get_dword_4B87C8();
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4CE80 @ 0x0004CE80
// sp-match: sub_4CE80 @ 0x0003AB60
// "CanIShoot": the entity's line-of-fire test (vf_134) against its target.
void sub_4CE80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwInt32 var_10;
    RwV3d var_C;

    l14 = sub_45170(arg_0);
    SCRIPT_CHECK(l14 != 0);
    SCRIPT_CHECK(l14->vf_120() != 0);
    var_C.x = 0.0f;
    var_C.y = 0.0f;
    var_C.z = 0.0f;
    var_10 = l14->vf_134(&var_C, l14->vf_120()->get_unk_1374(), 1, 1, 0, 0, -1);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_4CF30 @ 0x0004CF30
// sp-match: sub_4CF30 @ 0x0003AC90
// "GetTargetsCanShootStatus": the AI object's unk_544.
void sub_4CF30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK(local_8->vf_120() != 0);
    var_4 = local_8->vf_120()->unk_544;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4CFA0 @ 0x0004CFA0
// sp-match: sub_4CFA0 @ 0x0003AD80
// "CanIDiveForward": whether a soldier can dive 450 along its facing, making
// the landing point its unk_604 when it can.
void sub_4CFA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_18;
    type_3DAFC8 *l14;
    RwV3d var_10;
    RwInt32 var_4;

    l14 = 0;
    stk_18 = sub_45170(arg_0);
    l14 = stk_18->vf_008();
    SCRIPT_CHECK(l14 != 0);
    RwV3dScale(&var_10, l14->sub_CD5A0(), 450.0f);
    var_4 = l14->sub_13E9A0(&var_10, 0, 0);
    if (var_4 != 0)
        RwV3dAdd(&l14->unk_604, l14->sub_CD550(), &var_10);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// An inline function declaring one local it never uses, with no address and
// so no database name; named for what it does. Evidence: "PlayDiveToPoint"
// (sub_4D090) reserves one slot after its last check's five, which only an
// inline function's local takes (a block's locals come before every inline
// one's, docs/toolchain.md). What the original inline did is not known.
inline void SCRIPT_RESERVE_1()
{
    RwInt32 reserve_0;
}

// match: sub_4D090 @ 0x0004D090
// sp-match: sub_4D090 @ 0x0003AEB0
// "PlayDiveToPoint": plays a soldier's current performance at its AI
// object's point unk_5B0, for an object of kind 2.
void sub_4D090(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_67620 *ebp_C;
    type_3DAFC8 *v8;
    AIData *var_4;

    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    SCRIPT_CHECK(ebp_C->vf_024()->get_unk_14() == 2);
    v8 = 0;
    var_10 = sub_45170(arg_0);
    v8 = var_10->vf_008();
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8->vf_088(0);
    sub_47F90(ebp_C, v8, &var_4->unk_5B0, 0, 0, 0, 0);
    SCRIPT_RESERVE_1();
    sub_44350(arg_4, 0);
}

// match: sub_4D170 @ 0x0004D170
// sp-match: sub_4D170 @ 0x0003AFF0
// "CanIDiveAwayFromGrenade": whether its soldier can dive to one side of its
// grenade's path (45 degrees off, then straight across, then the other
// side, sub_13E9A0), sending its AI object there (unk_604).
void sub_4D170(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAFC8 *var_4;
    type_3D3548 *var_8;
    AIData *var_C;
    RwInt32 var_10;
    RwV3d var_1C;
    RwV3d var_28;
    RwV3d var_34;
    RwV3d var_40;
    RwV3d var_4C;
    RwMatrix var_90;
    RwV3d *var_94;
    RwV3d *var_98;
    RwV3d var_A4;

    var_4 = 0;
    var_8 = sub_45170(arg_0);
    var_4 = var_8->vf_008();
    SCRIPT_CHECK(var_4 != 0);
    var_C = var_4->vf_120();
    SCRIPT_CHECK(var_C != 0);
    var_10 = 0;
    if (!var_4->unk_610)
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, (void *)var_10);
        return;
    }
    var_1C = *var_4->unk_610->vf_05C();
    var_28 = var_4->unk_610->unk_10;
    var_28.y = 0.0f;
    RwV3dSubMacro(&var_34, &var_1C, var_4->sub_CD550());
    var_34.y = 0.0f;
    if (RwV3dLength((RwV3d *)&var_28) < flt_3CE9BC)
    {
        var_28 = var_34;
    }
    RwV3dNormalize(&var_28, &var_28);
    var_40.x = -var_28.z;
    var_40.y = 0.0f;
    var_40.z = var_28.x;
    var_4C.x = var_28.z;
    var_4C.y = 0.0f;
    var_4C.z = -var_28.x;
    RwV3dScaleMacro(&var_40, &var_40, 450.0f);
    RwV3dScaleMacro(&var_4C, &var_4C, 450.0f);
    RwMatrixSetIdentityMacro(&var_90);
    if (RwV3dDotProductMacro(&var_40, &var_34) <= 0.0f)
    {
        var_94 = &var_40;
        var_98 = &var_4C;
        RwMatrixRotate(&var_90, &var_90.up, -45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_A4, &var_40, &var_90);
    }
    else
    {
        var_94 = &var_4C;
        var_98 = &var_40;
        RwMatrixRotate(&var_90, &var_90.up, 45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_A4, &var_4C, &var_90);
    }
    if (var_4->sub_13E9A0(var_94, 0, 0))
    {
        RwV3dAddMacro(&var_4->unk_604, var_94, var_4->sub_CD550());
        var_C->sub_17140(&var_4->unk_604);
        var_10 = 1;
    }
    else if (var_4->sub_13E9A0(&var_A4, 0, 0))
    {
        RwV3dAddMacro(&var_4->unk_604, &var_A4, var_4->sub_CD550());
        var_C->sub_17140(&var_4->unk_604);
        var_10 = 1;
    }
    else if (var_4->sub_13E9A0(var_98, 0, 0))
    {
        RwV3dAddMacro(&var_4->unk_604, var_98, var_4->sub_CD550());
        var_C->sub_17140(&var_4->unk_604);
        var_10 = 1;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_4D660 @ 0x0004D660
// sp-match: sub_4D660 @ 0x0003B400
// "CanGetCoverFromGrenade": a soldier's AI object's cover search
// (sub_28640) from its unk_610 point; with no unk_610 it fails the check and
// returns the result by value (0, a null pointer to the value).
void sub_4D660(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3DAFC8 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    ebp_C = 0;
    var_10 = sub_45170(arg_0);
    ebp_C = var_10->vf_008();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8 = 0;
    if (ebp_C->unk_610 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, (void *)v8);
    } else {
        // sub_28640 takes the point's address as its dword argument.
        v8 = var_4->sub_28640((RwInt32)&ebp_C->unk_610->unk_04);
        sub_44350(arg_4, &v8);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_4D720 @ 0x0004D720
// sp-match: sub_4D720 @ 0x0003B520
// "CanGetPointFromGrenade": a soldier's AI object's point search (sub_28470)
// from its unk_610 object's point (vf_05C); 0 with no unk_610.
void sub_4D720(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3DAFC8 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    ebp_C = 0;
    var_10 = sub_45170(arg_0);
    ebp_C = var_10->vf_008();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8 = 0;
    if (ebp_C->unk_610 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &v8);
    } else {
        v8 = var_4->sub_28470(ebp_C->unk_610->vf_05C());
        sub_44350(arg_4, &v8);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_4D7F0 @ 0x0004D7F0
// sp-match: sub_4D7F0 @ 0x0003B650
// "SetMoveOutOfWayFattyPoint": the AI object's answer (sub_21C90) for the
// entity of the object with the handle arg 1; 0 otherwise.
void sub_4D7F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    type_3D2E7C *var_10;
    RwUInt32 ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    var_4 = sub_45170(arg_0);
    v8 = 0;
    if (var_10 != 0) {
        l14 = var_10->sub_71300();
        if (l14 != 0 && var_4 != 0 && var_4->vf_120() != 0)
            v8 = var_4->vf_120()->sub_21C90(l14);
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_4D8B0 @ 0x0004D8B0
// sp-match: sub_4D8B0 @ 0x0003B700
// "GetContactType": a soldier's AI object's sub_22110, unless its side
// (unk_2C & 7) is 1; 0 otherwise.
void sub_4D8B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    if (local_8->vf_008() != 0) {
        varC = local_8->unk_2C & 7;
        if (varC != 1)
            var_4 = local_8->vf_008()->vf_120()->sub_22110();
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4D930 @ 0x0004D930
// sp-match: sub_4D930 @ 0x0003B790
// "EnableColorCodedName": a soldier's unk_64C.
void sub_4D930(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4->vf_008() != 0)
        var_4->vf_008()->unk_64C = SCRIPT_ARG(arg_4, 1);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// sub_4D9B0 ("RotateMyOrientation") and sub_4DB20 ("CanIDiveAwayFromTank")
// stay binary (docs/units.md).

// match: sub_4D9B0 @ 0x0004D9B0
// sp-match: sub_4D9B0 @ 0x0003B7F0
// "RotateMyOrientation": turns its frame by the angles arg 1, arg 2 and
// arg 3 about its own up, right and at axes.
void sub_4D9B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    RwFrame *var_C;
    RwMatrix var_50;
    RwReal var_54;
    RwReal var_58;
    RwReal var_5C;

    var_4 = sub_45170(arg_0);
    var_C = var_4->get_unk_340();
    var_50 = *RwFrameGetMatrix(var_C);
    var_54 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_58 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_5C = SCRIPT_ARGT<RwReal>(arg_4, 3);
    if (var_54 != 0.0f)
    {
        RwMatrixRotate(&var_50, &var_50.up, var_54, rwCOMBINEPRECONCAT);
    }
    if (var_58 != 0.0f)
    {
        RwMatrixRotate(&var_50, &var_50.right, var_58, rwCOMBINEPRECONCAT);
    }
    if (var_5C != 0.0f)
    {
        RwMatrixRotate(&var_50, &var_50.at, var_5C, rwCOMBINEPRECONCAT);
    }
    RwFrameTransform(var_C, &var_50, rwCOMBINEREPLACE);
    sub_44350(arg_4, 0);
}

// match: sub_4DB20 @ 0x0004DB20
// sp-match: sub_4DB20 @ 0x0003B900
// "CanIDiveAwayFromTank": whether its soldier can dive clear of the tank
// threatening it (unk_614): 450 units across the tank's heading (sub_CD5A0)
// on the side away from it, then 45 degrees either way of that (sub_13E9A0,
// ignoring the tank); failing those, the nearest of the tank's cover points
// (unk_263C: usable ones, free ones first, then those with bit 0). The AI
// object heads for the chosen point, 100 units up.
void sub_4DB20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAFC8 *var_4;
    type_3D3548 *var_8;
    AIData *var_C;
    RwInt32 var_10;
    type_3D3548 *var_14;
    RwV3d *var_18;
    RwV3d var_24;
    RwV3d var_44;
    RwMatrix var_A0;
    RwV3d var_AC;
    RwV3d var_B8;
    RwInt32 var_BC;
    type_3DBC78 *var_C0;
    RwReal var_C4;
    RwReal var_C8;
    RwReal var_CC;
    RwReal var_D0;
    type_14D180 *var_D4;
    type_14D180 *var_D8;
    type_14D180 *var_DC;
    type_14D180 *var_E0;
    RwInt32 var_E4;
    type_14D180 *var_E8;
    RwV3d *var_EC;

    var_4 = 0;
    var_8 = sub_45170(arg_0);
    var_4 = var_8->vf_008();
    SCRIPT_CHECK(var_4 != 0);
    var_C = var_4->vf_120();
    SCRIPT_CHECK(var_C != 0);
    var_10 = 0;
    var_14 = var_4->unk_614.sub_D4910();
    if (!var_14)
    {
        sub_44350(arg_4, &var_10);
        return;
    }
    var_18 = var_4->sub_CD550();
    RwV3dSubMacro(&var_24, var_18, var_14->sub_CD550());
    RwV3dCrossProductMacro(&var_44, var_14->sub_CD5A0(), var_4->sub_CDB90());
    RwV3dScaleMacro(&var_44, &var_44, 450.0f);
    RwMatrixSetIdentityMacro(&var_A0);
    if (RwV3dDotProductMacro(&var_44, &var_24) >= 0.0f)
    {
        RwMatrixRotate(&var_A0, &var_A0.up, -45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_AC, &var_44, &var_A0);
        RwMatrixSetIdentityMacro(&var_A0);
        RwMatrixRotate(&var_A0, &var_A0.up, 45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_B8, &var_44, &var_A0);
    }
    else
    {
        RwV3dNegateMacro(&var_44, &var_44);
        RwMatrixRotate(&var_A0, &var_A0.up, -45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_AC, &var_44, &var_A0);
        RwMatrixSetIdentityMacro(&var_A0);
        RwMatrixRotate(&var_A0, &var_A0.up, 45.0f, rwCOMBINEREPLACE);
        sub_141320(&var_B8, &var_44, &var_A0);
    }
    var_BC = 0x305A180;
    if (var_4->sub_13E9A0(&var_44, var_14, var_BC))
    {
        RwV3dAddMacro(&var_4->unk_604, &var_44, var_18);
        var_4->unk_604.y += 100.0f;
        var_C->sub_17140(&var_4->unk_604);
        var_C->unk_5B0 = var_4->unk_604;
        var_10 = 1;
    }
    else if (var_4->sub_13E9A0(&var_AC, var_14, var_BC))
    {
        RwV3dAddMacro(&var_4->unk_604, &var_AC, var_18);
        var_4->unk_604.y += 100.0f;
        var_C->sub_17140(&var_4->unk_604);
        var_C->unk_5B0 = var_4->unk_604;
        var_10 = 1;
    }
    else if (var_4->sub_13E9A0(&var_B8, var_14, var_BC))
    {
        RwV3dAddMacro(&var_4->unk_604, &var_B8, var_18);
        var_4->unk_604.y += 100.0f;
        var_C->sub_17140(&var_4->unk_604);
        var_C->unk_5B0 = var_4->unk_604;
        var_10 = 1;
    }
    if (var_10 == 0)
    {
        var_C0 = var_14->vf_010();
        if (var_C0->vf_1DC())
        {
            var_C4 = 1.0e37f;
            var_C8 = 1.0e37f;
            var_CC = 1.0e37f;
            var_D0 = 1.0e37f;
            var_D4 = 0;
            var_D8 = 0;
            var_DC = 0;
            var_E0 = var_C0->unk_263C;
            for (var_E4 = 0; var_E4 < 0xC; var_E4++)
            {
                var_E8 = &var_E0[var_E4];
                if ((var_E8->unk_00 & 3) == 3)
                {
                    var_C4 = sub_140C90(var_18, &var_E8->unk_14);
                    if (((var_E8->unk_00 >> 2) & 1) == 0 && var_C4 < var_C8)
                    {
                        var_C8 = var_C4;
                        var_D4 = var_E8;
                    }
                    if (var_C4 < var_CC)
                    {
                        var_CC = var_C4;
                        var_D8 = var_E8;
                    }
                }
                if (var_E8->unk_00 & 1)
                {
                    var_C4 = sub_140C90(var_18, &var_E8->unk_14);
                    if (var_C4 < var_D0)
                    {
                        var_D0 = var_C4;
                        var_DC = var_E8;
                    }
                }
            }
            var_EC = 0;
            if (var_D4)
            {
                var_EC = &var_D4->unk_14;
            }
            else if (var_D8)
            {
                var_EC = &var_D8->unk_14;
            }
            else if (var_DC)
            {
                var_EC = &var_DC->unk_14;
            }
            if (var_EC)
            {
                var_4->unk_604 = *var_EC;
                var_4->unk_604.y += 100.0f;
                var_C->sub_17140(&var_4->unk_604);
                var_C->unk_5B0 = var_4->unk_604;
                var_10 = 1;
            }
        }
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_4E470 @ 0x0004E470
// sp-match: sub_4E470 @ 0x0003C070
// "IsThreatenedByTank": whether the soldier's unk_614 tank (flags 0x40080 of
// its unk_2C) threatens it (vf_2D4).
void sub_4E470(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    type_3D3548 *var_10;
    type_3DBC78 *ebp_C;
    type_3DAFC8 *v8;
    RwInt32 var_4;

    v8 = 0;
    l14 = sub_45170(arg_0);
    v8 = l14->vf_008();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    var_10 = v8->unk_614.sub_D4910();
    if (var_10 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &var_4);
    } else if ((var_10->unk_2C & 0x40080) == 0) { // not an address: entity kind bits
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &var_4);
    } else {
        ebp_C = (type_3DBC78 *)var_10;
        var_4 = ebp_C->vf_2D4(v8, 0, 0);
        sub_44350(arg_4, &var_4);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_4E550 @ 0x0004E550
// sp-match: sub_4E550 @ 0x0003C1B0
// "GetDistanceFromGrenade": a soldier's distance to its unk_610 point; 0
// without one.
void sub_4E550(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_18;
    RwReal l14;
    type_3DAFC8 *var_10;
    RwV3d var_C;

    var_10 = 0;
    stk_18 = sub_45170(arg_0);
    var_10 = stk_18->vf_008();
    SCRIPT_CHECK(var_10 != 0);
    l14 = 0.0f;
    if (var_10->unk_610 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &l14);
    } else {
        RwV3dSub(&var_C, &var_10->unk_610->unk_04, var_10->sub_CD550());
        l14 = RwV3dLength(&var_C);
        sub_44350(arg_4, &l14);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_4E650 @ 0x0004E650
// sp-match: sub_4E650 @ 0x0003C2D0
// "GetDistanceFromPoint": the entity's distance to (arg 1, arg 2, arg 3).
void sub_4E650(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_20;
    type_3D3548 *var_1C;
    RwV3d var_18;
    RwV3d var_C;

    var_1C = sub_45170(arg_0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    RwV3dSub(&var_18, &var_C, var_1C->sub_CD550());
    local_20 = RwV3dLength(&var_18);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_20);
}

// match: sub_4E740 @ 0x0004E740
// sp-match: sub_4E740 @ 0x0003C3A0
// "GetPlayerDistanceFromPoint": the player's distance to (arg 1, arg 2,
// arg 3).
void sub_4E740(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_20;
    type_3D3548 *var_1C;
    RwV3d var_18;
    RwV3d var_C;

    var_1C = sub_1745A0(0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    RwV3dSub(&var_18, &var_C, var_1C->sub_CD550());
    local_20 = RwV3dLength(&var_18);
    sub_44350(arg_4, &local_20);
}

// match: sub_4E830 @ 0x0004E830
// sp-match: sub_4E830 @ 0x0003C470
// "GetDistanceFromTank": a soldier's distance to its unk_614 tank; 0
// without one.
void sub_4E830(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_1C;
    type_3D3548 *local_18;
    RwReal local_14;
    type_3DAFC8 *local_10;
    RwV3d var_C;

    local_10 = 0;
    var_1C = sub_45170(arg_0);
    local_10 = var_1C->vf_008();
    SCRIPT_CHECK(local_10 != 0);
    local_14 = 0.0f;
    local_18 = local_10->unk_614.sub_D4910();
    if (local_18 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &local_14);
    } else {
        RwV3dSub(&var_C, local_18->sub_CD550(), local_10->sub_CD550());
        local_14 = RwV3dLength(&var_C);
        sub_44350(arg_4, &local_14);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_4E930 @ 0x0004E930
// sp-match: sub_4E930 @ 0x0003C5B0
// "GetTargetPosture": 0x12 or 8 for the target's postures (vf_0AC) listed,
// else 0.
void sub_4E930(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = 0;
    if (var_4 != 0) {
        SCRIPT_CHECK(var_4->vf_120() != 0);
        varC = var_4->vf_120()->get_unk_1374();
        if (varC != 0) {
            switch (varC->vf_0AC()) {
            case 7:
            case 18:
            case 24:
            case 42:
                local_8 = 0x12;
                break;
            case 8:
            case 23:
            case 43:
            case 64:
                local_8 = 8;
                break;
            default:
                local_8 = 0;
            }
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_4EA40 @ 0x0004EA40
// sp-match: sub_4EA40 @ 0x0003C6F0
// "GetTargetType": the target's kind bits 0x600B0 of unk_2C.
void sub_4EA40(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    type_3D3548 *local_8;
    RwUInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    if (local_8 != 0) {
        SCRIPT_CHECK(local_8->vf_120() != 0);
        varC = local_8->vf_120()->get_unk_1374();
        if (varC != 0)
            var_4 = varC->unk_2C & 0x600B0; // not an address: entity kind bits
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4EAD0 @ 0x0004EAD0
// sp-match: sub_4EAD0 @ 0x0003C7C0
// "FindAStarPathToAIObj": plans a path to the entity of the object with the
// handle arg 1 (of kind 2), with the options args 2 to 9 (sub_293A0); -1
// without an AI object.
void sub_4EAD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *v38;
    RwUInt32 v34;
    RwReal v30;
    RwInt32 var_2C;
    type_3D2E7C *loc28;
    RwInt32 slot_24;
    RwInt32 v20;
    RwInt32 slot_1C;
    RwReal local_18;
    RwInt32 local_14;
    RwInt32 local_10;
    AIData *fp_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    var_4 = -1;
    lv_8 = sub_45170(arg_0);
    if (lv_8 != 0) {
        fp_C = lv_8->vf_120();
        if (fp_C != 0) {
            v34 = SCRIPT_ARG(arg_4, 1);
            loc28 = (type_3D2E7C *)sub_67620(v34);
            SCRIPT_CHECK(loc28 != 0);
            v30 = SCRIPT_ARGT<RwReal>(arg_4, 2);
            slot_24 = SCRIPT_ARG(arg_4, 3);
            local_14 = SCRIPT_ARG(arg_4, 4);
            v20 = SCRIPT_ARG(arg_4, 5);
            slot_1C = SCRIPT_ARG(arg_4, 6);
            local_10 = SCRIPT_ARG(arg_4, 7);
            var_2C = SCRIPT_ARG(arg_4, 8);
            local_18 = SCRIPT_ARGT<RwReal>(arg_4, 9);
            if (loc28 != 0 && loc28->sub_71300() != 0) {
                SCRIPT_CHECK(slot_24 >= 0 && slot_24 < 3);
                SCRIPT_CHECK(local_14 >= 0 && local_14 < 1);
                SCRIPT_CHECK(v20 >= 0 && v20 < 7);
                // The image reserves slots for four checks here, not eight:
                // the rest call the hook directly.
                sub_44220(slot_1C >= 0 && slot_1C < 3);
                sub_44220(local_10 >= 0 && local_10 < 17);
                sub_44220(var_2C >= 0 && var_2C < 17);
                sub_44220(loc28->get_unk_14() == 2);
                v38 = loc28->sub_71300();
                var_4 = fp_C->sub_293A0(v38, v30, slot_24, local_14, v20, slot_1C, local_10,
                                         var_2C, 0, 0, 1, local_18, 0);
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4EE30 @ 0x0004EE30
// sp-match: sub_4EE30 @ 0x0003C9E0
// "FindAStarPathToPathNode": plans the AI object's path unk_5BC to its node unk_5A8 (sub_29540) with the radius
// arg 1 and the options args 2 to 8; -1 without an AI object.
void sub_4EE30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal bp_2C;
    RwReal local_28;
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    RwInt32 l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    var_4 = -1;
    lv_8 = sub_45170(arg_0);
    if (lv_8 != 0) {
        local_C = lv_8->vf_120();
        if (local_C != 0) {
            local_28 = SCRIPT_ARGT<RwReal>(arg_4, 1);
            local_20 = SCRIPT_ARG(arg_4, 2);
            stk_14 = SCRIPT_ARG(arg_4, 3);
            var_1C = SCRIPT_ARG(arg_4, 4);
            var18 = SCRIPT_ARG(arg_4, 5);
            l10 = SCRIPT_ARG(arg_4, 6);
            local_24 = SCRIPT_ARG(arg_4, 7);
            bp_2C = SCRIPT_ARGT<RwReal>(arg_4, 8);
            SCRIPT_CHECK(local_20 >= 0 && local_20 < 3);
            SCRIPT_CHECK(stk_14 >= 0 && stk_14 < 1);
            SCRIPT_CHECK(var_1C >= 0 && var_1C < 7);
            SCRIPT_CHECK(var18 >= 0 && var18 < 3);
            // The image reserves slots for four checks here, not six: the
            // rest call the hook directly.
            sub_44220(l10 >= 0 && l10 < 17);
            sub_44220(local_24 >= 0 && local_24 < 17);
            var_4 = local_C->sub_29540(local_28, local_20, stk_14, var_1C, var18, l10, local_24,
                                     &local_C->unk_5BC, 0, 0, 1, bp_2C, 0);
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4F110 @ 0x0004F110
// sp-match: sub_4F110 @ 0x0003CBA0
// "FindAStarPathToPoint": plans the AI object's path unk_5BC to its point unk_5B0 (sub_29870) with the radius
// arg 1 and the options args 2 to 8; -1 without an AI object.
void sub_4F110(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal bp_2C;
    RwReal local_28;
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    RwInt32 l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    var_4 = -1;
    lv_8 = sub_45170(arg_0);
    if (lv_8 != 0) {
        local_C = lv_8->vf_120();
        if (local_C != 0) {
            local_28 = SCRIPT_ARGT<RwReal>(arg_4, 1);
            local_20 = SCRIPT_ARG(arg_4, 2);
            stk_14 = SCRIPT_ARG(arg_4, 3);
            var_1C = SCRIPT_ARG(arg_4, 4);
            var18 = SCRIPT_ARG(arg_4, 5);
            l10 = SCRIPT_ARG(arg_4, 6);
            local_24 = SCRIPT_ARG(arg_4, 7);
            bp_2C = SCRIPT_ARGT<RwReal>(arg_4, 8);
            SCRIPT_CHECK(local_20 >= 0 && local_20 < 3);
            SCRIPT_CHECK(stk_14 >= 0 && stk_14 < 1);
            SCRIPT_CHECK(var_1C >= 0 && var_1C < 7);
            SCRIPT_CHECK(var18 >= 0 && var18 < 3);
            // The image reserves slots for four checks here, not six: the
            // rest call the hook directly.
            sub_44220(l10 >= 0 && l10 < 17);
            sub_44220(local_24 >= 0 && local_24 < 17);
            var_4 = local_C->sub_29870(local_28, local_20, stk_14, var_1C, var18, l10, local_24,
                                     &local_C->unk_5BC, 0, 0, 1, bp_2C, 0);
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4F3F0 @ 0x0004F3F0
// sp-match: sub_4F3F0 @ 0x0003CD60
// "GetAIControl": the AI object's unk_51C.
void sub_4F3F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4->unk_51C);
}

// match: sub_4F440 @ 0x0004F440
// sp-match: sub_4F440 @ 0x0003CDD0
// "SetAIControl".
void sub_4F440(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_51C = varC;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F4C0 @ 0x0004F4C0
// sp-match: sub_4F4C0 @ 0x0003CE60
// "GetHitPoints": of the entity of the object with the handle arg 1.
void sub_4F4C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(v8);
    ebp_C = var_10->sub_71300();
    var_4 = ebp_C->vf_174();
    sub_44350(arg_4, &var_4);
}

// match: sub_4F530 @ 0x0004F530
// sp-match: sub_4F530 @ 0x0003CEE0
// "SetHitPoints": of the entity of the object with the handle arg 1.
void sub_4F530(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    var_10 = (type_3D2E7C *)sub_67620(v8);
    ebp_C = var_10->sub_71300();
    if (ebp_C != 0)
        ebp_C->vf_178(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_4F5D0 @ 0x0004F5D0
// sp-match: sub_4F5D0 @ 0x0003CF40
// "IncrementHitPoints": of the entity of the object with the handle arg 1.
void sub_4F5D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    var_10 = (type_3D2E7C *)sub_67620(v8);
    ebp_C = var_10->sub_71300();
    if (ebp_C != 0)
        ebp_C->vf_180(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_4F670 @ 0x0004F670
// sp-match: sub_4F670 @ 0x0003CFA0
// "GetDamageLevel".
void sub_4F670(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_184();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4F6C0 @ 0x0004F6C0
// sp-match: sub_4F6C0 @ 0x0003D040
// "GetDestructionID".
void sub_4F6C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_0DC();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_4F710 @ 0x0004F710
// sp-match: sub_4F710 @ 0x0003D0E0
// "SetDamageLevel".
void sub_4F710(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_188(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F790 @ 0x0004F790
// sp-match: sub_4F790 @ 0x0003D170
// "SetGravity".
void sub_4F790(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_18C(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F800 @ 0x0004F800
// sp-match: sub_4F800 @ 0x0003D1C0
// "SetNoFallThroughWorld".
void sub_4F800(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->unk_28_8 = local_8;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F870 @ 0x0004F870
// sp-match: sub_4F870 @ 0x0003D210
// "SetEnvCollisionNotification".
void sub_4F870(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_194(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F8E0 @ 0x0004F8E0
// sp-match: sub_4F8E0 @ 0x0003D260
// "SetWallCollisionNotification".
void sub_4F8E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_198(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F950 @ 0x0004F950
// sp-match: sub_4F950 @ 0x0003D2B0
// "SetGroundCollisionNotification".
void sub_4F950(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_19C(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4F9C0 @ 0x0004F9C0
// sp-match: sub_4F9C0 @ 0x0003D300
// "SetCollideWithFlags": ors arg 2 into the collision flags of the entity of
// the object with the handle arg 1.
void sub_4F9C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    type_3D2E7C *var_4;

    var_4 = 0;
    v8 = SCRIPT_ARG(arg_4, 1);
    if (v8 != 0)
        var_4 = (type_3D2E7C *)sub_67620(v8);
    if (var_4 != 0) {
        ebp_C = var_4->sub_71300();
        if (ebp_C != 0) {
            var_10 = SCRIPT_ARG(arg_4, 2);
            ebp_C->unk_30 = ebp_C->unk_30 | var_10;
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FA70 @ 0x0004FA70
// sp-match: sub_4FA70 @ 0x0003D360
// "ClearCollideWithFlags": clears them.
void sub_4FA70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    type_3D2E7C *var_4;

    var_4 = 0;
    v8 = SCRIPT_ARG(arg_4, 1);
    if (v8 != 0)
        var_4 = (type_3D2E7C *)sub_67620(v8);
    if (var_4 != 0) {
        ebp_C = var_4->sub_71300();
        if (ebp_C != 0) {
            var_10 = SCRIPT_ARG(arg_4, 2);
            ebp_C->unk_30 = ~var_10 & ebp_C->unk_30;
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FB20 @ 0x0004FB20
// sp-match: sub_4FB20 @ 0x0003D3D0
// "SetJiggleReactionOnNamedEntity": on (arg 1) or off, for the entity the
// object under the key arg 2 (two slots) holds.
void sub_4FB20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *l14;
    RwInt32 var_10;
    type_3DFEEC *ebp_C;
    type_3D3548 *v8;
    type_3DF8D8 *var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    v8 = 0;
    l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    var_4 = sub_198800(l14);
    SCRIPT_CHECK(var_4 != 0);
    ebp_C = (type_3DFEEC *)var_4;
    SCRIPT_CHECK(ebp_C->unk_10 != 0);
    v8 = ((type_D48D0 *)&ebp_C->unk_24_id)->sub_D4910();
    SCRIPT_CHECK(v8 != 0);
    if (var_10 != 0)
        v8->unk_1BC = 1;
    else
        v8->unk_1BC = 0;
    sub_44350(arg_4, 0);
}

// match: sub_4FC10 @ 0x0004FC10
// sp-match: sub_4FC10 @ 0x0003D4F0
// "SetJiggleReactionOnEntity": on (arg 1) or off.
void sub_4FC10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    if (local_8 != 0)
        var_4->unk_1BC = 1;
    else
        var_4->unk_1BC = 0;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FC90 @ 0x0004FC90
// sp-match: sub_4FC90 @ 0x0003D540
// "SetVelocity": (arg 1, arg 2, arg 3).
void sub_4FC90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d var_1C;
    RwReal l10;
    type_3D3548 *local_C;
    RwReal lv_8;
    RwReal var_4;

    local_C = sub_45170(arg_0);
    SCRIPT_CHECK(local_C != 0);
    lv_8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    l10 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_1C.x = lv_8;
    var_1C.y = var_4;
    var_1C.z = l10;
    local_C->sub_D04D0(&var_1C);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FD60 @ 0x0004FD60
// sp-match: sub_4FD60 @ 0x0003D5F0
// "ScaleVelocity": by arg 1.
void sub_4FD60(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d lv_14;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    lv_14 = *local_8->vf_0C8();
    RwV3dScale(&lv_14, &lv_14, var_4);
    local_8->sub_D04D0(&lv_14);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FE10 @ 0x0004FE10
// sp-match: sub_4FE10 @ 0x0003D6D0
// "GetVelocityMagnitude".
void sub_4FE10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d lv_14;
    RwReal local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    lv_14 = *var_4->vf_0C8();
    local_8 = RwV3dLength(&lv_14);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_4FE80 @ 0x0004FE80
// sp-match: sub_4FE80 @ 0x0003D790
// "SetCollision".
void sub_4FE80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_190(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FF00 @ 0x0004FF00
// sp-match: sub_4FF00 @ 0x0003D820
// "SetEnvironmentCollision".
void sub_4FF00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_1A0(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_4FF80 @ 0x0004FF80
// sp-match: sub_4FF80 @ 0x0003D8B0
// "SetEntityCollision".
void sub_4FF80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_1A8(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50000 @ 0x00050000
// sp-match: sub_50000 @ 0x0003D940
// "SetNoRender".
void sub_50000(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_1A4(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50080 @ 0x00050080
// sp-match: sub_50080 @ 0x0003D9D0
// "SetFiring".
void sub_50080(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_1B0(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50100 @ 0x00050100
// sp-match: sub_50100 @ 0x0003DA60
// "InfiniteAmmoClip": a soldier's.
void sub_50100(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAFC8 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = var_4->vf_008();
    varC->vf_248(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50170 @ 0x00050170
// sp-match: sub_50170 @ 0x0003DAB0
// "AllowFiring".
void sub_50170(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_1B4(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_501F0 @ 0x000501F0
// sp-match: sub_501F0 @ 0x0003DB40
// "GetSuppressed": a soldier's (kind 0x20); 0 for others.
void sub_501F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    SCRIPT_CHECK(local_8 != 0);
    if ((local_8->unk_2C & 0x3FFFFF0) == 0x20)
        var_4 = ((type_3DAFC8 *)local_8)->vf_254();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_50260 @ 0x00050260
// sp-match: sub_50260 @ 0x0003DBF0
// "GetAttitude": a soldier's (kind 0x20) or a type_3DDB98's (kind
// 0x200000); 0 for others.
void sub_50260(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    SCRIPT_CHECK(local_8 != 0);
    if ((local_8->unk_2C & 0x3FFFFF0) == 0x20)
        var_4 = ((type_3DAFC8 *)local_8)->vf_258();
    else if ((local_8->unk_2C & 0x3FFFFF0) == 0x200000) // not an address: entity kind bits
        var_4 = ((type_3DDB98 *)local_8)->vf_23C();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_502F0 @ 0x000502F0
// sp-match: sub_502F0 @ 0x0003DCC0
// "SetEngineAttitude": a soldier's or a type_3DDB98's.
void sub_502F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if ((var_4->unk_2C & 0x3FFFFF0) == 0x20)
        ((type_3DAFC8 *)var_4)->vf_25C(local_8);
    else if ((var_4->unk_2C & 0x3FFFFF0) == 0x200000) // not an address: entity kind bits
        ((type_3DDB98 *)var_4)->vf_240(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_503A0 @ 0x000503A0
// sp-match: sub_503A0 @ 0x0003DD70
// "SetTriggerCollision".
void sub_503A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_1B8(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50410 @ 0x00050410
// sp-match: sub_50410 @ 0x0003DDC0
// "SetTriggerProximityChecks": on (arg 1 set) or off.
void sub_50410(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *varC;
    type_67620 *local_8;
    RwInt32 var_4;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    varC = local_8->vf_024()->sub_712B0();
    SCRIPT_CHECK(varC != 0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    varC->unk_24_3 = var_4 == 0;
    sub_44350(arg_4, 0);
}

// match: sub_504C0 @ 0x000504C0
// sp-match: sub_504C0 @ 0x0003DEB0
// "IsNamedEntityInTrigger": whether the kind-0x2E object under the key
// arg 2 (two slots; flag 1) lies in the trigger volume of the entity of the
// object with the handle arg 1.
void sub_504C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 local_24;
    RwInt32 local_20;
    RwReal *var_1C;
    type_3D2E7C *var18;
    type_3DF8D8_04 *stk_14;
    type_3D3548 *l10;
    type_3DF8D8 *local_C;
    RwInt32 lv_8;
    type_3DFEEC *var_4;

    local_24 = SCRIPT_ARG(arg_4, 1);
    var18 = (type_3D2E7C *)sub_67620(local_24);
    SCRIPT_CHECK(var18 != 0);
    l10 = var18->sub_71300();
    SCRIPT_CHECK(l10 != 0);
    var_1C = 0;
    var_1C = l10->vf_0C4();
    SCRIPT_CHECK(var_1C != 0);
    stk_14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    local_C = sub_198800(stk_14);
    // The image reserves slots for five checks here, not six: this one calls
    // the hook directly.
    sub_44220(local_C != 0);
    var_4 = (type_3DFEEC *)local_C;
    SCRIPT_CHECK(var_4->vf_008() == 0x2E);
    SCRIPT_CHECK(var_4->unk_10_0);
    local_20 = var_4->unk_2C;
    lv_8 = 0;
    if (var_1C != 0 && local_20 != 0)
        lv_8 = sub_144F20((RwV3d *)var_1C, (Trigger *)local_20);
    sub_44350(arg_4, &lv_8);
}

// match: sub_50620 @ 0x00050620
// sp-match: sub_50620 @ 0x0003E0E0
// "GetNumberOfObjectsInTrigger": how many entities of list arg 1
// (dword_4B8600) hold the kind-0x2E object under the key arg 2 (two slots;
// flag 1) in their trigger volumes.
void sub_50620(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal *local_20;
    RwInt32 var_1C;
    RwInt32 var18;
    type_3DF8D8_04 *stk_14;
    type_3D3548 *l10;
    type_3DF8D8 *local_C;
    RwInt32 lv_8;
    type_3DFEEC *var_4;

    lv_8 = SCRIPT_ARG(arg_4, 1);
    stk_14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    local_C = sub_198800(stk_14);
    SCRIPT_CHECK(local_C != 0);
    var_4 = (type_3DFEEC *)local_C;
    SCRIPT_CHECK(var_4->vf_008() == 0x2E);
    SCRIPT_CHECK(var_4->unk_10_0);
    var_1C = var_4->unk_2C;
    var18 = 0;
    l10 = dword_4B8600[lv_8].unk_00;
    if (var_1C != 0) {
        while (l10 != 0) {
            local_20 = 0;
            local_20 = l10->vf_0C4();
            SCRIPT_CHECK(local_20 != 0);
            if (local_20 != 0 && sub_144F20((RwV3d *)local_20, (Trigger *)var_1C) != 0)
                var18 = var18 + 1;
            l10 = l10->unk_10;
        }
    }
    sub_44350(arg_4, &var18);
}

// match: sub_50760 @ 0x00050760
// sp-match: sub_50760 @ 0x0003E290
// "SetAllowTargetLOSLoss": the AI object's unk_52C.
void sub_50760(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_52C = varC;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_507E0 @ 0x000507E0
// sp-match: sub_507E0 @ 0x0003E320
// "VehicleInProximity": the player's test (sub_10F8D0) for the map with the
// id arg 1 (-1 for any).
void sub_507E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    type_10F710 *v8;
    type_4CFE30 *var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    var_4 = 0;
    if (var_10 != -1) {
        if (var_10 >= 0 && var_10 < 2000)
            var_4 = dword_4CFE30[var_10];
        else
            var_4 = 0;
    }
    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_00C();
    SCRIPT_CHECK(v8 != 0);
    v8->sub_10F8D0(var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_508A0 @ 0x000508A0
// match: __ehhandler$?sub_508A0@@YAXIPAUtype_44350@@@Z-8 @ 0x002FF860
// match: __ehhandler$?sub_508A0@@YAXIPAUtype_44350@@@Z @ 0x002FF868
// sp-match: sub_508A0 @ 0x0003E410
// "VehicleAttachEntity": attaches the player the handle arg 1 names (flag 4
// of its unk_2C) to the vehicle, or detaches it for no entity.
void sub_508A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_20;
    RwInt32 var_1C;
    type_3DBC78 *local_18;
    type_3D3548 *local_14;

    local_14 = sub_45170(arg_0);
    SCRIPT_CHECK(local_14 != 0);
    local_18 = local_14->vf_010();
    SCRIPT_CHECK(local_18 != 0);
    type_D48D0 local_10;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_10 = var_1C;
    local_14 = local_10.sub_D4910();
    if (local_14 == 0) {
        local_18->vf_270();
    } else if ((local_14->unk_2C >> 4) & 1) {
        local_20 = local_14->vf_00C();
        SCRIPT_CHECK(local_20 != 0);
        local_18->vf_268(local_20);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_509C0 @ 0x000509C0
// sp-match: sub_509C0 @ 0x0003E530
// "VehicleAttachEntityToMountedWeapon": as "VehicleAttachEntity", for the
// vehicle's mounted weapon (vf_26C, vf_274). Its EH handler and unwind
// funclet are folded into sub_508A0's (0x2FF860).
void sub_509C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_20;
    RwInt32 var_1C;
    type_3DBC78 *local_18;
    type_3D3548 *local_14;

    local_14 = sub_45170(arg_0);
    SCRIPT_CHECK(local_14 != 0);
    local_18 = local_14->vf_010();
    SCRIPT_CHECK(local_18 != 0);
    type_D48D0 local_10;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_10 = var_1C;
    local_14 = local_10.sub_D4910();
    if (local_14 == 0) {
        local_18->vf_274();
    } else if ((local_14->unk_2C >> 4) & 1) {
        local_20 = local_14->vf_00C();
        SCRIPT_CHECK(local_20 != 0);
        local_18->vf_26C(local_20);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50AE0 @ 0x00050AE0
// sp-match: sub_50AE0 @ 0x0003E650
// "VehicleAttachPlayerPassenger": attaches the player the handle arg 1 names
// (flag 4 of its unk_2C) as a passenger with the options args 2 to 5, or
// detaches the passenger for no entity. Its EH handler and unwind funclet are
// folded into sub_508A0's (0x2FF860).
void sub_50AE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *var_30;
    RwInt32 bp_2C;
    type_3DBC78 *local_28;
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    type_3D3548 *local_18;
    RwInt32 local_14;

    local_18 = sub_45170(arg_0);
    SCRIPT_CHECK(local_18 != 0);
    local_28 = local_18->vf_010();
    SCRIPT_CHECK(local_28 != 0);
    local_24 = SCRIPT_ARG(arg_4, 2);
    local_20 = SCRIPT_ARG(arg_4, 3);
    local_14 = SCRIPT_ARG(arg_4, 4);
    var_1C = SCRIPT_ARG(arg_4, 5);
    type_D48D0 local_10;

    bp_2C = SCRIPT_ARG(arg_4, 1);
    local_10 = bp_2C;
    local_18 = local_10.sub_D4910();
    if (local_18 == 0) {
        local_28->vf_2CC();
    } else if ((local_18->unk_2C >> 4) & 1) {
        var_30 = local_18->vf_00C();
        SCRIPT_CHECK(var_30 != 0);
        local_28->vf_2C8(var_30, local_24, local_20, local_14, var_1C);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_50CB0 @ 0x00050CB0
// sp-match: sub_50CB0 @ 0x0003E8B0
// "VehicleGetPlayerPosture": the player's unk_4D0 while in a vehicle
// (posture 5, vf_200's vf_014 set); 0 otherwise.
void sub_50CB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = 0;
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0 && var_4->unk_19D0 == 5 && var_4->vf_200() != 0
        && var_4->vf_200()->vf_014() != 0)
        local_8 = var_4->unk_4D0;
    sub_44350(arg_4, &local_8);
}

// match: sub_50D30 @ 0x00050D30
// sp-match: sub_50D30 @ 0x0003E7B0
// "VehicleGetPlayerPassenger": the id of the passenger's object, 0 without
// one.
void sub_50D30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 l14;
    type_3D2E7C *var_10;
    RwUInt32 ebp_C;
    type_3DBC78 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    v8 = var_4->vf_010();
    SCRIPT_CHECK(v8 != 0);
    ebp_C = 0;
    var_4 = v8->unk_118C.sub_D4910();
    if (var_4 != 0) {
        var_10 = var_4->vf_098();
        l14 = var_10->unk_04;
        ebp_C = l14;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &ebp_C);
}

// match: sub_50DD0 @ 0x00050DD0
// sp-match: sub_50DD0 @ 0x0003E940
// "VehicleMountedWeaponGetAttachedEntity": the id of the object of the
// entity attached to the vehicle's mounted weapon, 0 without a weapon.
void sub_50DD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 stk_18;
    type_3D2E7C *l14;
    RwUInt32 var_10;
    type_3DBC78 *ebp_C;
    type_3DC9B0 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    ebp_C = var_4->vf_010();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_2C4();
    var_10 = 0;
    if (v8 != 0) {
        var_4 = v8->unk_5C0.sub_D4910();
        l14 = var_4->vf_098();
        stk_18 = l14->unk_04;
        var_10 = stk_18;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_50E80 @ 0x00050E80
// sp-match: sub_50E80 @ 0x0003EA50
// "VehicleGetMountedWeapon": the id of the mounted weapon of the vehicle a
// soldier holds (unk_624) or of the entity's own vehicle; 0 otherwise.
void sub_50E80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_20;
    RwInt32 var_1C;
    type_3DBC78 *var18;
    type_3D3548 *stk_14;
    type_3DBC78 *l10;
    type_3D3548 *local_C;
    RwInt32 lv_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    lv_8 = 0;
    if (var_4->vf_008() != 0) {
        l10 = var_4->vf_008()->unk_624.sub_D4910()->vf_010();
        SCRIPT_CHECK(l10 != 0);
        local_C = l10->vf_2C4();
        var_1C = local_C->unk_384;
        lv_8 = var_1C;
    } else if (var_4->vf_010() != 0) {
        var18 = var_4->vf_010();
        SCRIPT_CHECK(var18 != 0);
        stk_14 = var18->vf_2C4();
        local_20 = stk_14->unk_384;
        lv_8 = local_20;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_50F80 @ 0x00050F80
// sp-match: sub_50F80 @ 0x0003EB80
// "VehicleShowMountedWeapon": shows (arg 1 set) or hides the mounted weapon
// of the vehicle a soldier holds (unk_624) or of the entity's own vehicle.
void sub_50F80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *stk_18;
    type_3D3548 *l14;
    type_3DBC78 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    v8 = SCRIPT_ARG(arg_4, 1);
    if (var_4->vf_008() != 0) {
        var_10 = var_4->vf_008()->unk_624.sub_D4910()->vf_010();
        SCRIPT_CHECK(var_10 != 0);
        ebp_C = var_10->vf_2C4();
        ebp_C->unk_28_21 = v8 == 0;
    } else if (var_4->vf_010() != 0) {
        stk_18 = var_4->vf_010();
        SCRIPT_CHECK(stk_18 != 0);
        l14 = stk_18->vf_2C4();
        l14->unk_28_21 = v8 == 0;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// sub_510C0 ("PlayerExitVehicleTransition") and sub_512E0
// ("PlayerEnterVehicleTransition") stay binary (docs/units.md).

// match: sub_510C0 @ 0x000510C0
// sp-match: sub_510C0 @ 0x0003ECB0
// "PlayerExitVehicleTransition": the player (entity 0) leaves its vehicle
// for the point (arg 1, arg 2, arg 3), in the vehicle's frame when arg 4 is
// set, in state 14 (sub_1090F0).
void sub_510C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    type_3DBC78 *var_8;
    RwFrame *var_C;
    RwMatrix *var_10;
    RwInt32 var_14;
    RwV3d var_20;
#ifndef CODFH_SP
    RwMatrix var_60;
#endif
    type_10F710 *var_64;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    var_8 = var_4->vf_010();
    SCRIPT_CHECK(var_8 != 0);
    var_C = var_8->unk_338.unk_08;
    var_10 = RwFrameGetMatrix(var_C);
    var_14 = SCRIPT_ARG(arg_4, 4);
    var_20.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_20.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_20.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    if (var_14)
    {
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules its matrix work as SP 0x3ECB0 does
        RwMatrix var_60;
#endif
        RwMatrixSetIdentityMacro(&var_60);
        var_60.pos = var_20;
        RwMatrixTransform(&var_60, var_10, rwCOMBINEPOSTCONCAT);
        var_20 = var_60.pos;
    }
    var_64 = (type_10F710 *)sub_1745A0(0);
    var_64->unk_213C = var_20;
    var_64->unk_2154 = 0;
    var_64->unk_2148 = 1.0f;
    var_64->unk_215C = 0;
    var_64->sub_1090F0(14);
    var_64->sub_10E750(0, 1);
    sub_44350(arg_4, 0);
}

// match: sub_512E0 @ 0x000512E0
// sp-match: sub_512E0 @ 0x0003EEA0
// "PlayerEnterVehicleTransition": the player (entity 0) heads for the point
// (arg 1, arg 2, arg 3) in the vehicle's frame, for arg 4 times 60, in state
// 14 (sub_1090F0), and its animation plays its weapon's animation.
void sub_512E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    type_3DBC78 *var_8;
    RwFrame *var_C;
    RwMatrix *var_10;
    RwV3d var_1C;
    RwReal var_20;
    RwMatrix var_60;
    type_10F710 *var_64;
    type_4C19C0 *var_68;
    RwInt32 var_6C;
    RwInt32 var_70;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    var_8 = var_4->vf_010();
    SCRIPT_CHECK(var_8 != 0);
#ifndef CODFH_SP
    var_C = var_8->unk_338.unk_08;
    var_10 = RwFrameGetMatrix(var_C);
#endif
    var_1C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_1C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
#ifdef CODFH_SP // shape: the vehicle's matrix after the point (SP 0x3EEA0 loads it among the arguments)
    var_C = var_8->unk_338.unk_08;
    var_10 = RwFrameGetMatrix(var_C);
#endif
    var_20 = SCRIPT_ARGT<RwReal>(arg_4, 4);
    RwMatrixSetIdentityMacro(&var_60);
    var_60.pos = var_1C;
    RwMatrixTransform(&var_60, var_10, rwCOMBINEPOSTCONCAT);
    var_1C = var_60.pos;
    var_64 = (type_10F710 *)sub_1745A0(0);
    var_64->unk_213C = var_1C;
    var_64->unk_2154 = 0;
    var_64->unk_2148 = 1.0f;
    var_64->unk_215C = 1;
    var_64->unk_2160 = 0;
    var_64->unk_2164 = var_20 * 60.0f;
    var_64->unk_2168 = *(RwV3d *)var_64->vf_0C4();
    var_64->sub_1090F0(14);
    var_68 = var_64->unk_1A48[var_64->unk_1AE4]->unk_448;
    if (sub_77B70(var_68->unk_34, (void **)(&var_70), (void **)(&var_6C)))
    {
        var_64->unk_284->sub_794C0(0);
        var_64->unk_284->sub_796A0((RtAnimAnimation *)var_70, var_68->unk_34, 0, (type_783F0 *)var_6C, 0,
                                   1.0f, 1.0f);
    }
    sub_44350(arg_4, 0);
}

// match: sub_515B0 @ 0x000515B0
// sp-match: sub_515B0 @ 0x0003F110
// "VehicleSetEngine": a vehicle's (flags 0x40080 of its unk_2C).
void sub_515B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    varC = var_4->vf_010();
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->vf_278(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51650 @ 0x00051650
// sp-match: sub_51650 @ 0x0003F1E0
// "VehicleSetMaxThrottle": a vehicle's (flags 0x40080 of its unk_2C).
void sub_51650(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
#ifdef CODFH_SP // single player reads the limit as a real (SP 0x3F1E0: fld/fstp)
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
#else
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
#endif
    local_8 = sub_45170(arg_0);
    varC = local_8->vf_010();
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
#ifdef CODFH_SP
    varC->vf_288(*(RwInt32 *)&var_4);
#else
    varC->vf_288(var_4);
#endif
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_516F0 @ 0x000516F0
// sp-match: sub_516F0 @ 0x0003F2C0
// "VehicleSetMaxSpeed": the vehicle's top speed unk_450.unk_268 from arg 1
// (x 1618.4615 x 100 / 216000).
void sub_516F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    RwReal var_4;

    v8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    SCRIPT_CHECK(v8 != 0);
    if (v8->vf_010() != 0) {
#ifdef CODFH_SP // shape: SP 0x3F2C0 keeps the division a separate step
        ebp_C = var_4 * 1618.4615f * 100.0f;
        ebp_C = ebp_C / 216000.0f;
#else
        ebp_C = var_4 * 1618.4615f * 100.0f / 216000.0f;
#endif
        var_10 = (type_3DBC78 *)v8;
        var_10->unk_450.unk_268 = ebp_C;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51790 @ 0x00051790
// sp-match: sub_51790 @ 0x0003F360
// "VehicleSetCruiseSpeed".
void sub_51790(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    if (local_8->vf_010() != 0) {
        varC = (type_3DBC78 *)local_8;
        varC->unk_450.sub_14C270(var_4);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51820 @ 0x00051820
// sp-match: sub_51820 @ 0x0003F400
// "VehicleGetHatchState": of hatch arg 1.
void sub_51820(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC048 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_014();
    SCRIPT_CHECK(var_10 != 0);
    SCRIPT_CHECK(var_10->unk_2C_18);
    var_4 = var_10->sub_15A480(v8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_518C0 @ 0x000518C0
// sp-match: sub_518C0 @ 0x0003F500
// "VehicleSetHatchState": hatch arg 1 with the options args 2 to 5.
void sub_518C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC048 *var_1C;
    type_3D3548 *var18;
#ifdef CODFH_SP // single player reads arg 4 as a real (SP 0x3F500: fld/fstp)
    RwReal stk_14;
#else
    RwInt32 stk_14;
#endif
    RwInt32 l10;
    RwInt32 local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    l10 = SCRIPT_ARG(arg_4, 1);
    local_C = SCRIPT_ARG(arg_4, 2);
    lv_8 = SCRIPT_ARG(arg_4, 3);
#ifdef CODFH_SP
    stk_14 = SCRIPT_ARGT<RwReal>(arg_4, 4);
#else
    stk_14 = SCRIPT_ARG(arg_4, 4);
#endif
    var_4 = SCRIPT_ARG(arg_4, 5);
    var18 = sub_45170(arg_0);
    var_1C = var18->vf_014();
    SCRIPT_CHECK(var_1C != 0);
    SCRIPT_CHECK(var_1C->unk_2C_18);
#ifdef CODFH_SP
    var_1C->sub_15A4A0(l10, local_C, lv_8, *(RwInt32 *)&stk_14, var_4);
#else
    var_1C->sub_15A4A0(l10, local_C, lv_8, stk_14, var_4);
#endif
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51A10 @ 0x00051A10
// sp-match: sub_51A10 @ 0x0003F620
// "VehicleSetThrottle": a vehicle's (flags 0x40080 of its unk_2C).
void sub_51A10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = sub_45170(arg_0);
    varC = local_8->vf_010();
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->vf_280(var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51AB0 @ 0x00051AB0
// sp-match: sub_51AB0 @ 0x0003F700
// "VehicleGetVelocity": the length of a vehicle's velocity.
void sub_51AB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_3DBC78 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_010();
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK((local_8->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC = RwV3dLength(&local_8->unk_450.unk_124);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &varC);
}

// match: sub_51B30 @ 0x00051B30
// sp-match: sub_51B30 @ 0x0003F7F0
// "VehicleSetBrake": and the throttle to 0.
void sub_51B30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    varC = var_4->vf_010();
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->vf_290(local_8);
    varC->vf_280(0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51BE0 @ 0x00051BE0
// sp-match: sub_51BE0 @ 0x0003F8D0
// "VehicleEnablePhysics".
void sub_51BE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    varC = var_4->vf_010();
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->unk_450.unk_104 = local_8;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51C80 @ 0x00051C80
// sp-match: sub_51C80 @ 0x0003F9A0
// "VehicleTrigger_GetMyName": the name of the object's vehicle trigger
// (kind 7).
void sub_51C80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *varC;
    type_67620 *local_8;
    type_712B0 *var_4;

    local_8 = sub_67620(arg_0);
    varC = local_8->vf_024()->sub_712B0();
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK(varC->vf_008() == 7);
    var_4 = varC;
    sub_44350(arg_4, &var_4->unk_E0);
}

// match: sub_51D00 @ 0x00051D00
// sp-match: sub_51D00 @ 0x0003FA60
// "SoldierEntity_GetMyVehiclesName": the name of the vehicle whose trigger
// (unk_34C) the entity is in: of kind 5 for flag 5 of unk_2C, of kind 0x1F
// for flag 21.
void sub_51D00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_712B0 *ebp_C;
    type_3DF8D8_04 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(((var_4->unk_2C >> 5) & 1) || ((var_4->unk_2C >> 21) & 1));
    v8 = 0;
    if ((var_4->unk_2C >> 5) & 1) {
        ebp_C = var_4->get_unk_34C();
        SCRIPT_CHECK(ebp_C != 0);
        SCRIPT_CHECK(ebp_C->vf_008() == 5);
        v8 = &ebp_C->unk_F0;
    } else if ((var_4->unk_2C >> 21) & 1) {
        var_10 = var_4->get_unk_34C();
        // These two checks reserve no slots.
        sub_44220(var_10 != 0);
        sub_44220(var_10->vf_008() == 0x1F);
        v8 = &var_10->unk_F0;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, v8);
}

// match: sub_51E20 @ 0x00051E20
// sp-match: sub_51E20 @ 0x0003FBD0
// "SoldierTrigger_GetMyVehiclesName": the name of the vehicle of the
// object's trigger (kind 5 or 0x1F).
void sub_51E20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_712B0 *ebp_C;
    type_67620 *v8;
    type_3DF8D8_04 *var_4;

    v8 = sub_67620(arg_0);
    var_4 = 0;
    if (v8->vf_024()->sub_712B0()->vf_008() == 5) {
        ebp_C = v8->vf_024()->sub_712B0();
        SCRIPT_CHECK(ebp_C != 0);
        var_4 = &ebp_C->unk_F0;
    } else if (v8->vf_024()->sub_712B0()->vf_008() == 0x1F) {
        var_10 = v8->vf_024()->sub_712B0();
        SCRIPT_CHECK(var_10 != 0);
        var_4 = &var_10->unk_F0;
    } else {
        SCRIPT_CHECK(0);
    }
    sub_44350(arg_4, var_4);
}

// match: sub_51F10 @ 0x00051F10
// sp-match: sub_51F10 @ 0x0003FD00
// "VehicleSetSteering": a vehicle's (flags 0x40080 of its unk_2C).
void sub_51F10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    varC = (type_3DBC78 *)local_8;
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->vf_28C(var_4);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_51FB0 @ 0x00051FB0
// sp-match: sub_51FB0 @ 0x0003FDD0
// "VehicleSecondaryTurn": by arg 1 at rate 1.
void sub_51FB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_3DBC78 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    varC = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = (type_3DBC78 *)var_4;
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK((local_8->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    local_8->vf_294(varC, 1.0f);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_52050 @ 0x00052050
// sp-match: sub_52050 @ 0x0003FEB0
// "VehicleSecondaryPitch": by arg 1 at rate 1.
void sub_52050(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    varC = (type_3DBC78 *)local_8;
    SCRIPT_CHECK(varC != 0);
    SCRIPT_CHECK((varC->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    varC->vf_298(var_4, 1.0f);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_520F0 @ 0x000520F0
// sp-match: sub_520F0 @ 0x0003FF90
// "VehicleFireWeapon": weapon arg 1; the vehicle's result.
void sub_520F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    v8 = SCRIPT_ARG(arg_4, 1);
    var_10 = var_4->vf_010();
    SCRIPT_CHECK(var_10 != 0);
    SCRIPT_CHECK((var_10->unk_2C & 0x3FFFFF0 & 0x40080) != 0); // not an address: entity kind bits
    ebp_C = var_10->vf_2A8(v8, 0, 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &ebp_C);
}

// match: sub_521A0 @ 0x000521A0
// sp-match: sub_521A0 @ 0x00040090
// "VehicleEnableTurretTrack": turret tracking of the kind-0x2E object under
// the key arg 1 (two slots).
void sub_521A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC048 *l14;
    type_3DFEEC *var_10;
    type_3D3548 *ebp_C;
    type_3DF8D8 *v8;
    type_3DF8D8_04 *var_4;

    ebp_C = sub_45170(arg_0);
    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    v8 = sub_198800(var_4);
    SCRIPT_CHECK(v8 != 0);
    l14 = ebp_C->vf_014();
    SCRIPT_CHECK(l14 != 0);
    var_10 = (type_3DFEEC *)v8;
    SCRIPT_CHECK(var_10->vf_008() == 0x2E);
    l14->sub_15A0F0(var_10);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_52260 @ 0x00052260
// sp-match: sub_52260 @ 0x000401B0
// "VehicleDisableTurretTrack".
void sub_52260(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DC048 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_014();
    SCRIPT_CHECK(local_8 != 0);
    local_8->sub_15A120();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_522B0 @ 0x000522B0
// sp-match: sub_522B0 @ 0x00040230
// "VehicleGetDeathTask".
void sub_522B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    varC = local_8->vf_010();
    SCRIPT_CHECK(varC != 0);
    var_4 = varC->vf_248();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_52310 @ 0x00052310
// sp-match: sub_52310 @ 0x000402E0
// "VehicleSetGimpLevel".
void sub_52310(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = var_4->vf_010();
    SCRIPT_CHECK(local_8 != 0);
    local_8->unk_450.unk_108 = SCRIPT_ARG(arg_4, 1);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_52390 @ 0x00052390
// sp-match: sub_52390 @ 0x00040370
// "SetVehicleWeaponDisabled".
void sub_52390(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    ebp_C = sub_45170(arg_0);
    var_10 = ebp_C->vf_010();
    SCRIPT_CHECK(var_10 != 0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = SCRIPT_ARG(arg_4, 2);
    var_10->vf_2A0(var_4, v8);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_52440 @ 0x00052440
// sp-match: sub_52440 @ 0x00040410
// "OrientToCoverPoint": the AI object of the object's entity (kind 2) turns
// to its cover point (sub_26A30).
void sub_52440(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_26A30();
    sub_44350(arg_4, 0);
}

// match: sub_52500 @ 0x00052500
// sp-match: sub_52500 @ 0x00040560
// "OrientToCoverPointImmediate": as "OrientToCoverPoint", at once (sub_26A50).
void sub_52500(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_26A50();
    sub_44350(arg_4, 0);
}

// match: sub_525C0 @ 0x000525C0
// sp-match: sub_525C0 @ 0x000406B0
// "GetCoverPointPeekFlags": of the AI object's cover point (sub_F8FA0), for the object's entity
// (kind 2); 0 without one.
void sub_525C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_F60() != 0);
    v8 = 0;
    if (var_4->get_unk_F60() != 0)
        v8 = sub_F8FA0(var_4->get_unk_F60());
    sub_44350(arg_4, &v8);
}

// match: sub_526D0 @ 0x000526D0
// sp-match: sub_526D0 @ 0x00040880
// "GetCoverPointType": of the AI object's cover point (sub_F8FC0), for the object's entity
// (kind 2); 0 without one.
void sub_526D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_F60() != 0);
    v8 = 0;
    if (var_4->get_unk_F60() != 0)
        v8 = sub_F8FC0(var_4->get_unk_F60());
    sub_44350(arg_4, &v8);
}

// match: sub_527E0 @ 0x000527E0
// sp-match: sub_527E0 @ 0x00040A50
// "IsConnectedCorner": whether the AI object's cover point has a connected
// corner (sub_FA650), for the object's entity (kind 2).
void sub_527E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_F8350 *l14;
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_F60() != 0);
    v8 = 0;
    if (var_4->get_unk_F60() != 0) {
        l14 = sub_FA650(var_4->get_unk_F60());
        if (l14 != 0)
            v8 = 1;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_52900 @ 0x00052900
// sp-match: sub_52900 @ 0x00040C20
// "IsConnectedCornerOccupied": flag 2 of the connected corner, -1 without one.
void sub_52900(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_F8350 *l14;
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_F60() != 0);
    v8 = 0;
    if (var_4->get_unk_F60() != 0) {
        l14 = sub_FA650(var_4->get_unk_F60());
        if (l14 != 0)
            v8 = (l14->unk_00 >> 2) & 1;
        else
            v8 = -1;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_52A30 @ 0x00052A30
// sp-match: sub_52A30 @ 0x00040E00
// "SetConnectedCornerOccupied": moves the AI object to the connected corner
// (sub_23790, sub_236F0, sub_22F70); 1 when there is one.
void sub_52A30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_F8350 *l14;
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_F60() != 0);
    v8 = 0;
    if (var_4->get_unk_F60() != 0) {
        l14 = sub_FA650(var_4->get_unk_F60());
        if (l14 != 0) {
            var_4->sub_23790();
            var_4->sub_236F0(l14);
            var_4->sub_22F70();
            v8 = 1;
        }
    }
    sub_44350(arg_4, &v8);
}

// match: sub_52B70 @ 0x00052B70
// sp-match: sub_52B70 @ 0x00040FF0
// "SetCoverPoint": the AI object of the object's entity (kind 2) takes its cover point (sub_22F70).
void sub_52B70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_22F70();
    sub_44350(arg_4, 0);
}

// match: sub_52C30 @ 0x00052C30
// sp-match: sub_52C30 @ 0x00041140
// "SetCoverPointFromName": makes the node the kind-0x2E object (flags 0x10)
// under the key arg 1 (two slots) holds the cover point of the AI object of
// the object's entity (kind 2), and its point unk_5B0; the node must be a
// cover kind (flag 1 or 6, or kinds 3 to 5, 9, 0xB to 0xE, 0x11, 0x13).
void sub_52C30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *stk_18;
    type_3DFEEC *l14;
    type_3D3548 *var_10;
    type_3DF8D8 *ebp_C;
    type_3DF8D8_04 *v8;
    AIData *var_4;

    stk_18 = sub_67620(arg_0);
    SCRIPT_CHECK(stk_18->vf_024() != 0);
    SCRIPT_CHECK(stk_18->vf_024()->get_unk_14() == 2);
    var_10 = stk_18->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_198800(v8);
    SCRIPT_CHECK(ebp_C != 0);
    // The image reserves slots for five checks here, not eight: these three
    // call the hook directly.
    sub_44220(ebp_C->vf_008() == 0x2E);
    l14 = (type_3DFEEC *)ebp_C;
    sub_44220(l14->unk_10 == 0x10);
    sub_44220(((l14->get_unk_24_node()->unk_00 >> 1) & 1)
              || ((l14->get_unk_24_node()->unk_00 >> 6) & 1)
              || l14->get_unk_24_node()->unk_04 == 3
              || l14->get_unk_24_node()->unk_04 == 4
              || l14->get_unk_24_node()->unk_04 == 5
              || l14->get_unk_24_node()->unk_04 == 9
              || l14->get_unk_24_node()->unk_04 == 0xB
              || l14->get_unk_24_node()->unk_04 == 0x13
              || l14->get_unk_24_node()->unk_04 == 0xC
              || l14->get_unk_24_node()->unk_04 == 0xE
              || l14->get_unk_24_node()->unk_04 == 0xD
              || l14->get_unk_24_node()->unk_04 == 0x11);
    var_4->sub_236F0(l14->get_unk_24_node());
    var_4->unk_5B0 = l14->get_unk_24_node()->unk_10;
    sub_44350(arg_4, 0);
}

// match: sub_52F30 @ 0x00052F30
// sp-match: sub_52F30 @ 0x00041410
// "SetArrivedAtCoverPoint": the AI object of the object's entity (kind 2) marks its cover point reached (sub_235A0).
void sub_52F30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_235A0();
    sub_44350(arg_4, 0);
}

// match: sub_52FF0 @ 0x00052FF0
// sp-match: sub_52FF0 @ 0x00041560
// "ClearCoverPoint": the AI object of the object's entity (kind 2) clears its cover point (sub_23790).
void sub_52FF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_23790();
    sub_44350(arg_4, 0);
}

// match: sub_530B0 @ 0x000530B0
// sp-match: sub_530B0 @ 0x000416B0
// "IsCoverSafeFromGrenade": whether a soldier's AI object accepts its cover
// point (sub_28200) for its unk_610 point; 0 with no unk_610.
void sub_530B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAFC8 *var_10;
    RwInt32 ebp_C;
    AIData *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    var_10 = var_4->vf_008();
    SCRIPT_CHECK(var_10 != 0);
    ebp_C = 0;
    if (var_10->unk_610 == 0) {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, &ebp_C);
    } else {
        v8 = var_10->vf_120();
        SCRIPT_CHECK(v8 != 0);
        // sub_28200 takes the point's address as its dword argument.
        ebp_C = v8->sub_28200((RwInt32)&var_10->unk_610->unk_04, v8->get_unk_F60());
        sub_44350(arg_4, &ebp_C);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
}

// match: sub_53170 @ 0x00053170
// sp-match: sub_53170 @ 0x000417E0
// "CanSeeTarget": the AI object's sight test (sub_18DF0) of its target with
// arg 1, for the object's entity (kind 2); 0 without a target.
void sub_53170(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 stk_18;
    type_3D3548 *l14;
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    AIData *v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_120();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    l14 = v8->get_unk_1374();
    if (l14 != 0) {
        stk_18 = SCRIPT_ARG(arg_4, 1);
        var_4 = v8->sub_18DF0(l14, stk_18);
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_53280 @ 0x00053280
// sp-match: sub_53280 @ 0x00041980
// "IsFacingTarget": whether the target lies ahead of the object's entity
// (kind 2), by the dot product with its facing; 0 without a target.
void sub_53280(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *local_24;
    RwV3d local_20;
    type_3D3548 *stk_14;
    type_67620 *l10;
    type_3D3548 *local_C;
    RwInt32 lv_8;
    AIData *var_4;

    l10 = sub_67620(arg_0);
    SCRIPT_CHECK(l10->vf_024() != 0);
    SCRIPT_CHECK(l10->vf_024()->get_unk_14() == 2);
    local_C = l10->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_C != 0);
    var_4 = local_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    lv_8 = 0;
    stk_14 = var_4->get_unk_1374();
    if (stk_14 != 0) {
        local_24 = local_C->sub_CD5A0();
        RwV3dSub(&local_20, stk_14->sub_CD550(), local_C->sub_CD550());
        lv_8 = RwV3dDotProduct(&local_20, local_24) >= 0.0f;
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_53420 @ 0x00053420
// sp-match: sub_53420 @ 0x00041BA0
// "SetMyDistanceFromTarget": moves the soldier of the kind-2 object arg_0
// along the line from its target to it (kept at the target's height) to
// the distance arg 1 from the target: its animation's two matrices and its
// frame are transformed by the same move, and its velocity cleared.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_53420(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwMatrix *bp_2C;
    RwV3d *local_28;
    RwMatrix *local_24;
    RwV3d *local_20;
    RwV3d *var_1C;
    type_3D3548 *var18;
    RwReal stk_14;
    type_67620 *l10;
    type_3D3548 *local_C;
    AIData *lv_8;
    type_7C8D0 *var_4;

    l10 = sub_67620(arg_0);
    SCRIPT_CHECK(l10->vf_024() != 0);
    SCRIPT_CHECK(l10->vf_024()->get_unk_14() == 2);
    local_C = l10->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_C != 0);
    lv_8 = local_C->vf_120();
    SCRIPT_CHECK(lv_8 != 0);
    var18 = lv_8->unk_1374.sub_D4910();
    var_4 = local_C->unk_284;
    stk_14 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    if (var18 != 0 && var_4 != 0) {
        local_24 = &var_4->unk_100;
        bp_2C = RwMatrixCreate();
        *bp_2C = *local_24;
        local_20 = &local_24->pos;
        local_28 = &var18->get_unk_284()->unk_100.pos;
        var_1C = &bp_2C->pos;
        local_28->y = local_20->y;
        RwV3dSubMacro(var_1C, local_20, local_28);
        RwV3dScaleMacro(var_1C, var_1C, stk_14 / (RwV3dLength((RwV3d *)var_1C)));
        RwV3dAddMacro(var_1C, local_28, var_1C);
        RwMatrixTransform(local_24, bp_2C, rwCOMBINEREPLACE);
        local_24 = &var_4->unk_140;
        RwMatrixTransform(local_24, bp_2C, rwCOMBINEREPLACE);
        zero_v3d(&local_C->unk_154);
        local_24 = &local_C->get_unk_340()->modelling;
        RwMatrixTransform(local_24, bp_2C, rwCOMBINEREPLACE);
        RwFrameUpdateObjects(local_C->get_unk_340());
        RwMatrixDestroy(bp_2C);
    }
    sub_44350(arg_4, 0);
}

// match: sub_53730 @ 0x00053730
// sp-match: sub_53730 @ 0x00041E20
// "GetUniqueNumber": a number from arg 1 to arg 2 picked by the high word of
// the object's id; arg 1 when the range is empty.
void sub_53730(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_20;
    RwInt32 var_1C;
    type_67620 *var18;
    type_3D2E7C *stk_14;
    RwInt32 l10;
    RwInt32 local_C;
    RwUInt32 lv_8;
    RwInt32 var_4;

    var18 = sub_67620(arg_0);
    l10 = SCRIPT_ARG(arg_4, 1);
    local_20 = SCRIPT_ARG(arg_4, 2);
    stk_14 = var18->vf_024();
    lv_8 = stk_14->unk_04;
    local_C = ((RwUInt16 *)&lv_8)[1];
    var_4 = l10;
    var_1C = local_20 - l10 + 1;
    if (var_1C > 1)
        var_4 = local_C % var_1C + l10;
    else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, &var_4);
}

// match: sub_53800 @ 0x00053800
// sp-match: sub_53800 @ 0x00041EF0
// "RandRange": a random number from arg 1 to arg 2.
void sub_53800(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 varC;
    RwUInt32 local_8;
    RwUInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    local_8 = RpRandom() % (varC - var_4 + 1) + var_4;
    sub_44350(arg_4, &local_8);
}

// match: sub_53890 @ 0x00053890
// sp-match: sub_53890 @ 0x00041F60
// "RandRangeFloat": a random float from arg 1 to arg 2.
void sub_53890(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_10;
    RwReal ebp_C;
    RwReal v8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10 = (RwReal)RpRandom() * (1.0f / RPRANDMAX);
    v8 = (ebp_C - var_4) * var_10 + var_4;
    sub_44350(arg_4, &v8);
}

// match: sub_53930 @ 0x00053930
// sp-match: sub_53930 @ 0x00042000
// "RegisterTimer": timer arg 3 posting message arg 2 after arg 1 seconds;
// its handle.
void sub_53930(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    type_67620 *var_10;
    RwInt32 ebp_C;
    RwReal v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    v8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    l14 = SCRIPT_ARG(arg_4, 3);
    ebp_C = sub_733D0(var_10, l14, var_4, v8 * 60.0f);
    sub_44350(arg_4, &ebp_C);
}

// match: sub_53A00 @ 0x00053A00
// sp-match: sub_53A00 @ 0x00042090
// "UnregisterTimerByMessage".
void sub_53A00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    RwInt32 var_4;

    local_8 = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    sub_734E0(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_53A60 @ 0x00053A60
// sp-match: sub_53A60 @ 0x000420E0
// "RegisterAStarCheck": replaces the AI object's A* check (unk_55C) with one
// of kind arg 1 (0 to 12) against the entity of the object with the handle
// arg 2 (of kind 2) at the distance arg 3; its handle, 0 without an AI
// object.
void sub_53A60(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 local_20;
    RwReal var_1C;
    type_3D2E7C *var18;
    type_3D3548 *stk_14;
    RwInt32 l10;
    AIData *local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    var_4 = 0;
    lv_8 = sub_45170(arg_0);
    if (lv_8 != 0) {
        local_C = lv_8->vf_120();
        if (local_C != 0) {
            if (local_C->unk_55C != 0) {
                sub_33190(local_C->unk_55C);
                local_C->unk_55C = 0;
            }
            stk_14 = 0;
            l10 = SCRIPT_ARG(arg_4, 1);
            local_20 = SCRIPT_ARG(arg_4, 2);
            var18 = (type_3D2E7C *)sub_67620(local_20);
            SCRIPT_CHECK(l10 >= 0 && l10 < 13);
            var_1C = SCRIPT_ARGT<RwReal>(arg_4, 3);
            if (var18 != 0) {
                SCRIPT_CHECK(var18->get_unk_14() == 2);
                stk_14 = var18->sub_71300();
            }
            var_4 = local_C->sub_28A60(l10, stk_14, var_1C, 0);
            if (var_4 != 0) {
                local_C->unk_55C = var_4;
                local_C->unk_560 = dword_449288;
                local_C->unk_564 = dword_449284;
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_53C10 @ 0x00053C10
// sp-match: sub_53C10 @ 0x00042230
// "UnRegisterAStarCheck": the check with the handle arg 1.
void sub_53C10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    AIData *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        local_8 = var_4->vf_120();
        if (local_8 != 0) {
            varC = SCRIPT_ARG(arg_4, 1);
            if (varC != 0)
                sub_33190(varC);
            local_8->unk_55C = 0;
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_53CA0 @ 0x00053CA0
// sp-match: sub_53CA0 @ 0x000422A0
// "IsPathBlocked": with flag 2, 23 or 25 of the AI object's unk_49C,
// whether unk_598 or unk_59C is set; 0 otherwise.
void sub_53CA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        varC = var_4->vf_120();
        if (varC != 0) {
            if (((varC->unk_49C >> 2) & 1) || ((varC->unk_49C >> 23) & 1)
                || ((varC->unk_49C >> 25) & 1))
#ifdef CODFH_SP // shape: through AIData::is_blocked, whose out-of-line copy this file emits (SP 0x32F80)
                local_8 = varC->is_blocked();
#else
                local_8 = varC->unk_598 != 0 || varC->unk_59C != 0;
#endif
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_53D50 @ 0x00053D50
// sp-match: sub_53D50 @ 0x00042340
// "IsPathBlockedWhileStrafing": with the same flags, the AI object's
// unk_5A0.
void sub_53D50(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        varC = var_4->vf_120();
        if (varC != 0) {
            if (((varC->unk_49C >> 2) & 1) || ((varC->unk_49C >> 23) & 1)
                || ((varC->unk_49C >> 25) & 1))
                local_8 = varC->get_unk_5A0();
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_53DF0 @ 0x00053DF0
// sp-match: sub_53DF0 @ 0x000423D0
// "SuggestManeuver": maneuver arg 1 to the entity's group.
void sub_53DF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3DF30 *ebp_C;
    RwInt32 v8;
    AIData *var_4;

    var_10 = sub_45170(arg_0);
    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = var_10->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    ebp_C = var_4->unk_56C;
    if (ebp_C != 0)
        ebp_C->sub_3E8F0(v8);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_53E80 @ 0x00053E80
// sp-match: sub_53E80 @ 0x00042470
// "ForceManeuver": maneuver arg 1 with arg 2 on the group with the id
// arg 3.
void sub_53E80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = SCRIPT_ARG(arg_4, 3);
    if (sub_3F0D0(var_4) != 0)
        sub_3F0D0(var_4)->sub_3EA20(local_8, varC);
    sub_44350(arg_4, 0);
}

// match: sub_53F40 @ 0x00053F40
// sp-match: sub_53F40 @ 0x000424E0
// "SetFireAndMovementPointFromName": hands the point of the object under the
// key arg 1 (two slots; kind 0x2E with its flags set, or kind 0x2D) to the
// group with the id arg 3 (sub_3EA50).
void sub_53F40(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *var_10;
    type_3DF8D8_04 *ebp_C;
    type_3DF8D8 *v8;
    RwInt32 var_4;

    var_10 = 0;
    ebp_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = SCRIPT_ARG(arg_4, 2);
    v8 = sub_198800(ebp_C);
    SCRIPT_CHECK(v8 != 0);
    if (v8 != 0 && v8->vf_008() == 0x2E) {
        type_3DFEEC *var_14 = (type_3DFEEC *)v8;
        SCRIPT_CHECK(var_14->unk_10 != 0);
        var_10 = var_14->vf_00C();
        SCRIPT_CHECK(var_10 != 0);
    } else if (v8 != 0 && v8->vf_008() == 0x2D) {
        type_3DFED8 *var_18 = (type_3DFED8 *)v8;
        var_10 = var_18->vf_00C();
        SCRIPT_CHECK(var_10 != 0);
    } else
        sub_44220(0);
    if (sub_3F0D0(var_4) != 0)
        sub_3F0D0(var_4)->sub_3EA50(var_10);
    sub_44350(arg_4, 0);
}

// match: sub_540A0 @ 0x000540A0
// sp-match: sub_540A0 @ 0x00042670
// "ClearFireAndMovementPoint": clears the point of the group with the id
// arg 1.
void sub_540A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    if (sub_3F0D0(var_4) != 0)
        sub_3F0D0(var_4)->sub_3EA50(0);
    sub_44350(arg_4, 0);
}

// match: sub_54110 @ 0x00054110
// sp-match: sub_54110 @ 0x000426C0
// "DisableFireAndMovement": sets or clears (arg 1) kind 5 of the group with
// the id arg 2.
void sub_54110(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (sub_3F0D0(var_4) != 0)
        sub_3F0D0(var_4)->sub_3EB80(local_8, 5);
    sub_44350(arg_4, 0);
}

// match: sub_541B0 @ 0x000541B0
// sp-match: sub_541B0 @ 0x00042720
// "SetFireAndMovementExclusionEnemyDistance": the range arg 1 of the group
// with the id arg 2.
void sub_541B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (sub_3F0D0(var_4) != 0)
        sub_3F0D0(var_4)->sub_3EAD0(local_8);
    sub_44350(arg_4, 0);
}

// match: sub_54250 @ 0x00054250
// sp-match: sub_54250 @ 0x00042780
// "GetStartState": the start state of the entity's trigger (flag 5), or
// nothing.
void sub_54250(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_712B0 *ebp_C;
    type_712B0 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if ((var_4->unk_2C >> 5) & 1) {
        var_10 = var_4;
        ebp_C = var_10->get_unk_34C();
        SCRIPT_CHECK(ebp_C != 0);
        v8 = ebp_C;
        {
            // A local the image reserves and never uses.
            RwInt32 var_14;
        }
        sub_44350(arg_4, &v8->unk_168);
    } else
        sub_44350(arg_4, 0);
}

// match: sub_542E0 @ 0x000542E0
// match: __ehhandler$?sub_542E0@@YAXIPAUtype_44350@@@Z-8 @ 0x002FF840
// match: __ehhandler$?sub_542E0@@YAXIPAUtype_44350@@@Z @ 0x002FF848
// sp-match: sub_542E0 @ 0x00057110
// "SetDoorPathNodeState": sets the state arg 1 on the door node (filter 5)
// nearest the entity within 500, and on its linked door nodes (flag 12):
// kinds 7 and 4 or 8 and 3 for open and closed, and flag 8 while closed.
void sub_542E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 *var_24;
    type_4C00E8 *lv_28;
    type_3D3548 *stk_90;
    type_F8350 *bp_94;
    RwInt32 stk_98;
    type_F8350 *lcl_9C;

    stk_98 = SCRIPT_ARG(arg_4, 1);
    stk_90 = sub_45170(arg_0);
    type_154C0_1048 loc8C;
    loc8C.unk_04 = *stk_90->sub_CD550();
    loc8C.unk_10 = 500.0f;
    loc8C.unk_00 = 0;
    loc8C.unk_18 = sub_F7E80(5);
    loc8C.unk_1C = 0;
    sub_F8970(&loc8C, 1, 0);
    loc8C.unk_34->unk_00_7 = stk_98;
    var_24 = 0;
    bp_94 = loc8C.unk_34;
    if (bp_94->unk_00_0)
        var_24 = bp_94->unk_2C;
    else
        var_24 = bp_94->unk_1C_links;
    type_3CE1FC var_20(var_24);
    lv_28 = &unk_4C00E8;
    while (!var_20.at_end()) {
        lcl_9C = lv_28->unk_2C[var_20.get_unk_0C()];
        if (lcl_9C->unk_00_12 && (lcl_9C->unk_04 == 7 || lcl_9C->unk_04 == 4)) {
            lcl_9C->unk_00_8 = stk_98 == 0;
            if (stk_98 != 0)
                lcl_9C->unk_04 = 7;
            else
                lcl_9C->unk_04 = 4;
        } else if (lcl_9C->unk_00_12 && (lcl_9C->unk_04 == 8 || lcl_9C->unk_04 == 3)) {
            lcl_9C->unk_00_8 = stk_98 == 0;
            if (stk_98 != 0)
                lcl_9C->unk_04 = 8;
            else
                lcl_9C->unk_04 = 3;
        }
        {
            // A local the image reserves and never uses.
            RwInt32 unused_0;
        }
        var_20.sub_31A10();
    }
    sub_44350(arg_4, 0);
}

// match: sub_545C0 @ 0x000545C0
// sp-match: sub_545C0 @ 0x00042850
// "SetAnimatedBGEntityType": the type arg 1 of the animated background
// entity.
void sub_545C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_545C0 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8->unk_2C_8);
    varC = (type_545C0 *)local_8;
    varC->unk_3D4 = var_4;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_54640 @ 0x00054640
// sp-match: sub_54640 @ 0x000428E0
// "AttachPlayerToAnimatedBGEntity": attaches the player the handle arg 1
// names (flag 4 of its unk_2C) to the entity's type_3DA6C0 with arguments 2
// to 4, or detaches it for no entity. Its EH handler and unwind funclet are
// folded into sub_508A0's (0x2FF860).
void sub_54640(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 bp_2C;
    type_10F710 *local_28;
    RwInt32 local_24;
    RwInt32 local_20;
    RwInt32 var_1C;
    type_3DA6C0 *local_18;
    type_3D3548 *local_14;

    local_14 = sub_45170(arg_0);
    SCRIPT_CHECK(local_14 != 0);
    local_18 = local_14->vf_01C();
    SCRIPT_CHECK(local_18 != 0);
    type_D48D0 local_10;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_10 = var_1C;
    local_14 = local_10.sub_D4910();
    if (local_14 == 0) {
        local_18->sub_75CB0();
    } else if ((local_14->unk_2C >> 4) & 1) {
        local_28 = local_14->vf_00C();
        SCRIPT_CHECK(local_28 != 0);
        local_24 = SCRIPT_ARG(arg_4, 2);
        bp_2C = SCRIPT_ARG(arg_4, 3);
        local_20 = SCRIPT_ARG(arg_4, 4);
        local_18->sub_75AF0(local_28, local_24, bp_2C, local_20);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_547E0 @ 0x000547E0
// sp-match: sub_547E0 @ 0x00042A20
// "AnimatedBGEntityAttachPlayerToMountedWeapon": as
// "AttachPlayerToAnimatedBGEntity", for the entity's mounted weapon (vf_238,
// vf_23C). Its EH handler and unwind funclet are folded into sub_508A0's
// (0x2FF860).
void sub_547E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_20;
    RwInt32 var_1C;
    type_545C0 *local_18;
    type_3D3548 *local_14;

    local_18 = (type_545C0 *)sub_45170(arg_0);
    SCRIPT_CHECK(local_18 != 0);
    type_D48D0 local_10;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_10 = var_1C;
    local_14 = local_10.sub_D4910();
    if (local_14 == 0) {
        local_18->vf_23C();
    } else if ((local_14->unk_2C >> 4) & 1) {
        local_20 = local_14->vf_00C();
        SCRIPT_CHECK(local_20 != 0);
        local_18->vf_238(local_20);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_548E0 @ 0x000548E0
// sp-match: sub_548E0 @ 0x00042AF0
// "AnimatedBGEntityMountedWeaponGetAttachedPlayer": the handle of the
// entity attached to the entity's mounted weapon, or nothing without one.
void sub_548E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 stk_18;
    type_3D2E7C *l14;
    type_3D3548 *var_10;
    RwUInt32 ebp_C;
    type_545C0 *v8;
    type_3DC9B0 *var_4;

    v8 = (type_545C0 *)sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_234();
    if (var_4 != 0) {
        var_10 = var_4->unk_5C0.sub_D4910();
        l14 = var_10->vf_098();
        stk_18 = l14->unk_04;
        ebp_C = stk_18;
        {
            // A local the image reserves and never uses.
            RwInt32 unused_0;
        }
        sub_44350(arg_4, &ebp_C);
    } else
        sub_44350(arg_4, 0);
}

// match: sub_54980 @ 0x00054980
// sp-match: sub_54980 @ 0x00042BA0
// "SendFlying": sends a soldier (vf_008) or a type_3DDB98 (vf_024) flying
// along (arg 1, arg 2, arg 3) with arg 4; any other entity has no wings.
void sub_54980(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal l14;
    type_3D3548 *var_10;
    RwV3d var_C;

    var_10 = sub_45170(arg_0);
    SCRIPT_CHECK(var_10 != 0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    l14 = SCRIPT_ARGT<RwReal>(arg_4, 4);
    if (var_10->vf_008() != 0)
        ((type_3DAFC8 *)var_10)->sub_13DF40(&var_C, l14);
    else if (var_10->vf_024() != 0)
        ((type_3DDB98 *)var_10)->sub_17BF90(&var_C, l14);
    else
        SCRIPT_CHECK("This entity has no wings!");
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_54AB0 @ 0x00054AB0
// sp-match: sub_54AB0 @ 0x00042CA0
// "SwapToDestroyedVersion": swaps the entity (flag 16) for its destroyed
// version.
void sub_54AB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_9BB60 *var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8->unk_2C_16);
    var_4 = (type_9BB60 *)local_8;
    var_4->sub_9BB60();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_54B00 @ 0x00054B00
// sp-match: sub_54B00 @ 0x00042D10
// "PZ_Manipulate": starts (arg 2 = 0: spawning its particle system at its
// matrix) or stops (1) the zone object of the map entry arg 1.
void sub_54B00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_4CFE30 *v8;
    RwInt32 varC;

    varC = SCRIPT_ARG(arg_4, 1);
    if (varC >= 0 && varC < 2000)
        v8 = dword_4CFE30[varC];
    else
        v8 = 0;
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (v8 != 0 && v8->unk_D8 != 0) {
        switch (var_4) {
        case 0: {
            type_17DB90 *var_10 = v8->unk_D8;
            var_10->unk_54 = 1;
            v8->unk_D8->sub_17DB90(sub_F2FF0(v8->unk_DC, (RwMatrix *)v8->unk_60, 0, 1, 0, 0));
            break;
        }
        case 1: {
#ifdef CODFH_SP // through the setter (SP 0x42D10 stores straight through edi, no copy of the zone)
            v8->unk_D8->set_running(0);
#else
            type_17DB90 *var_14 = v8->unk_D8;
            var_14->unk_54 = 0;
#endif
            v8->unk_D8->sub_17DB90(0);
            break;
        }
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_54C30 @ 0x00054C30
// sp-match: sub_54C30 @ 0x00042DB0
// "PZ_SetUserData": the user data (arg 2, arg 3) of the zone object of the
// map entry arg 1.
void sub_54C30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_4CFE30 *v8;
    RwInt32 stk_C;
    RwInt32 var_10;

    var_10 = SCRIPT_ARG(arg_4, 1);
    if (var_10 >= 0 && var_10 < 2000)
        v8 = dword_4CFE30[var_10];
    else
        v8 = 0;
    stk_C = SCRIPT_ARG(arg_4, 2);
    var_4 = SCRIPT_ARG(arg_4, 3);
    if (v8 != 0 && v8->unk_D8 != 0) {
        type_17DB90 *var_14 = v8->unk_D8;
        var_14->unk_C0 = stk_C;
        var_14->unk_C4 = var_4;
    }
    sub_44350(arg_4, 0);
}

// match: sub_54D20 @ 0x00054D20
// sp-match: sub_54D20 @ 0x00042E30
// "PG_SetParentAndAttachPoint": parents the projectile generator arg 1 to
// the entity of the object under the key arg 2 (two slots; with its flag 2)
// at the attach point arg 3, or detaches it without an object.
void sub_54D20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *var_1C;
    type_3D3548 *var18;
    RwInt32 stk_14;
    type_1227C0 *l10;
    RwInt32 local_C;
    type_3DF8D8_04 *lv_8;
    type_3DF8D8 *var_4;

    stk_14 = SCRIPT_ARG(arg_4, 1);
    l10 = sub_1227C0(stk_14);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    var_4 = 0;
    if (lv_8 != 0) {
        var_4 = sub_198800(lv_8);
        SCRIPT_CHECK(var_4 != 0);
    }
    local_C = SCRIPT_ARG(arg_4, 3);
    if (var_4 != 0) {
        var_1C = (type_3DFEEC *)var_4;
        var18 = ((type_D48D0 *)&var_1C->unk_24_id)->sub_D4910();
        if ((var_1C->unk_10 & 2) && var18 != 0)
            l10->sub_121C70(var18, local_C);
    } else
        l10->sub_121C70(0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_54E50 @ 0x00054E50
// sp-match: sub_54E50 @ 0x00042F50
// "PG_DetatchFromParent": detaches the projectile generator arg 1.
void sub_54E50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_1227C0 *var_4;
    RwInt32 local_8;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_1227C0(local_8);
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_121C70(0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_54EC0 @ 0x00054EC0
// sp-match: sub_54EC0 @ 0x00042FD0
// "PG_SetSplinePathFromName": the path of the projectile generator arg 1:
// the spline of the object under the key arg 2 (two slots; kind 0x2E with
// flags 0x80), after its default path for the key (-1, -1).
void sub_54EC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    type_3DF8D8_04 *var_10;
    type_1227C0 *ebp_C;
    type_3DFEEC *v8;
    type_3DF8D8 *var_4;

    l14 = SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_1227C0(l14);
    SCRIPT_CHECK(ebp_C != 0);
    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    var_4 = 0;
    if (var_10->unk_00 == -1 && var_10->unk_04 == -1) {
        ebp_C->unk_DC = ebp_C->get_default_path();
        ebp_C->unk_CC = 0;
    }
    var_4 = sub_198800(var_10);
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->vf_008() == 0x2E);
    v8 = (type_3DFEEC *)var_4;
    SCRIPT_CHECK(v8->unk_10 == 0x80);
    SCRIPT_CHECK(v8->unk_24 != 0);
    ebp_C->unk_DC = v8->get_unk_24();
    ebp_C->unk_CC = 0;
    sub_44350(arg_4, 0);
}

// match: sub_55020 @ 0x00055020
// sp-match: sub_55020 @ 0x000431A0
// "PG_ManipulateProjectileGenerator": on the projectile generator arg 1,
// by arg 2: 0 creates one for the object's trigger (kind 0x13) and returns
// its id, 1 stops it (and its sound), 2 starts it, 3 destroys it (and its
// sound) and returns 0.
void sub_55020(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_20;
    RwInt32 var_1C;
    type_1227C0 *var18;
    type_712B0 *stk_14;
    type_67620 *l10;
    type_3D2E7C *local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    l10 = sub_67620(arg_0);
    var_1C = SCRIPT_ARG(arg_4, 1);
    lv_8 = SCRIPT_ARG(arg_4, 2);
    var18 = sub_1227C0(var_1C);
    local_C = l10->vf_024();
    SCRIPT_CHECK(local_C != 0);
    stk_14 = local_C->sub_712B0();
    SCRIPT_CHECK(stk_14->vf_008() == 0x13);
    switch (lv_8) {
    case 0:
        local_20 = sub_1223B0(stk_14);
        var_1C = local_20;
        break;
    case 1:
        SCRIPT_CHECK(var18 != 0);
        var18->sub_121D20(0);
        if (var18->unk_10 != 0) {
            SoundEmitter_Stop((type_44C4E8 *)var18->unk_10, 0);
            sub_3C6C0(var18->unk_10);
            var18->unk_10 = 0;
        }
        break;
    case 2:
        SCRIPT_CHECK(var18 != 0);
        var18->sub_121D20(1);
        break;
    case 3:
        SCRIPT_CHECK(var18 != 0);
        sub_1225D0(var18);
        var_1C = 0;
        if (var18->unk_10 != 0) {
            SoundEmitter_Stop((type_44C4E8 *)var18->unk_10, 0);
            sub_3C6C0(var18->unk_10);
            var18->unk_10 = 0;
        }
        break;
    default:
        sub_44220(0);
    }
    var_4 = var_1C;
    sub_44350(arg_4, &var_4);
}

// match: sub_55210 @ 0x00055210
// sp-match: sub_55210 @ 0x000433B0
// "PG_TargetObjectByScript": has the projectile generator of the object's
// trigger (kind 0x13) target the entity of the object the handle arg 1
// names (with an id, not flagged 9); returns its result, or 0.
void sub_55210(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_1C;
    type_3D2E7C *var18;
    type_3D3548 *stk_14;
    RwInt32 l10;
    type_67620 *local_C;
    type_3D2E7C *lv_8;
    RwInt32 var_4;

    local_C = sub_67620(arg_0);
    l10 = SCRIPT_ARG(arg_4, 1);
    lv_8 = (type_3D2E7C *)sub_67620(l10);
    var_4 = 0;
    if (lv_8->get_unk_24() != -1 && (stk_14 = lv_8->sub_71300()) != 0 && !((stk_14->unk_28 >> 9) & 1)) {
        var18 = local_C->vf_024();
        SCRIPT_CHECK(var18 != 0);
        var_1C = var18->sub_712B0();
        SCRIPT_CHECK(var_1C->vf_008() == 0x13);
        if (var_1C->unk_224 != 0)
            var_4 = var_1C->unk_224->sub_121960(stk_14);
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_55310 @ 0x00055310
// sp-match: sub_55310 @ 0x00043490
// "PG_TargetNamedObjectByScript": as "PG_TargetObjectByScript", for the
// entity of the object under the key arg 1 (two slots; with its flag 2).
void sub_55310(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *local_20;
    type_3D2E7C *var_1C;
    type_3DFEEC *var18;
    type_3D3548 *stk_14;
    type_67620 *l10;
    type_3DF8D8_04 *local_C;
    RwInt32 lv_8;
    type_3DF8D8 *var_4;

    l10 = sub_67620(arg_0);
    local_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(local_C);
    lv_8 = 0;
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        var18 = (type_3DFEEC *)var_4;
        stk_14 = ((type_D48D0 *)&var18->unk_24_id)->sub_D4910();
        if ((var18->unk_10 & 2) && stk_14 != 0 && !((stk_14->unk_28 >> 9) & 1)) {
            var_1C = l10->vf_024();
            SCRIPT_CHECK(var_1C != 0);
            local_20 = var_1C->sub_712B0();
            SCRIPT_CHECK(local_20->vf_008() == 0x13);
            if (local_20->unk_224 != 0)
                lv_8 = local_20->unk_224->sub_121960(stk_14);
        }
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_55430 @ 0x00055430
// sp-match: sub_55430 @ 0x000435C0
// "PG_TargetPoint": has the projectile generator of the object's trigger
// (kind 0x13) target the point (arg 1, arg 2, arg 3) with arg 4; returns 1.
void sub_55430(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player reads arg 4 as a real (SP 0x435C0: fld/fstp)
    RwReal local_20;
#else
    RwInt32 local_20;
#endif
    type_712B0 *var_1C;
    type_67620 *local_18;
    type_3D2E7C *local_14;
    RwInt32 local_10;
    RwV3d var_C;

    local_18 = sub_67620(arg_0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
#ifdef CODFH_SP
    local_20 = SCRIPT_ARGT<RwReal>(arg_4, 4);
#else
    local_20 = SCRIPT_ARG(arg_4, 4);
#endif
    local_10 = 1;
    local_14 = local_18->vf_024();
    SCRIPT_CHECK(local_14 != 0);
    var_1C = local_14->sub_712B0();
    SCRIPT_CHECK(var_1C->vf_008() == 0x13);
    if (var_1C->unk_224 != 0)
#ifdef CODFH_SP
        var_1C->unk_224->sub_1218A0(&var_C, local_20);
#else
        var_1C->unk_224->sub_1218A0(&var_C, local_20);
#endif
    sub_44350(arg_4, &local_10);
}

// match: sub_55570 @ 0x00055570
// sp-match: sub_55570 @ 0x00043710
// "PG_TargetNamedPoint": has the projectile generator of the object's
// trigger (kind 0x13) target the object under the key arg 1 (two slots)
// with arg 2; returns 1.
void sub_55570(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player reads arg 2 as a real (SP 0x43710: fld/fstp)
    RwReal stk_18;
#else
    RwInt32 stk_18;
#endif
    type_712B0 *l14;
    type_67620 *var_10;
    type_3D2E7C *ebp_C;
    type_3DF8D8_04 *v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
#ifdef CODFH_SP
    stk_18 = SCRIPT_ARGT<RwReal>(arg_4, 2);
#else
    stk_18 = SCRIPT_ARG(arg_4, 2);
#endif
    var_4 = 1;
    ebp_C = var_10->vf_024();
    SCRIPT_CHECK(ebp_C != 0);
    l14 = ebp_C->sub_712B0();
    SCRIPT_CHECK(l14->vf_008() == 0x13);
    if (l14->unk_224 != 0)
#ifdef CODFH_SP
        l14->unk_224->sub_121910(v8, stk_18);
#else
        l14->unk_224->sub_121910(v8, stk_18);
#endif
    sub_44350(arg_4, &var_4);
}

// match: sub_55660 @ 0x00055660
// sp-match: sub_55660 @ 0x00043840
// "PG_EnableFiringStages": turns the firing stages of the projectile
// generator of the object's trigger (kind 0x13) on or off (arg 1).
void sub_55660(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    SCRIPT_CHECK(var_10->vf_008() == 0x13);
    if (var_10->unk_224 != 0)
        var_10->unk_224->sub_121A30(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_55720 @ 0x00055720
// sp-match: sub_55720 @ 0x00043920
// "PG_TargetDefault": returns the projectile generator of the object's
// trigger (kind 0x13) to its default target.
void sub_55720(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *varC;
    type_67620 *local_8;
    type_3D2E7C *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = local_8->vf_024();
    SCRIPT_CHECK(var_4 != 0);
    varC = var_4->sub_712B0();
    SCRIPT_CHECK(varC->vf_008() == 0x13);
    if (varC->unk_224 != 0)
        varC->unk_224->sub_121870();
    sub_44350(arg_4, 0);
}

// match: sub_557B0 @ 0x000557B0
// sp-match: sub_557B0 @ 0x000439F0
// "PG_EnableLOSCheck": turns the line-of-sight check of the projectile
// generator of the object's trigger (kind 0x13) on or off (arg 1).
void sub_557B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    SCRIPT_CHECK(var_10->vf_008() == 0x13);
    if (var_10->unk_224 != 0)
        var_10->unk_224->vf_014(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_55870 @ 0x00055870
// sp-match: sub_55870 @ 0x00043AE0
// "PG_ForcedFire": fires the projectile generator of the object's trigger
// (kind 0x13).
void sub_55870(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *varC;
    type_67620 *local_8;
    type_3D2E7C *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = local_8->vf_024();
    SCRIPT_CHECK(var_4 != 0);
    varC = var_4->sub_712B0();
    SCRIPT_CHECK(varC->vf_008() == 0x13);
    if (varC->unk_224 != 0)
        varC->unk_224->sub_120150();
    sub_44350(arg_4, 0);
}

// match: sub_55900 @ 0x00055900
// sp-match: sub_55900 @ 0x00043BB0
// "PlaySound": not supported; it only fails its check.
void sub_55900(RwUInt32 arg_0, type_44350 *arg_4)
{
    SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_55930 @ 0x00055930
// sp-match: sub_55930 @ 0x00043C00
// "LockPlayerMovement": locks or unlocks (arg 2) the movement of player
// arg 1.
void sub_55930(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_10F710 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    local_8 = (type_10F710 *)sub_1745A0(var_4);
    SCRIPT_CHECK(local_8 != 0);
    local_8->sub_108FF0(varC);
    sub_44350(arg_4, 0);
}

// match: sub_559D0 @ 0x000559D0
// sp-match: sub_559D0 @ 0x00043C90
// "SetPlayerState": the state arg 2 of player arg 1.
void sub_559D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_10F710 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    local_8 = (type_10F710 *)sub_1745A0(var_4);
    SCRIPT_CHECK(local_8 != 0);
    local_8->sub_1090F0(varC);
    sub_44350(arg_4, 0);
}

// match: sub_55A70 @ 0x00055A70
// sp-match: sub_55A70 @ 0x00043D20
// "ToggleCCESSPoolCreation": turns pool creation on or off (arg 1) for the
// object's trigger.
void sub_55A70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    SCRIPT_CHECK(var_10 != 0);
    if (var_4 != 0)
        sub_8B180(var_10);
    else
        sub_8B250(var_10);
    sub_44350(arg_4, 0);
}

// match: sub_55B20 @ 0x00055B20
// sp-match: sub_55B20 @ 0x00043E00
// "SetCCESSPoolManager": makes the object's trigger (kind 0x19) the pool
// manager with arg 1.
void sub_55B20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    SCRIPT_CHECK(var_10->vf_008() == 0x19);
    sub_8B770(var_10, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_55BD0 @ 0x00055BD0
// sp-match: sub_55BD0 @ 0x00043EE0
// "SetCCESSPoolManagerState": the pool manager's state arg 1.
void sub_55BD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_4B2178 = var_4;
    sub_44350(arg_4, 0);
}

// match: sub_55C20 @ 0x00055C20
// sp-match: sub_55C20 @ 0x00043F10
// "ChangeCCESSPoolSize": the size arg 3 of pool arg 1 (below 5) for arg 2
// (below 2).
void sub_55C20(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    varC = SCRIPT_ARG(arg_4, 2);
    var_4 = SCRIPT_ARG(arg_4, 3);
    SCRIPT_CHECK(local_8 < 5 && local_8 >= 0);
    SCRIPT_CHECK(varC < 2 && varC >= 0);
    sub_8B810(local_8, varC, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_55D10 @ 0x00055D10
// sp-match: sub_55D10 @ 0x00043FF0
// "SetNumSpawnableEntities": the object's trigger may spawn (arg 1, arg 2)
// entities.
void sub_55D10(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    l14 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    var_10->vf_010(l14, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_55DD0 @ 0x00055DD0
// sp-match: sub_55DD0 @ 0x00044090
// "SetDeadFlag": the entity's dead flag arg 1.
void sub_55DD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_D29C0(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_55E40 @ 0x00055E40
// sp-match: sub_55E40 @ 0x00044120
// "SetCollisionNotifyFlag": the entity's collision notification arg 1
// (vf_194).
void sub_55E40(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_194(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_55EC0 @ 0x00055EC0
// sp-match: sub_55EC0 @ 0x000441B0
// "DropPickup": does nothing, not even pop its arguments; it keeps a frame
// of twelve locals it never uses.
void sub_55EC0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player drops the entity's pickup and pops the arguments (SP 0x441B0)
    type_3D3548 *entity;

    entity = sub_45170(arg_0);
    SCRIPT_CHECK(entity != 0);
    entity->vf_1CC(1);
    sub_44350(arg_4, 0);
#else
    RwInt32 unused_B;
    RwInt32 unused_A;
    RwInt32 unused_9;
    RwInt32 unused_8;
    RwInt32 unused_7;
    RwInt32 unused_6;
    RwInt32 unused_5;
    RwInt32 unused_4;
    RwInt32 unused_3;
    RwInt32 unused_2;
    RwInt32 unused_1;
    RwInt32 unused_0;
#endif
}

// match: sub_55ED0 @ 0x00055ED0
// sp-match: sub_55ED0 @ 0x00044230
// "Custom_GetStartMessage": the start message of the object's custom
// trigger (kind 0x0B).
void sub_55ED0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *l14;
    type_67620 *var_10;
    type_3D2E7C *ebp_C;
    type_55ED0 *v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    ebp_C = var_10->vf_024();
    SCRIPT_CHECK(ebp_C != 0);
    l14 = ebp_C->sub_712B0();
    SCRIPT_CHECK(l14->vf_008() == 0xB);
    v8 = (type_55ED0 *)l14;
    var_4 = v8->unk_104->unk_14[0];
    sub_44350(arg_4, &var_4);
}

// match: sub_55F60 @ 0x00055F60
// sp-match: sub_55F60 @ 0x00044320
// "Custom_GetSceneID": the id of scene arg 1 (from 1) of the object's
// custom trigger (kind 0x0B).
void sub_55F60(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *stk_18;
    type_67620 *l14;
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    type_55ED0 *var_4;

    l14 = sub_67620(arg_0);
    var_10 = l14->vf_024();
    SCRIPT_CHECK(var_10 != 0);
    stk_18 = var_10->sub_712B0();
    SCRIPT_CHECK(stk_18->vf_008() == 0xB);
    var_4 = (type_55ED0 *)stk_18;
    v8 = SCRIPT_ARG(arg_4, 1) - 1;
    ebp_C = var_4->unk_10C[v8].unk_02;
    sub_44350(arg_4, &ebp_C);
}

// match: sub_56020 @ 0x00056020
// sp-match: sub_56020 @ 0x00044420
// "Custom_SendMessages": sends the messages of the object's custom trigger
// (kind 0x0B), each with its data, from the trigger.
void sub_56020(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 stk_18;
    RwInt32 l14;
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    type_55ED0 *var_4;

    ebp_C = sub_67620(arg_0);
    v8 = ebp_C->vf_024();
    SCRIPT_CHECK(v8 != 0);
    var_10 = v8->sub_712B0();
    SCRIPT_CHECK(var_10->vf_008() == 0xB);
    var_4 = (type_55ED0 *)var_10;
    for (l14 = 0; l14 < 5 && var_4->unk_108->unk_14[l14] != 0xFFFF; l14++) {
#ifdef CODFH_SP // shape: SP 0x44420 reads unk_108 once per message
        RwInt32 data = var_4->unk_108->unk_00[l14];

        sub_6B680(var_4->unk_108->unk_14[l14], 0, (type_42E00_10 *)((RwInt32)var_4), 0, &data, 1, 1, 0);
#else
        stk_18 = var_4->unk_108->unk_00[l14];
        sub_6B680(var_4->unk_108->unk_14[l14], 0, (type_42E00_10 *)((RwInt32)var_4), 0, &stk_18, 1, 1, 0);
#endif
    }
    sub_44350(arg_4, 0);
}

// match: sub_56100 @ 0x00056100
// sp-match: sub_56100 @ 0x00044530
// "Custom_SetObject": the entity's custom object arg 1 (from 1).
void sub_56100(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 1) - 1;
    local_8->sub_9B430(var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_56170 @ 0x00056170
// sp-match: sub_56170 @ 0x000445C0
// "Custom_SetAnimatedObject": the entity's animated object arg 1 (from 1).
void sub_56170(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 1) - 1;
    local_8->sub_9B2C0(var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_561E0 @ 0x000561E0
// sp-match: sub_561E0 @ 0x00044650
// "GetAttachPointXFromNamedEntity": the x of the tag arg 2 in the named
// object's entity's clump.
void sub_561E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.pos.x;
                var_1C.y = var_70.pos.y;
                var_1C.z = var_70.pos.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.x);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_56350 @ 0x00056350
// sp-match: sub_56350 @ 0x00044810
// "GetAttachPointYFromNamedEntity": the y of the tag arg 2 in the named
// object's entity's clump.
void sub_56350(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.pos.x;
                var_1C.y = var_70.pos.y;
                var_1C.z = var_70.pos.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.y);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_564C0 @ 0x000564C0
// sp-match: sub_564C0 @ 0x000449D0
// "GetAttachPointZFromNamedEntity": the z of the tag arg 2 in the named
// object's entity's clump.
void sub_564C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.pos.x;
                var_1C.y = var_70.pos.y;
                var_1C.z = var_70.pos.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.z);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_56630 @ 0x00056630
// sp-match: sub_56630 @ 0x00044B90
// "GetAttachPointOrientationXFromNamedEntity": the facing x of the tag arg 2 in the named
// object's entity's clump.
void sub_56630(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.at.x;
                var_1C.y = var_70.at.y;
                var_1C.z = var_70.at.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.x);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_567A0 @ 0x000567A0
// sp-match: sub_567A0 @ 0x00044D50
// "GetAttachPointOrientationYFromNamedEntity": the facing y of the tag arg 2 in the named
// object's entity's clump.
void sub_567A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.at.x;
                var_1C.y = var_70.at.y;
                var_1C.z = var_70.at.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.y);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_56910 @ 0x00056910
// sp-match: sub_56910 @ 0x00044F10
// "GetAttachPointOrientationZFromNamedEntity": the facing z of the tag arg 2 in the named
// object's entity's clump.
void sub_56910(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;
    type_3DF8D8 *var_8;
    type_3DFEEC *var_C;
    type_3D3548 *var_10;
    RwV3d var_1C;
    RwInt32 var_20;
    RpClump *var_24;
    RwMatrix var_70;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_8 = sub_198800(var_4);
    SCRIPT_CHECK(var_8 != 0);
    if (var_8)
    {
        var_C = (type_3DFEEC *)var_8;
        var_10 = ((type_D48D0 *)&var_C->unk_24_id)->sub_D4910();
        if ((var_C->unk_10 & 2) && var_10)
        {
            var_1C.x = 0.0f;
            var_1C.y = 0.0f;
            var_1C.z = 0.0f;
            var_20 = SCRIPT_ARG(arg_4, 2);
            var_24 = var_10->unk_25C.unk_08;
            if (var_24)
            {
                sub_EC2D0(var_24, (RwInt32)&var_70, var_20, 0, 1);
                var_1C.x = var_70.at.x;
                var_1C.y = var_70.at.y;
                var_1C.z = var_70.at.z;
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            sub_44350(arg_4, &var_1C.z);
        }
        else
        {
            SCRIPT_CHECK(0);
            sub_44350(arg_4, 0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_56A80 @ 0x00056A80
// sp-match: sub_56A80 @ 0x000450D0
// "SetCrewAttachPosition": the entity's crew attach position arg 1
// (unk_354).
void sub_56A80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8->unk_354 = var_4;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_56AF0 @ 0x00056AF0
// sp-match: sub_56AF0 @ 0x00045150
// "GetEntityFromName": the handle of the entity (flag 2) or trigger (flag
// 1) of the kind-0x2E object under the key arg 1 (two slots), or 0.
void sub_56AF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 local_20;
    type_712B0 *var_1C;
    type_3D3548 *var18;
    type_3D2E7C *stk_14;
    type_3DFEEC *l10;
    type_3DF8D8 *local_C;
    RwUInt32 lv_8;
    type_3DF8D8_04 *var_4;

    lv_8 = 0;
    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_C = sub_198800(var_4);
    SCRIPT_CHECK(local_C != 0);
    l10 = (type_3DFEEC *)local_C;
    SCRIPT_CHECK(l10->vf_008() == 0x2E);
    SCRIPT_CHECK((l10->unk_10 & 2) || (l10->unk_10 & 1));
    stk_14 = 0;
    if (l10->unk_10 & 2) {
        var18 = ((type_D48D0 *)&l10->unk_24_id)->sub_D4910();
        if (var18 != 0)
            stk_14 = var18->vf_098();
    } else {
        var_1C = l10->unk_2C_trigger;
        if (var_1C != 0)
            stk_14 = var_1C->sub_BDF50();
    }
    if (stk_14 != 0) {
        local_20 = stk_14->unk_04;
        lv_8 = local_20;
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_56C10 @ 0x00056C10
// sp-match: sub_56C10 @ 0x000452B0
// "IsNameValid": whether the key arg 1 (two slots) is (-1, -1), names a
// kind-0x2D object, or names a kind-0x2E object holding its entity (flag
// 2), trigger (1), spline (0x10 or 0x80).
void sub_56C10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *stk_18;
    type_3D3548 *l14;
    type_3DFEEC *var_10;
    type_3DF8D8_04 *ebp_C;
    type_3DF8D8 *v8;
    RwInt32 var_4;

    ebp_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    v8 = sub_198800(ebp_C);
    var_4 = 0;
    if (ebp_C->unk_00 == -1 && ebp_C->unk_04 == -1)
        var_4 = 1;
    else if (v8 != 0 && v8->vf_008() == 0x2D)
        var_4 = 1;
    else if (v8 != 0 && v8->vf_008() == 0x2E) {
        var_10 = (type_3DFEEC *)v8;
        SCRIPT_CHECK(var_10->vf_008() == 0x2E || v8->vf_008() == 0x2D);
        SCRIPT_CHECK(var_10->unk_10 != 0);
        if (var_10->unk_10 & 2) {
            l14 = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
            if (l14 != 0)
                var_4 = 1;
        } else if (var_10->unk_10 & 1) {
            stk_18 = var_10->unk_2C_trigger;
            if (stk_18 != 0)
                var_4 = 1;
        } else if (var_10->unk_10 & 0x10) {
            if (var_10->get_unk_24() != 0)
                var_4 = 1;
        } else if ((var_10->unk_10 & 0x80) && var_10->unk_24 != 0)
            var_4 = 1;
        SCRIPT_CHECK(var_4 != 0);
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, &var_4);
}

// match: sub_56DC0 @ 0x00056DC0
// sp-match: sub_56DC0 @ 0x00045400
// "GetPositionXFromName": the x of the point of the object under the key
// arg 1 (two slots; kind 0x2E with its flags set, or kind 0x2D), or 0.
void sub_56DC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *varC;
    type_3DF8D8_04 *local_8;
    type_3DF8D8 *var_4;

    varC = 0;
    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = sub_198800(local_8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        varC = var_10->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        varC = var_14->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else
        sub_44220(0);
    if (varC != 0)
        sub_44350(arg_4, &varC->x);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_56F00 @ 0x00056F00
// sp-match: sub_56F00 @ 0x000455A0
// "GetPositionYFromName": the y of the point of the object under the key
// arg 1 (two slots; kind 0x2E with its flags set, or kind 0x2D), or 0.
void sub_56F00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *varC;
    type_3DF8D8_04 *local_8;
    type_3DF8D8 *var_4;

    varC = 0;
    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = sub_198800(local_8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        varC = var_10->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        varC = var_14->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else
        sub_44220(0);
    if (varC != 0)
        sub_44350(arg_4, &varC->y);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_57040 @ 0x00057040
// sp-match: sub_57040 @ 0x00045740
// "GetPositionZFromName": the z of the point of the object under the key
// arg 1 (two slots; kind 0x2E with its flags set, or kind 0x2D), or 0.
void sub_57040(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *varC;
    type_3DF8D8_04 *local_8;
    type_3DF8D8 *var_4;

    varC = 0;
    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = sub_198800(local_8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        varC = var_10->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        varC = var_14->vf_00C();
        SCRIPT_CHECK(varC != 0);
    } else
        sub_44220(0);
    if (varC != 0)
        sub_44350(arg_4, &varC->z);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_57180 @ 0x00057180
// sp-match: sub_57180 @ 0x000458E0
// "SetupGotoPoint": the goto point (arg 1, arg 2, arg 3) of the object's
// entity: its AI object's target point with the arrival distance arg 4, a
// type_3DDB98's (sub_17BF10) or a type_3DE0E0's (unk_644).
void sub_57180(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *bp_2C;
    type_67620 *local_28;
    type_3D2E7C *local_24;
    RwReal local_20;
    RwV3d var_1C;
    RwReal l10;
    RwReal local_C;
    type_3D3548 *lv_8;
    RwReal var_4;

    local_28 = sub_67620(arg_0);
    local_20 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    l10 = SCRIPT_ARGT<RwReal>(arg_4, 4);
    local_24 = local_28->vf_024();
    SCRIPT_CHECK(local_24 != 0);
    var_1C.x = local_20;
    var_1C.y = local_C;
    var_1C.z = var_4;
    lv_8 = local_24->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    bp_2C = lv_8->vf_120();
    if (bp_2C != 0) {
        bp_2C->unk_5B0 = var_1C;
        bp_2C->unk_78 = l10;
    } else if (lv_8->vf_024() != 0)
        ((type_3DDB98 *)lv_8)->sub_17BF10(&var_1C);
    else if (lv_8->vf_02C() != 0)
        ((type_3DE0E0 *)lv_8)->unk_644 = var_1C;
    sub_44350(arg_4, 0);
}

// match: sub_57320 @ 0x00057320
// sp-match: sub_57320 @ 0x00045A60
// "GetOrientationXFromName": the x of the direction (vf_010) of the object
// under the key arg 1 (two slots; kind 0x2E with its flags set, or kind
// 0x2D), or 0.
void sub_57320(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *varC;
    RwV3d *local_8;
    type_3DF8D8 *var_4;

    local_8 = 0;
    varC = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    var_4 = sub_198800(varC);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        local_8 = var_10->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        local_8 = var_14->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else
        sub_44220(0);
    if (local_8 != 0)
        sub_44350(arg_4, &local_8->x);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_57460 @ 0x00057460
// sp-match: sub_57460 @ 0x00045C00
// "GetOrientationYFromName": the y of the direction (vf_010) of the object
// under the key arg 1 (two slots; kind 0x2E with its flags set, or kind
// 0x2D), or 0.
void sub_57460(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *varC;
    RwV3d *local_8;
    type_3DF8D8 *var_4;

    local_8 = 0;
    varC = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    var_4 = sub_198800(varC);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        local_8 = var_10->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        local_8 = var_14->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else
        sub_44220(0);
    if (local_8 != 0)
        sub_44350(arg_4, &local_8->y);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_575A0 @ 0x000575A0
// sp-match: sub_575A0 @ 0x00045DA0
// "GetOrientationZFromName": the z of the direction (vf_010) of the object
// under the key arg 1 (two slots; kind 0x2E with its flags set, or kind
// 0x2D), or 0.
void sub_575A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *varC;
    RwV3d *local_8;
    type_3DF8D8 *var_4;

    local_8 = 0;
    varC = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    var_4 = sub_198800(varC);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0 && var_4->vf_008() == 0x2E) {
        type_3DFEEC *var_10 = (type_3DFEEC *)var_4;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        local_8 = var_10->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else if (var_4 != 0 && var_4->vf_008() == 0x2D) {
        type_3DFED8 *var_14 = (type_3DFED8 *)var_4;
        local_8 = var_14->vf_010();
        SCRIPT_CHECK(local_8 != 0);
    } else
        sub_44220(0);
    if (local_8 != 0)
        sub_44350(arg_4, &local_8->z);
    else {
        sub_44220(0);
        RwReal var_18 = 0.0f;
        sub_44350(arg_4, &var_18);
    }
}

// match: sub_576E0 @ 0x000576E0
// sp-match: sub_576E0 @ 0x00045F40
// "GetOrientationXFromAIObj": the x of the direction (sub_CD5A0) of the
// entity of the object the handle arg 1 names, or 0.
void sub_576E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    RwV3d *v8;
    type_3D3548 *var_4;

    v8 = 0;
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->sub_71300();
    SCRIPT_CHECK(var_4 != 0);
    v8 = var_4->sub_CD5A0();
    if (v8 != 0)
        sub_44350(arg_4, &v8->x);
    else {
        SCRIPT_CHECK(0);
        RwReal var_14 = 0.0f;
        sub_44350(arg_4, &var_14);
    }
}

// match: sub_577A0 @ 0x000577A0
// sp-match: sub_577A0 @ 0x00046050
// "GetOrientationYFromAIObj": the y of the direction (sub_CD5A0) of the
// entity of the object the handle arg 1 names, or 0.
void sub_577A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    RwV3d *v8;
    type_3D3548 *var_4;

    v8 = 0;
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->sub_71300();
    SCRIPT_CHECK(var_4 != 0);
    v8 = var_4->sub_CD5A0();
    if (v8 != 0)
        sub_44350(arg_4, &v8->y);
    else {
        SCRIPT_CHECK(0);
        RwReal var_14 = 0.0f;
        sub_44350(arg_4, &var_14);
    }
}

// match: sub_57860 @ 0x00057860
// sp-match: sub_57860 @ 0x00046160
// "GetOrientationZFromAIObj": the z of the direction (sub_CD5A0) of the
// entity of the object the handle arg 1 names, or 0.
void sub_57860(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    RwV3d *v8;
    type_3D3548 *var_4;

    v8 = 0;
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_10 != 0);
    var_4 = var_10->sub_71300();
    SCRIPT_CHECK(var_4 != 0);
    v8 = var_4->sub_CD5A0();
    if (v8 != 0)
        sub_44350(arg_4, &v8->z);
    else {
        SCRIPT_CHECK(0);
        RwReal var_14 = 0.0f;
        sub_44350(arg_4, &var_14);
    }
}

// match: sub_57920 @ 0x00057920
// sp-match: sub_57920 @ 0x00046270
// "SetupMatchOrientation": the direction (arg 1, arg 2, arg 3) the AI
// object of the object's entity turns to (unk_484).
void sub_57920(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_28;
    AIData *local_24;
    RwReal local_20;
    RwV3d var_1C;
    type_67620 *l10;
    type_3D2E7C *local_C;
    type_3D3548 *lv_8;
    RwReal var_4;

    l10 = sub_67620(arg_0);
    local_20 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_28 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    local_C = l10->vf_024();
    SCRIPT_CHECK(local_C != 0);
    var_1C.x = local_20;
    var_1C.y = var_4;
    var_1C.z = local_28;
    lv_8 = local_C->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    local_24 = lv_8->vf_120();
    SCRIPT_CHECK(local_24 != 0);
    if (local_24 != 0)
        local_24->unk_484 = var_1C;
    sub_44350(arg_4, 0);
}

// match: sub_57A50 @ 0x00057A50
// sp-match: sub_57A50 @ 0x000463E0
// "SetMyPosition": moves the object's entity (kind 2) to (arg 1, arg 2,
// arg 3) (vf_0C0).
void sub_57A50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    type_67620 *local_8;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    if (var_4 != 0) {
        RwV3d var_14;

        var_14.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
        var_14.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
        var_14.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
        var_4->vf_0C0(&var_14);
    }
    sub_44350(arg_4, 0);
}

// match: sub_57B70 @ 0x00057B70
// sp-match: sub_57B70 @ 0x000464F0
// "TeleportToNamedObject": moves the object's entity (kind 2) to the
// matrix of the entity or trigger of the object under the key arg 1 (two
// slots), facing its at vector.
void sub_57B70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwFrame *local_24;
    type_712B0 *local_20;
    type_67620 *var_1C;
    type_3D3548 *var18;
    type_3DFEEC *stk_14;
    type_3D3548 *l10;
    RwMatrix *local_C;
    type_3DF8D8_04 *lv_8;
    type_3DF8D8 *var_4;

    lv_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(lv_8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        local_24 = 0;
        local_C = 0;
        stk_14 = (type_3DFEEC *)var_4;
        l10 = ((type_D48D0 *)&stk_14->unk_24_id)->sub_D4910();
        local_20 = stk_14->unk_2C_trigger;
        if (l10 != 0) {
            local_24 = l10->get_unk_340();
            local_C = RwFrameGetLTM(local_24);
        } else {
            SCRIPT_CHECK(local_20 != 0);
            local_C = (RwMatrix *)local_20->unk_60;
        }
        var_1C = sub_67620(arg_0);
        SCRIPT_CHECK(var_1C->vf_024() != 0);
        SCRIPT_CHECK(var_1C->vf_024()->get_unk_14() == 2);
        var18 = var_1C->vf_024()->get_unk_10();
        if (local_C != 0 && var18 != 0) {
            var18->vf_0C0(&local_C->pos);
            var18->vf_0D8(&local_C->at);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_57CF0 @ 0x00057CF0
// sp-match: sub_57CF0 @ 0x00046680
// "TeleportNamedObjectToNamedPoint": moves the entity of the object under
// the key arg 1 to the point of the object under the key arg 2 (kind 0x2E:
// its entity's volume or its trigger's matrix; kind 0x2D: its matrix),
// facing the entity's or trigger's at vector.
void sub_57CF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFED8 *v38;
    type_712B0 *v34;
    type_3D3548 *v30;
    RwFrame *var_2C;
    type_3DFEEC *loc28;
    type_3D3548 *slot_24;
    RwMatrix *v20;
    RwV3d slot_1C;
    type_3DF8D8_04 *local_10;
    type_3DF8D8 *fp_C;
    type_3DF8D8_04 *lv_8;
    type_3DF8D8 *var_4;

    lv_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    var_4 = sub_198800(lv_8);
    fp_C = sub_198800(local_10);
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(fp_C != 0);
    if (var_4 != 0 && fp_C != 0) {
        var_2C = 0;
        v20 = 0;
        loc28 = (type_3DFEEC *)var_4;
        slot_24 = ((type_D48D0 *)&loc28->unk_24_id)->sub_D4910();
        if (fp_C->vf_008() == 0x2E) {
            loc28 = (type_3DFEEC *)fp_C;
            v30 = ((type_D48D0 *)&loc28->unk_24_id)->sub_D4910();
            if (v30 != 0) {
                slot_1C = *(RwV3d *)v30->vf_0C4();
                var_2C = v30->get_unk_340();
                v20 = RwFrameGetLTM(var_2C);
            } else {
                v34 = loc28->unk_2C_trigger;
                SCRIPT_CHECK(v34 != 0);
                slot_1C = ((RwMatrix *)v34->unk_60)->pos;
                v20 = (RwMatrix *)v34->unk_60;
            }
        } else if (fp_C->vf_008() == 0x2D) {
            v38 = (type_3DFED8 *)fp_C;
            slot_1C = ((RwMatrix *)v38->unk_10)->pos;
        }
        if (slot_24 != 0) {
            slot_24->vf_0C0(&slot_1C);
            if (v20 != 0)
                slot_24->vf_0D8(&v20->at);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_57EE0 @ 0x00057EE0
// sp-match: sub_57EE0 @ 0x00046840
// "SetMyOrientation": moves the object's entity (kind 2) by (arg 1, arg 2,
// arg 3) from its position (vf_0D0).
void sub_57EE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    type_67620 *local_8;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    if (var_4 != 0) {
        RwV3d var_14;
        RwV3d local_20;

        var_14.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
        var_14.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
        var_14.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
        local_20 = *var_4->sub_CD550();
        RwV3dAdd(&local_20, &local_20, &var_14);
        var_4->vf_0D0(&local_20);
    }
    sub_44350(arg_4, 0);
}

// match: sub_58030 @ 0x00058030
// sp-match: sub_58030 @ 0x00046990
// "RideVehicle": the object's entity (kind 2; a soldier or a type_3DDB98)
// rides the vehicle entity of the object under the key arg 1 (two slots),
// which learns of it (vf_27C); its AI object notes the ride (unk_4E0).
void sub_58030(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *local_20;
    type_3D3548 *var_1C;
    type_3DBC78 *var18;
    type_67620 *stk_14;
    AIData *l10;
    type_3D3548 *local_C;
    type_3DF8D8_04 *lv_8;
    type_3DF8D8 *var_4;

    stk_14 = sub_67620(arg_0);
    SCRIPT_CHECK(stk_14->vf_024() != 0);
    SCRIPT_CHECK(stk_14->vf_024()->get_unk_14() == 2);
    local_C = stk_14->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_C != 0);
    lv_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(lv_8);
    if (var_4 != 0 && (local_C->vf_008() != 0 || local_C->vf_024() != 0)) {
        local_20 = (type_3DFEEC *)var_4;
        var_1C = ((type_D48D0 *)&local_20->unk_24_id)->sub_D4910();
        SCRIPT_CHECK(var_1C->vf_010() != 0 || var_1C->vf_01C() != 0 || var_1C->vf_020() != 0);
        if (local_C->vf_008() != 0)
            local_C->vf_008()->unk_624.sub_D48D0(var_1C);
        else
            local_C->vf_024()->unk_3D8.sub_D48D0(var_1C);
        var18 = var_1C->vf_010();
        if (var18 != 0)
            var18->vf_27C(1);
    }
    l10 = local_C->vf_120();
    if (l10 != 0)
        l10->unk_4E0 = 1;
    sub_44350(arg_4, 0);
}

// match: sub_58210 @ 0x00058210
// sp-match: sub_58210 @ 0x00046B70
// "StopRidingVehicle": the object's entity stops riding its vehicle, which
// learns of it (vf_27C).
void sub_58210(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *var_1C;
    type_3DBC78 *var18;
    type_3DDB98 *stk_14;
    type_67620 *l10;
    AIData *local_C;
    type_3DAFC8 *lv_8;
    type_3D3548 *var_4;

    l10 = sub_67620(arg_0);
    var_4 = l10->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    local_C = var_4->vf_120();
    if (local_C != 0)
        local_C->unk_4E0 = 0;
    lv_8 = var_4->vf_008();
    stk_14 = var_4->vf_024();
    if (lv_8 != 0 && lv_8->unk_624.sub_D4910() != 0) {
        var18 = lv_8->unk_624.sub_D4910()->vf_010();
        if (var18 != 0)
            var18->vf_27C(0);
        lv_8->unk_624.sub_D48D0(0);
    } else if (stk_14 != 0 && stk_14->unk_3D8.sub_D4910() != 0) {
        var_1C = stk_14->unk_3D8.sub_D4910()->vf_010();
        if (var_1C != 0)
            var_1C->vf_27C(0);
        stk_14->unk_3D8.sub_D48D0(0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_58360 @ 0x00058360
// sp-match: sub_58360 @ 0x00046C60
// "AttachToEntity": attaches its entity to the named object's (an animated
// entity, a vehicle or one with a spline) at the tag arg 2: rigidly as a
// child frame with arg 3, else as a soldier's or vehicle's ride; 0 when the
// named object's entity is none of those.
void sub_58360(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    RwInt32 var_8;
    type_3DF8D8_04 *var_C;
    RwInt32 var_10;
    type_3DF8D8 *var_14;
    type_3DFEEC *var_18;
    type_3D3548 *var_20;
    type_3D3548 *var_30;
    RwInt32 var_34;
    RwFrame *var_3C;
    RwFrame *var_44;
    RwMatrix var_90;
    RwMatrix var_D0;

    var_4 = sub_67620(arg_0);
    var_8 = 1;
    var_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 3);
    var_14 = sub_198800(var_C);
    SCRIPT_CHECK(var_14 != 0);
    if (var_14)
    {
        var_18 = (type_3DFEEC *)var_14;
        var_20 = var_4->vf_024()->get_unk_10();
        SCRIPT_CHECK(var_20 != 0);
        if (((type_D48D0 *)&var_18->unk_24_id)->sub_D4910()->vf_01C()
            || ((type_D48D0 *)&var_18->unk_24_id)->sub_D4910()->vf_020()
            || ((type_D48D0 *)&var_18->unk_24_id)->sub_D4910()->vf_010())
        {
            var_30 = ((type_D48D0 *)&var_18->unk_24_id)->sub_D4910();
            var_34 = SCRIPT_ARG(arg_4, 2);
            if (var_10)
            {
                var_3C = var_30->get_unk_340();
                var_44 = var_20->get_unk_340();
                sub_EC2D0(var_30->get_unk_264(), (RwInt32)&var_90, var_34, 1, 1);
                RwFrameTransform(var_44, &var_90, rwCOMBINEREPLACE);
                RwMatrixInitializeMacro(&var_D0, rwMATRIXTYPENORMAL);
                RwMatrixInvert(&var_D0, RwFrameGetLTM(var_3C));
                RwFrameTransform(var_44, &var_D0, rwCOMBINEPOSTCONCAT);
                RwFrameAddChild(var_3C, var_44);
            }
            else if (var_20->vf_008())
            {
                var_20->vf_008()->unk_620 = 1;
                var_20->vf_008()->unk_628 = var_34;
                var_20->vf_008()->unk_624.sub_D48D0(((type_D48D0 *)&var_18->unk_24_id)->sub_D4910());
            }
            else if (var_20->vf_024())
            {
                var_20->vf_024()->unk_3D4 = 1;
                var_20->vf_024()->unk_3DC = var_34;
                var_20->vf_024()->unk_3D8.sub_D48D0(((type_D48D0 *)&var_18->unk_24_id)->sub_D4910());
            }
        }
        else
        {
            var_8 = 0;
        }
    }
    else
    {
        SCRIPT_CHECK(0);
    }
    sub_44350(arg_4, &var_8);
}

// match: sub_58670 @ 0x00058670
// sp-match: sub_58670 @ 0x00046F20
// "DetachFromEntity": undoes "AttachToEntity": its frame leaves its parent,
// keeping its place in the world, and a ride is cleared.
void sub_58670(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D3548 *var_C;
    RwFrame *var_14;
    RwFrame *var_18;
    RwMatrix var_60;

    var_4 = sub_67620(arg_0);
    var_C = var_4->vf_024()->get_unk_10();
    var_14 = var_C->get_unk_340();
    SCRIPT_CHECK(var_C != 0);
    if (RwFrameGetParent(var_14))
    {
        var_18 = RwFrameGetParent(var_14);
        RwFrameRemoveChild(var_14);
        RwMatrixInitializeMacro(&var_60, rwMATRIXTYPENORMAL);
        var_60 = *RwFrameGetLTM(var_18);
        RwFrameTransform(var_14, &var_60, rwCOMBINEPOSTCONCAT);
    }
    if (var_C->vf_008())
    {
        var_C->vf_008()->unk_620 = 0;
        var_C->vf_008()->unk_628 = 0;
        var_C->vf_008()->unk_624.sub_D48D0(0);
    }
    else if (var_C->vf_024())
    {
        var_C->vf_024()->unk_3D4 = 0;
        var_C->vf_024()->unk_3DC = 0;
        var_C->vf_024()->unk_3D8.sub_D48D0(0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_587F0 @ 0x000587F0
// sp-match: sub_587F0 @ 0x00047020
// "GetDodgeDirection": of the directions args 1 to 4 (-1 for none), one in
// random order the soldier (flag 5) can dodge in with args 5 and 6, or -1.
void sub_587F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 v48;
    RwInt32 slot_44;
    RwUInt32 l40;
    RwInt32 var_3C;
    type_3DAFC8 *v38;
    RwInt32 v34;
    RwInt32 v30;
    type_67620 *var_2C;
    RwInt32 loc28[4];
    type_3D3548 *local_18;
    RwInt32 local_14[4];
    RwInt32 var_4;

    var_2C = sub_67620(arg_0);
    loc28[0] = SCRIPT_ARG(arg_4, 1);
    loc28[1] = SCRIPT_ARG(arg_4, 2);
    loc28[2] = SCRIPT_ARG(arg_4, 3);
    loc28[3] = SCRIPT_ARG(arg_4, 4);
    v34 = SCRIPT_ARG(arg_4, 5);
    var_4 = SCRIPT_ARG(arg_4, 6);
    local_14[0] = 0;
    local_14[1] = 1;
    local_14[2] = 2;
    local_14[3] = 3;
    local_18 = var_2C->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_18 != 0);
    SCRIPT_CHECK(local_18->unk_2C_5);
    v38 = (type_3DAFC8 *)local_18;
    for (var_3C = 0; var_3C < 4; var_3C++) {
        l40 = RpRandom() % 4;
        slot_44 = local_14[l40];
        local_14[l40] = local_14[var_3C];
        local_14[var_3C] = slot_44;
    }
    v30 = -1;
    for (v48 = 0; v48 < 4; v48++) {
        if (loc28[local_14[v48]] != -1 && v38->sub_13E580(local_14[v48], v34, var_4)) {
            v30 = loc28[local_14[v48]];
            break;
        }
    }
    sub_44350(arg_4, &v30);
}

// match: sub_58A20 @ 0x00058A20
// sp-match: sub_58A20 @ 0x000471E0
// "SetPickup": the soldier's (flag 5) pickup arg 1 (below 0x6E) and count
// arg 2 (at least 1), or none.
void sub_58A20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAFC8 *l14;
    type_67620 *var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    v8 = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    SCRIPT_CHECK(v8->unk_2C_5);
    l14 = (type_3DAFC8 *)v8;
    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (ebp_C >= 0x6E || ebp_C < 0 || var_4 < 1) {
        ebp_C = -1;
        var_4 = 0;
    }
    l14->unk_810 = ebp_C;
    l14->unk_814 = var_4;
    sub_44350(arg_4, 0);
}

// match: sub_58B20 @ 0x00058B20
// sp-match: sub_58B20 @ 0x000472D0
// "CheckAttackPostureTransition": whether the soldier (flag 5) can go from
// posture arg 1 to posture arg 2: 1 within a class (standing 7, 0x12, 0x2A,
// 0x3B, 0x3F; crouching 8, 0x2B, 0x40; other), else whether it can shoot
// its tracked entity from there (vf_134), which it cannot when crouching
// more than 250 below it.
void sub_58B20(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *var_3C;
    RwV3d *v38;
    type_3DAFC8 *v34;
    RwInt32 v30;
    type_3D3548 *var_2C;
    RwInt32 loc28;
    type_67620 *slot_24;
    RwInt32 v20;
    RwInt32 slot_1C;
    type_3D3548 *local_18;
    RwInt32 local_14;
    RwInt32 local_10;
    RwV3d var_C;

    slot_24 = sub_67620(arg_0);
    slot_1C = SCRIPT_ARG(arg_4, 1);
    local_10 = SCRIPT_ARG(arg_4, 2);
    switch (slot_1C) {
    case 8:
    case 0x2B:
    case 0x40:
        v30 = 2;
        break;
    case 7:
    case 0x12:
    case 0x2A:
    case 0x3B:
    case 0x3F:
        v30 = 1;
        break;
    default:
        v30 = 0;
    }
    switch (local_10) {
    case 8:
    case 0x2B:
    case 0x40:
        loc28 = 2;
        break;
    case 7:
    case 0x12:
    case 0x2A:
    case 0x3B:
    case 0x3F:
        loc28 = 1;
        break;
    default:
        loc28 = 0;
    }
    v20 = 0;
    local_14 = 1;
    if (v30 == loc28) {
        local_14 = 0;
        v20 = 1;
    }
    local_18 = slot_24->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_18 != 0);
    SCRIPT_CHECK(local_18->unk_2C_5);
    v34 = (type_3DAFC8 *)local_18;
    var_2C = v34->vf_120()->get_unk_1374();
    if (loc28 == 2 && var_2C != 0) {
        v38 = var_2C->vf_0CC();
        var_3C = local_18->vf_0CC();
        if (v38->y - var_3C->y > 250.0f) {
            local_14 = 0;
            v20 = 0;
        }
    }
    var_C.x = 0;
    var_C.y = 0;
    var_C.z = 0;
    if (local_14 != 0 && v34->vf_134(&var_C, var_2C, 0, 0, 0, 0, loc28))
        v20 = 1;
    sub_44350(arg_4, &v20);
}

// match: sub_58DD0 @ 0x00058DD0
// sp-match: sub_58DD0 @ 0x00047560
// sp-match: sub_58DD0 @ 0x00047560
// "SetPlayerBuddy": makes the entity of the object the handle arg 1 names
// player 0's buddy, shown if arg 2; hides the buddy otherwise.
void sub_58DD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_1C;
    RwInt32 var18;
    RwInt32 stk_14;
    type_3D2E7C *l10;
    type_10F710 *local_C;
    RwInt32 lv_8;
    type_3D3548 *var_4;

    stk_14 = SCRIPT_ARG(arg_4, 1);
    lv_8 = SCRIPT_ARG(arg_4, 2);
    l10 = (type_3D2E7C *)sub_67620(stk_14);
    var_4 = l10->sub_71300();
    local_C = (type_10F710 *)sub_1745A0(0);
    if (local_C != 0 && var_4 != 0) {
#ifdef CODFH_SP // the handle copied through its getter (SP 0x47560: the pop tail's registers follow)
        local_C->unk_2104.unk_00_h = var_4->get_unk_384_h();
#else
        var18 = var_4->unk_384;
        var_1C = var18;
        local_C->unk_2104 = var_1C;
#endif
        if (lv_8 != 0)
            dword_4B9190->sub_DFEB0(1, var_4);
    }
    if (lv_8 == 0)
        dword_4B9190->sub_DFEB0(0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_58EC0 @ 0x00058EC0
// sp-match: sub_58EC0 @ 0x000475F0
// "SetBuddyHealthType": the buddy display's health type arg 1.
void sub_58EC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_4B9190->sub_DFF40(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_58F10 @ 0x00058F10
// sp-match: sub_58F10 @ 0x00047630
// "SetTaskCommand_GoToAttachPoint": tells its script object to go to the
// tag arg 2 of the named object's entity ("SetTaskCommand_GoToPoint"), or
// "TaskCompleted" when there is none.
void sub_58F10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D2E7C *var_8;
    type_3DF8D8_04 *var_C;
    type_3DF8D8 *var_10;
    type_3DFEEC *var_14;
    type_3D3548 *var_18;
    RwInt32 var_1C;
    RwV3d var_28;
    RwInt32 var_2C;
    RpClump *var_30;
    RwMatrix var_70;
    RwReal var_80[4];

    var_4 = sub_67620(arg_0);
    var_8 = var_4->vf_024();
    SCRIPT_CHECK(var_8 != 0);
    var_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = sub_198800(var_C);
    SCRIPT_CHECK(var_10 != 0);
    if (var_10)
    {
        var_14 = (type_3DFEEC *)var_10;
        var_18 = ((type_D48D0 *)&var_14->unk_24_id)->sub_D4910();
        if (!var_18)
        {
            var_1C = 0;
            sub_6B5F0("TaskCompleted", (type_67620 *)var_8, 0, 0, &var_1C, 1, true, false);
        }
        else if ((var_14->unk_10 & 2) && var_18)
        {
            var_28.x = 0.0f;
            var_28.y = 0.0f;
            var_28.z = 0.0f;
            var_2C = SCRIPT_ARG(arg_4, 2);
            var_30 = var_18->unk_25C.unk_08;
            if (var_30)
            {
                sub_EC2D0(var_30, (RwInt32)&var_70, var_2C, 0, 1);
#ifdef CODFH_SP // shape: a struct copy (SP 0x47630: three dword moves)
                var_28 = var_70.pos;
#else
                var_28.x = var_70.pos.x;
                var_28.y = var_70.pos.y;
                var_28.z = var_70.pos.z;
#endif
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            var_80[0] = var_28.x;
            var_80[1] = var_28.y;
            var_80[2] = var_28.z;
            var_80[3] = 0.0f;
            sub_6B5F0("SetTaskCommand_GoToPoint", (type_67620 *)var_8, 0, 0, (RwInt32 *)var_80, 4, true, false);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_590F0 @ 0x000590F0
// sp-match: sub_590F0 @ 0x00047830
// "SetTaskCommand_GoToAttachPoint": tells its script object to go to the
// tag arg 2 of the named object's entity ("SetTaskCommand_TurnToPoint"), or
// "TaskCompleted" when there is none.
void sub_590F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D2E7C *var_8;
    type_3DF8D8_04 *var_C;
    type_3DF8D8 *var_10;
    type_3DFEEC *var_14;
    type_3D3548 *var_18;
    RwInt32 var_1C;
    RwV3d var_28;
    RwInt32 var_2C;
    RpClump *var_30;
    RwMatrix var_70;
    RwReal var_80[4];

    var_4 = sub_67620(arg_0);
    var_8 = var_4->vf_024();
    SCRIPT_CHECK(var_8 != 0);
    var_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = sub_198800(var_C);
    SCRIPT_CHECK(var_10 != 0);
    if (var_10)
    {
        var_14 = (type_3DFEEC *)var_10;
        var_18 = ((type_D48D0 *)&var_14->unk_24_id)->sub_D4910();
        if (!var_18)
        {
            var_1C = 0;
            sub_6B5F0("TaskCompleted", (type_67620 *)var_8, 0, 0, &var_1C, 1, true, false);
        }
        else if ((var_14->unk_10 & 2) && var_18)
        {
            var_28.x = 0.0f;
            var_28.y = 0.0f;
            var_28.z = 0.0f;
            var_2C = SCRIPT_ARG(arg_4, 2);
            var_30 = var_18->unk_25C.unk_08;
            if (var_30)
            {
                sub_EC2D0(var_30, (RwInt32)&var_70, var_2C, 0, 1);
#ifdef CODFH_SP // shape: a struct copy (SP 0x47830: three dword moves)
                var_28 = var_70.at;
#else
                var_28.x = var_70.at.x;
                var_28.y = var_70.at.y;
                var_28.z = var_70.at.z;
#endif
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            var_80[0] = var_28.x;
            var_80[1] = var_28.y;
            var_80[2] = var_28.z;
            var_80[3] = 300.0f;
            sub_6B5F0("SetTaskCommand_TurnToPoint", (type_67620 *)var_8, 0, 0, (RwInt32 *)var_80, 4, true, false);
        }
        else
        {
            SCRIPT_CHECK(0);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_592E0 @ 0x000592E0
// sp-match: sub_592E0 @ 0x00047A40
// "SetTaskCommand_TeleportToAttachPoint": as "SetTaskCommand_GoToAttachPoint",
// teleporting there ("SetTaskCommand_TeleportToPoint").
void sub_592E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;
    type_3D2E7C *var_8;
    type_3DF8D8_04 *var_C;
    type_3DF8D8 *var_10;
    type_3DFEEC *var_14;
    type_3D3548 *var_18;
    RwInt32 var_1C;
    RwV3d var_28;
    RwInt32 var_2C;
    RpClump *var_30;
    RwMatrix var_70;
    RwReal var_7C[3];

    var_4 = sub_67620(arg_0);
    var_8 = var_4->vf_024();
    SCRIPT_CHECK(var_8 != 0);
    var_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = sub_198800(var_C);
    SCRIPT_CHECK(var_10 != 0);
    if (var_10)
    {
        var_14 = (type_3DFEEC *)var_10;
        var_18 = ((type_D48D0 *)&var_14->unk_24_id)->sub_D4910();
        if (!var_18)
        {
            var_1C = 0;
            sub_6B5F0("TaskCompleted", (type_67620 *)var_8, 0, 0, &var_1C, 1, true, false);
        }
        else if ((var_14->unk_10 & 2) && var_18)
        {
            var_28.x = 0.0f;
            var_28.y = 0.0f;
            var_28.z = 0.0f;
            var_2C = SCRIPT_ARG(arg_4, 2);
            var_30 = var_18->unk_25C.unk_08;
            if (var_30)
            {
                sub_EC2D0(var_30, (RwInt32)&var_70, var_2C, 0, 1);
#ifdef CODFH_SP // shape: a struct copy (SP 0x47A40: three dword moves)
                var_28 = var_70.pos;
#else
                var_28.x = var_70.pos.x;
                var_28.y = var_70.pos.y;
                var_28.z = var_70.pos.z;
#endif
            }
            else
            {
                SCRIPT_CHECK(0);
            }
            var_7C[0] = var_28.x;
            var_7C[1] = var_28.y;
            var_7C[2] = var_28.z;
            sub_6B5F0("SetTaskCommand_TeleportToPoint", (type_67620 *)var_8, 0, 0, (RwInt32 *)var_7C, 3, true, false);
        }
    }
    else
    {
        SCRIPT_CHECK(0);
    }
    sub_44350(arg_4, 0);
}

// match: sub_594B0 @ 0x000594B0
// sp-match: sub_594B0 @ 0x00047C30
// "Vehicle_AllowAttack": whether the vehicle entity of the object under the key arg 1 (two
// slots) may attack (arg 2).
void sub_594B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *stk_18;
    type_3D3548 *l14;
    type_3DFEEC *var_10;
    RwInt32 ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARG(arg_4, 2);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        var_10 = (type_3DFEEC *)var_4;
        l14 = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
        if (l14 != 0 && l14->vf_010() != 0) {
            stk_18 = l14->vf_010();
            if ((var_10->unk_10 & 2) && stk_18 != 0)
                stk_18->unk_DC0 = ebp_C;
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_595A0 @ 0x000595A0
// sp-match: sub_595A0 @ 0x00047D30
// "Vehicle_AllowMove": whether the vehicle entity of the object under the key arg 1 (two
// slots) may move (arg 2).
void sub_595A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *stk_18;
    type_3D3548 *l14;
    type_3DFEEC *var_10;
    RwInt32 ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARG(arg_4, 2);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        var_10 = (type_3DFEEC *)var_4;
        l14 = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
        if (l14 != 0 && l14->vf_010() != 0) {
            stk_18 = l14->vf_010();
            if ((var_10->unk_10 & 2) && stk_18 != 0)
                stk_18->unk_DC4 = ebp_C;
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_59690 @ 0x00059690
// sp-match: sub_59690 @ 0x00047E30
// "CompareGodalls": whether the keys arg 1 and arg 2 (two slots each) are
// equal.
void sub_59690(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    local_8 = 0;
    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    varC = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    if (var_4->unk_00 == varC->unk_00 && var_4->unk_04 == varC->unk_04)
        local_8 = 1;
    sub_44350(arg_4, &local_8);
}

// match: sub_59730 @ 0x00059730
// sp-match: sub_59730 @ 0x00047EB0
// "ReturnNegGodID": the null key (-1, -1).
void sub_59730(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 var_8;

    var_8.unk_00 = -1;
    var_8.unk_04 = -1;
    sub_44350(arg_4, &var_8);
}

// match: sub_59770 @ 0x00059770
// sp-match: sub_59770 @ 0x00047F10
// "Vehicle_IncrementRiderCount": counts a rider on the vehicle entity of the object
// under the key arg 1 (two slots): it may attack, and move with two riders
// and none incoming.
void sub_59770(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *l14;
    type_3D3548 *var_10;
    type_3DFEEC *ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        ebp_C = (type_3DFEEC *)var_4;
        var_10 = ((type_D48D0 *)&ebp_C->unk_24_id)->sub_D4910();
        if (var_10 != 0 && var_10->vf_010() != 0) {
            l14 = var_10->vf_010();
            if ((ebp_C->unk_10 & 2) && l14 != 0) {
                l14->unk_DC8++;
                l14->unk_DC0 = 1;
                if (l14->unk_DCC == 0 && l14->unk_DC8 >= 2)
                    l14->unk_DC4 = 1;
            }
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_59880 @ 0x00059880
// sp-match: sub_59880 @ 0x00048020
// "Vehicle_IncrementIncomingRiderCount": counts an incoming rider on the vehicle entity of
// the object under the key arg 1 (two slots), which may not move.
void sub_59880(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *l14;
    type_3D3548 *var_10;
    type_3DFEEC *ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        ebp_C = (type_3DFEEC *)var_4;
        var_10 = ((type_D48D0 *)&ebp_C->unk_24_id)->sub_D4910();
        if (var_10 != 0 && var_10->vf_010() != 0) {
            l14 = var_10->vf_010();
            if ((ebp_C->unk_10 & 2) && l14 != 0) {
                l14->unk_DCC++;
                l14->unk_DC4 = 0;
            }
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_59960 @ 0x00059960
// sp-match: sub_59960 @ 0x00048110
// "Vehicle_DecrementRiderCount": uncounts a rider on the vehicle entity of the
// object under the key arg 1 (two slots): without riders it may not attack,
// below two it may not move.
void sub_59960(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *l14;
    type_3D3548 *var_10;
    type_3DFEEC *ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        ebp_C = (type_3DFEEC *)var_4;
        var_10 = ((type_D48D0 *)&ebp_C->unk_24_id)->sub_D4910();
        if (var_10 != 0 && var_10->vf_010() != 0) {
            l14 = var_10->vf_010();
            if ((ebp_C->unk_10 & 2) && l14 != 0) {
                l14->unk_DC8--;
                if (l14->unk_DC8 < 0)
                    l14->unk_DC8 = 0;
                if (l14->unk_DC8 == 0)
                    l14->unk_DC0 = 0;
                if (l14->unk_DC8 < 2)
                    l14->unk_DC4 = 0;
            }
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_59A90 @ 0x00059A90
// sp-match: sub_59A90 @ 0x00048230
// "FlakVehicle_SetCrewMember": makes the object's entity the crew member of
// seat arg 1 (0x32 to 0x34) of the flak vehicle with the handle arg 2.
void sub_59A90(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *stk_18;
    type_3D2E7C *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    stk_18 = sub_67620(arg_0);
    l14 = stk_18->vf_024();
    SCRIPT_CHECK(l14 != 0);
    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_D5CF0(var_4);
    switch (v8) {
    case 0x32:
        var_10 = 0;
        break;
    case 0x33:
        var_10 = 1;
        break;
    case 0x34:
        var_10 = 2;
        break;
    default:
        var_10 = -1;
        SCRIPT_CHECK(0);
    }
    if (ebp_C != 0 && ebp_C->vf_018() != 0)
        ebp_C->vf_018()->sub_15ABA0(var_10, l14->sub_71300());
    sub_44350(arg_4, 0);
}

// match: sub_59BB0 @ 0x00059BB0
// sp-match: sub_59BB0 @ 0x00048350
// "FlakVehicle_GetCrewMember": the crew member of seat arg 1 (0x32 to 0x34)
// of the flak vehicle with the handle arg 2, or 0.
void sub_59BB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_D5CF0(var_4);
    switch (v8) {
    case 0x32:
        l14 = 0;
        break;
    case 0x33:
        l14 = 1;
        break;
    case 0x34:
        l14 = 2;
        break;
    default:
        l14 = -1;
        SCRIPT_CHECK(0);
    }
    var_10 = 0;
    if (ebp_C != 0 && ebp_C->vf_018() != 0)
        var_10 = ebp_C->vf_018()->sub_15AB40(l14);
    sub_44350(arg_4, &var_10);
}

// match: sub_59CB0 @ 0x00059CB0
// sp-match: sub_59CB0 @ 0x00048440
// "FlakVehicle_SetCrewMemberStatus": the status arg 3 of seat arg 1 (0x32
// to 0x34) of the flak vehicle with the handle arg 2.
void sub_59CB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_D5CF0(var_4);
    switch (v8) {
    case 0x32:
        var_10 = 0;
        break;
    case 0x33:
        var_10 = 1;
        break;
    case 0x34:
        var_10 = 2;
        break;
    default:
        var_10 = -1;
        SCRIPT_CHECK(0);
    }
    if (ebp_C != 0 && ebp_C->vf_018() != 0) {
        l14 = SCRIPT_ARG(arg_4, 3);
        ebp_C->vf_018()->sub_15ABE0(var_10, l14);
    }
    sub_44350(arg_4, 0);
}

// match: sub_59DD0 @ 0x00059DD0
// sp-match: sub_59DD0 @ 0x00048520
// "FlakVehicle_ClearCrewMember": clears seat arg 1 (0x32 to 0x34) of the
// flak vehicle with the handle arg 2, with arg 3.
void sub_59DD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    v8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    ebp_C = sub_D5CF0(var_4);
    switch (v8) {
    case 0x32:
        l14 = 0;
        break;
    case 0x33:
        l14 = 1;
        break;
    case 0x34:
        l14 = 2;
        break;
    default:
        l14 = -1;
        SCRIPT_CHECK(0);
    }
    var_10 = SCRIPT_ARG(arg_4, 3);
    if (ebp_C != 0 && ebp_C->vf_018() != 0)
        ebp_C->vf_018()->sub_15AC00(l14, var_10);
    sub_44350(arg_4, 0);
}

// match: sub_59EF0 @ 0x00059EF0
// sp-match: sub_59EF0 @ 0x00048600
// "Vehicle_DecrementIncomingRiderCount": uncounts an incoming rider on the
// vehicle entity of the object under the key arg 1 (two slots), after
// sending "SetIncoming" from the object; with none incoming and two riders
// it may move.
void sub_59EF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_20;
    type_3DBC78 *var_1C;
    type_3D3548 *var18;
    type_3DFEEC *stk_14;
    type_67620 *l10;
    type_3D2E7C *local_C;
    type_3DF8D8_04 *lv_8;
    type_3DF8D8 *var_4;

    l10 = sub_67620(arg_0);
    local_C = l10->vf_024();
    SCRIPT_CHECK(local_C != 0);
    lv_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(lv_8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        stk_14 = (type_3DFEEC *)var_4;
        var18 = ((type_D48D0 *)&stk_14->unk_24_id)->sub_D4910();
        if (var18 != 0 && var18->vf_010() != 0) {
            var_1C = var18->vf_010();
            if ((stk_14->unk_10 & 2) && var_1C != 0) {
                local_20 = 0;
                sub_6B5F0("SetIncoming", (type_67620 *)local_C, 0, 0, &local_20, 1, 1, 0);
                var_1C->unk_DCC--;
                if (var_1C->unk_DCC < 0)
                    var_1C->unk_DCC = 0;
                if (var_1C->unk_DCC == 0 && var_1C->unk_DC8 >= 2)
                    var_1C->unk_DC4 = 1;
            }
        }
    } else
        SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_5A060 @ 0x0005A060
// sp-match: sub_5A060 @ 0x000487B0
// "NamedEntityExists": whether the object under the key arg 1 (two slots)
// holds a live entity; nothing when there is no object.
void sub_5A060(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *l14;
    type_3D3548 *var_10;
    RwInt32 ebp_C;
    type_3DF8D8_04 *v8;
    type_3DF8D8 *var_4;

    ebp_C = 0;
    v8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_198800(v8);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        l14 = (type_3DFEEC *)var_4;
        var_10 = ((type_D48D0 *)&l14->unk_24_id)->sub_D4910();
        if (var_10 != 0)
            ebp_C = 1;
        sub_44350(arg_4, &ebp_C);
    } else {
        SCRIPT_CHECK(0);
        sub_44350(arg_4, 0);
    }
}

// match: sub_5A110 @ 0x0005A110
// sp-match: sub_5A110 @ 0x000489D0
// "GetRidingVehicle": whether the object's entity (kind 2) rides a vehicle
// (its AI object's unk_4E0).
void sub_5A110(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    type_67620 *var_10;
    type_3D2E7C *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    ebp_C = var_10->vf_024();
    SCRIPT_CHECK(ebp_C != 0);
    SCRIPT_CHECK(ebp_C->get_unk_14() == 2);
    v8 = ebp_C->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    l14 = 0;
    if (var_4 != 0)
        l14 = var_4->unk_4E0;
    sub_44350(arg_4, &l14);
}

// match: sub_5A1C0 @ 0x0005A1C0
// sp-match: sub_5A1C0 @ 0x00048B10
// "SetRestrictedTankTargetZone": restricts the targets of the object's tank
// (kind 2, vf_014) to the zone (arg 1, arg 2).
void sub_5A1C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *l14;
    type_3D2E7C *var_10;
    type_3D3548 *ebp_C;
    RwReal v8;
    RwReal var_4;

    l14 = sub_67620(arg_0);
    var_10 = l14->vf_024();
    SCRIPT_CHECK(var_10 != 0);
    SCRIPT_CHECK(var_10->get_unk_14() == 2);
    ebp_C = var_10->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    SCRIPT_CHECK(ebp_C->vf_014() != 0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    v8 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    ebp_C->vf_014()->sub_15A530(var_4, v8);
    sub_44350(arg_4, 0);
}

// match: sub_5A2C0 @ 0x0005A2C0
// sp-match: sub_5A2C0 @ 0x00048C80
// "ClearRestrictedTankTargetZone": lifts the target restriction of the
// object's tank (kind 2, vf_014).
void sub_5A2C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D2E7C *local_8;
    type_3D3548 *var_4;

    varC = sub_67620(arg_0);
    local_8 = varC->vf_024();
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK(local_8->get_unk_14() == 2);
    var_4 = local_8->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->vf_014() != 0);
    var_4->vf_014()->sub_15A590();
    sub_44350(arg_4, 0);
}

// match: sub_5A370 @ 0x0005A370
// sp-match: sub_5A370 @ 0x00048DC0
// "GetTankHFOV": the horizontal field of view of the tank with the handle
// arg 1, or 0.
void sub_5A370(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_D5CF0(var_4);
    if (local_8 != 0)
        varC = ((type_3DBC78 *)local_8)->unk_DD0;
    else
        varC = 0;
    sub_44350(arg_4, &varC);
}

// match: sub_5A3E0 @ 0x0005A3E0
// sp-match: sub_5A3E0 @ 0x00048E40
// "SetTankHFOV": the horizontal field of view arg 2 (AI parameter 2) of the
// tank with the handle arg 1.
void sub_5A3E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_D5CF0(var_4);
    if (local_8 != 0) {
        varC = SCRIPT_ARG(arg_4, 2);
        local_8->vf_16C(2, varC);
    }
    sub_44350(arg_4, 0);
}

// match: sub_5A480 @ 0x0005A480
// sp-match: sub_5A480 @ 0x00048EA0
// "GetPreferredAttackRange": the preferred attack range (vf_114) of the
// entity with the handle arg 1, in state 0 or 1.
void sub_5A480(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_D5CF0(var_4);
    SCRIPT_CHECK(local_8->unk_24 == 0 || local_8->unk_24 == 1);
    varC = local_8->vf_114();
    sub_44350(arg_4, &varC);
}

// match: sub_5A510 @ 0x0005A510
// sp-match: sub_5A510 @ 0x00048F60
// "DontWaitForNoRenderToDeleteMe": clears flag 11 of the object's entity.
void sub_5A510(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    type_67620 *local_8;

    local_8 = sub_67620(arg_0);
    var_4 = local_8->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_28 &= ~0x800;    // not an address: flag 11
    sub_44350(arg_4, 0);
}

// match: sub_5A570 @ 0x0005A570
// sp-match: sub_5A570 @ 0x00048FE0
// "RedSquareHax": dword_438E84 = arg 1.
void sub_5A570(RwUInt32 arg_0, type_44350 *arg_4)
{
    dword_438E84 = SCRIPT_ARG(arg_4, 1);
    sub_44350(arg_4, 0);
}

// match: sub_5A5B0 @ 0x0005A5B0
// sp-match: sub_5A5B0 @ 0x00049010
// "BlockFacing": for a soldier (kind 2), whether its AI object's facing is
// blocked (arg 1).
void sub_5A5B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *var_10;
    type_67620 *ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    SCRIPT_CHECK(ebp_C->vf_024()->get_unk_14() == 2);
    v8 = ebp_C->vf_024()->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    if (v8->vf_008() != 0) {
        var_10 = v8->vf_120();
        SCRIPT_CHECK(var_10 != 0);
        var_10->unk_49C_10 = var_4;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5A6C0 @ 0x0005A6C0
// sp-match: sub_5A6C0 @ 0x00049190
// "AttachRingMountGunToGunner": the soldier of the kind-2 object arg_0
// takes the ring-mounted gun arg 1 (in list 0 or 1); the gun turns by the
// angle, in the horizontal plane, between its bone 0x9B's facing and the
// soldier's (negated when the soldier is to its left).
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_5A6C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwFrame *q68;
    RwInt32 lcl_64;
    RwReal l60;
    RwV3d fp_5C;
    type_67620 *loc50;
    type_3D2E7C *x4C;
    RwMatrix *w48;
    RwMatrix *loc44;
    type_3DAFC8 *fp_40;
    type_3D3548 *ebp_3C;
    RwV3d local_38;
    RwV3d stk_2C;
    RwInt32 t20;
    RwV3d l1C;
    RwV3d lv_10;
    type_5A6C0 *bp_4;

    loc50 = sub_67620(arg_0);
    x4C = loc50->vf_024();
    SCRIPT_CHECK(x4C != 0);
    SCRIPT_CHECK(x4C->get_unk_14() == 2);
    ebp_3C = x4C->get_unk_10();
    SCRIPT_CHECK(ebp_3C != 0);
    fp_40 = static_cast<type_3DAFC8 *>(ebp_3C);
    t20 = SCRIPT_ARG(arg_4, 1);
    bp_4 = (type_5A6C0 *)sub_D5CF0(t20);
    SCRIPT_CHECK(bp_4->unk_24 == 0 || bp_4->unk_24 == 1);
    q68 = fp_40->get_unk_340();
    lv_10 = q68->ltm.at;
    w48 = bp_4->Animation_GetMatrixArray();
    lcl_64 = RpHAnimIDGetIndex(bp_4->get_unk_284()->get_unk_18(), 0x9B);
    SCRIPT_CHECK(lcl_64 != -1);
    loc44 = &w48[lcl_64];
    local_38 = loc44->at;
    local_38.y = 0.0f;
    lv_10.y = 0.0f;
    RwV3dNormalize(&stk_2C, &local_38);
    RwV3dNormalize(&fp_5C, &lv_10);
    // The cosine clamped to +-0.99999 by two conditionals, the inner one
    // evaluated again for the value.
    l60 = acos(0.99999f > (RwV3dDotProduct(&fp_5C, &stk_2C) > -0.99999f
                                  ? RwV3dDotProduct(&fp_5C, &stk_2C) : -0.99999f)
                      ? (RwV3dDotProduct(&fp_5C, &stk_2C) > -0.99999f
                             ? RwV3dDotProduct(&fp_5C, &stk_2C) : -0.99999f)
                      : 0.99999f)
             * 57.295776f;
    RwV3dCrossProduct(&l1C, &fp_5C, &stk_2C);
    if (l1C.y > 0.0f)
        l60 *= -1.0f;
    bp_4->unk_B24 = l60;
    sub_44350(arg_4, 0);
}

// match: sub_5A9D0 @ 0x0005A9D0
// sp-match: sub_5A9D0 @ 0x000572D0
// "LoadSoundBank": loads the sound bank under the key arg 1 (two slots);
// arguments 2 (a word) and 3 (below 5) are only read. Its first check ORs
// the key's validity into the key's low word, `-1 &&` first, as written.
void sub_5A9D0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP
    // shape: the key and the two read-only arguments live in one local record
    // whose address escapes, so /O2 keeps their stores (SP 0x5737B, 0x5738C):
    // type_825E0's layout (types/soundbank.h, not included by this unit)
    struct
    {
        type_3DF8D8_04 var_10;
        RwInt32 v8;
        RwInt16 var_4;
    } l;

    l.var_10 = *(type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(l.var_10.unk_00 |= (-1 && l.var_10.unk_04 != -1 && l.var_10.unk_00 != 0 && l.var_10.unk_04 != 0));
    l.var_4 = SCRIPT_ARGT<RwInt16>(arg_4, 2);
    l.v8 = SCRIPT_ARG(arg_4, 3);
    SCRIPT_CHECK(l.v8 < 5);
    sub_84300((type_825E0 *)(&l.var_10));
    sub_44350(arg_4, 0);
#else
    type_3DF8D8_04 var_10;
    RwInt32 v8;
    RwInt16 var_4;

    var_10 = *(type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_10.unk_00 |= (-1 && var_10.unk_04 != -1 && var_10.unk_00 != 0 && var_10.unk_04 != 0));
    var_4 = SCRIPT_ARGT<RwInt16>(arg_4, 2);
    v8 = SCRIPT_ARG(arg_4, 3);
    SCRIPT_CHECK(v8 < 5);
    sub_84300((type_825E0 *)(&var_10));
    sub_44350(arg_4, 0);
#endif
}

// match: sub_5AAE0 @ 0x0005AAE0
// sp-match: sub_5AAE0 @ 0x00049460
// "LoadAnimGroup": loads animation group arg 2 (1 to 6) of the object under
// the key arg 1 (two slots), by its name (vf_00C).
void sub_5AAE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8 *varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(--local_8 >= 0 && local_8 < 6);
    varC = sub_198800(var_4);
    SCRIPT_CHECK(varC != 0);
    sub_777F0((const RwChar *)varC->vf_00C(), *(type_449C94_08 *)var_4, local_8, 0);
    sub_44350(arg_4, 0);
}

// match: sub_5ABC0 @ 0x0005ABC0
// sp-match: sub_5ABC0 @ 0x00049540
// "SetRestartAnimGroup": animation group arg 2 (from 1) restarts from the
// key arg 1 (two slots).
void sub_5ABC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3DF8D8_04 *local_8;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    var_4--;
    if (dword_4B67CC != 0)
        dword_4B67CC->sub_A1130(var_4, local_8);
    sub_44350(arg_4, 0);
}

// match: sub_5AC50 @ 0x0005AC50
// sp-match: sub_5AC50 @ 0x00049590
// Plays the facial animation arg_0 on the soldier arg_4 (flagging it in
// unk_805), or formats its id for a message that is never shown.
void sub_5AC50(RwInt32 arg_0, type_3DAFC8 *arg_4)
{
    RwChar bp_2C[0x20];
    RwInt32 local_8;
    RwInt32 var_4;

    if (sub_77B70(arg_0, (void **)(&local_8), (void **)(&var_4)) != 0) {
        arg_4->unk_28C->sub_794C0(0.1f);
        arg_4->unk_28C->sub_796A0((RtAnimAnimation *)local_8, arg_0, 0, (type_783F0 *)var_4, 0, 1.0f,
                                  1.0f);
        arg_4->unk_805 = 9;
    } else
        sprintf(bp_2C, "0x%08x", arg_0);
}

// match: sub_5ACE0 @ 0x0005ACE0
// sp-match: sub_5ACE0 @ 0x00049630
// As sub_5AC50, for a type_3DDB98 (unk_694).
void sub_5ACE0(RwInt32 arg_0, type_3DDB98 *arg_4)
{
    RwChar bp_2C[0x20];
    RwInt32 local_8;
    RwInt32 var_4;

    if (sub_77B70(arg_0, (void **)(&local_8), (void **)(&var_4)) != 0) {
        arg_4->unk_28C->sub_794C0(0.1f);
        arg_4->unk_28C->sub_796A0((RtAnimAnimation *)local_8, arg_0, 0, (type_783F0 *)var_4, 0, 1.0f,
                                  1.0f);
        arg_4->unk_694 = 9;
    } else
        sprintf(bp_2C, "0x%08x", arg_0);
}

// match: sub_5AD70 @ 0x0005AD70
// sp-match: sub_5AD70 @ 0x000496D0
// "PlayFacialAnimation": plays the facial animation arg 1 on the entity (a
// type_3DDB98 or a soldier).
void sub_5AD70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    if (local_8->vf_024() != 0)
        sub_5ACE0(var_4, local_8->vf_024());
    else if (local_8->vf_008() != 0)
        sub_5AC50(var_4, local_8->vf_008());
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5AE10 @ 0x0005AE10
// sp-match: sub_5AE10 @ 0x00049750
// "PlayFacialAnimationOnNamedEntity": plays the facial animation arg 1 on
// the entity of the kind-0x2E object under the key arg 2 (two slots).
void sub_5AE10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *l14;
    type_3DFEEC *var_10;
    type_3D3548 *ebp_C;
    type_3DF8D8 *v8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    ebp_C = 0;
    l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    v8 = sub_198800(l14);
    SCRIPT_CHECK(v8 != 0);
    SCRIPT_CHECK(v8->vf_008() == 0x2E);
    var_10 = (type_3DFEEC *)v8;
    SCRIPT_CHECK(var_10->unk_10 != 0);
    ebp_C = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
    SCRIPT_CHECK(ebp_C != 0);
    if (ebp_C->vf_024() != 0)
        sub_5ACE0(var_4, ebp_C->vf_024());
    else if (ebp_C->vf_008() != 0)
        sub_5AC50(var_4, ebp_C->vf_008());
    sub_44350(arg_4, 0);
}

// match: sub_5AF50 @ 0x0005AF50
// sp-match: sub_5AF50 @ 0x000498E0
// "HasDefaultSplinePath": whether the object's entity (kind 2) has a default
// spline path: its AI object's (flag 12 of unk_49C and a spline), else a
// type_3DDB98's or type_3DA6C0's (vf_0F4).
void sub_5AF50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    v8 = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    ebp_C = 0;
    var_4 = v8->vf_120();
    if (var_4 != 0) {
        if (((var_4->unk_49C >> 12) & 1) && var_4->get_unk_D14() != 0)
            ebp_C = 1;
    } else if (v8->vf_024() != 0 && v8->vf_0F4() != 0)
        ebp_C = 1;
    else if (v8->vf_01C() != 0 && v8->vf_0F4() != 0)
        ebp_C = 1;
    sub_44350(arg_4, &ebp_C);
}

// match: sub_5B080 @ 0x0005B080
// sp-match: sub_5B080 @ 0x00049A70
// "DivorceSplinePath": the object's entity (kind 2) leaves its spline path:
// its AI object's (sending "SplinePath_ArrivedATDestination"), or a
// type_3DA6C0's, type_3DDB98's or type_3DAC58's (vf_0F8). It pops nothing.
void sub_5B080(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAC58 *stk_18;
    type_3DDB98 *l14;
    type_3DA6C0 *var_10;
    type_67620 *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    SCRIPT_CHECK(ebp_C->vf_024()->get_unk_14() == 2);
    v8 = ebp_C->vf_024()->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    if (var_4 != 0) {
        var_4->unk_D14 = 0;
        var_4->unk_D18 = 0.0f;
        var_4->sub_29360();
        sub_6B5F0("SplinePath_ArrivedATDestination", (type_67620 *)(v8->vf_098()), 0, 0, 0, 0, 1, 0);
    } else if (v8->vf_01C() != 0) {
        var_10 = (type_3DA6C0 *)v8;
        var_10->unk_448 = 0;
        var_10->unk_3E0 = 0.0f;
        var_10->unk_444 = 1.0f;
        var_10->vf_0F8(0.0f);
    } else if (v8->vf_024() != 0) {
        l14 = (type_3DDB98 *)v8;
        l14->sub_178640(0);
        l14->vf_0F8(0);
    } else if (v8->vf_020() != 0) {
        stk_18 = (type_3DAC58 *)v8;
        stk_18->unk_3B8 = 0;
        stk_18->unk_3B4 = 0.0f;
        stk_18->unk_3C0 = 1.0f;
        stk_18->vf_0F8(0);
    }
}

// match: sub_5B240 @ 0x0005B240
// sp-match: sub_5B240 @ 0x000573F0
// "SetSplinePathFromName": puts the object's entity (kind 2) on the spline
// of the kind-0x2E object (flags 0x80) under the key arg 1 (two slots), or
// for (-1, -1) on its trigger's default path (unk_F8, unk_F0, unk_E0, unk_E8
// or unk_1EC by class), from the start with the end at 1.
void sub_5B240(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DE0E0 *local_28;
    type_3DAC58 *local_24;
    type_3DDB98 *local_20;
    type_3DA6C0 *var_1C;
    type_3DF8D8_04 *var18;
    type_67620 *stk_14;
    type_3DFEEC *l10;
    type_3D3548 *local_C;
    type_3DF8D8 *lv_8;
    AIData *var_4;

    stk_14 = sub_67620(arg_0);
    SCRIPT_CHECK(stk_14->vf_024() != 0);
    SCRIPT_CHECK(stk_14->vf_024()->get_unk_14() == 2);
    local_C = stk_14->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_C != 0);
    var18 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = local_C->vf_120();
    lv_8 = 0;
    if (var18->unk_00 == -1 && var18->unk_04 == -1) {
        if (local_C->vf_008() != 0) {
            if (!((var_4->unk_49C >> 12) & 1))
                SCRIPT_CHECK(0);
            SCRIPT_CHECK(local_C->vf_008()->get_unk_34C() != 0);
            lv_8 = sub_198800(&local_C->vf_008()->get_unk_34C()->unk_F8);
        } else if (local_C->vf_01C() != 0) {
            SCRIPT_CHECK(local_C->vf_01C()->get_unk_34C() != 0);
            lv_8 = sub_198800(&local_C->vf_01C()->get_unk_34C()->unk_F0);
        } else if (local_C->vf_024() != 0) {
            SCRIPT_CHECK(local_C->vf_024()->get_unk_34C() != 0);
            lv_8 = sub_198800(&local_C->vf_024()->get_unk_34C()->unk_E0);
        } else if (local_C->vf_020() != 0) {
            SCRIPT_CHECK(local_C->vf_020()->get_unk_34C() != 0);
            lv_8 = sub_198800(&local_C->vf_020()->get_unk_34C()->unk_E8);
        } else if (local_C->vf_010() != 0 || local_C->vf_014() != 0) {
            // This check and the four after the lookup reserve no slots.
            sub_44220(local_C->get_unk_34C() != 0);
            lv_8 = sub_198800(&local_C->get_unk_34C()->unk_1EC);
        }
    } else
        lv_8 = sub_198800(var18);
    sub_44220(lv_8 != 0);
    sub_44220(lv_8->vf_008() == 0x2E);
    l10 = (type_3DFEEC *)lv_8;
    sub_44220(l10->unk_10 == 0x80);
    sub_44220(l10->unk_24 != 0);
    if (var_4 != 0) {
        var_4->unk_D14 = l10->get_unk_24();
        var_4->set_unk_D1C(1.0f);
    } else if (local_C->vf_01C() != 0) {
        var_1C = (type_3DA6C0 *)local_C;
        var_1C->unk_448 = l10->get_unk_24();
        var_1C->unk_3E0 = 0.0f;
        var_1C->unk_444 = 1.0f;
        var_1C->set_unk_444(1.0f);
    } else if (local_C->vf_024() != 0) {
        local_20 = (type_3DDB98 *)local_C;
        local_20->sub_178640(l10->unk_24);
        local_20->sub_5B800(1.0f);
    } else if (local_C->vf_020() != 0) {
        local_24 = (type_3DAC58 *)local_C;
        local_24->unk_3B8 = l10->get_unk_24();
        local_24->unk_3B4 = 0.0f;
        local_24->unk_3C0 = 1.0f;
        local_24->sub_5B850(1.0f);
    } else if (local_C->vf_02C() != 0) {
        local_28 = (type_3DE0E0 *)local_C;
        local_28->unk_97C = l10->get_unk_24();
        local_28->unk_974 = 0.0f;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5B800 @ 0x0005B800
// sp-match: sub_5B800 @ 0x000566C0
void type_3DDB98::sub_5B800(RwReal arg_0)
{
    unk_738 = arg_0;
    sub_22C20(unk_738, 0.0f, 1.0f);
}

// match: sub_5B850 @ 0x0005B850
// sp-match: sub_5B850 @ 0x00056700
void type_3DAC58::sub_5B850(RwReal arg_0)
{
    unk_3C0 = arg_0;
    sub_22C20(unk_3C0, 0.0f, 1.0f);
}

// match: sub_5B8A0 @ 0x0005B8A0
// sp-match: sub_5B8A0 @ 0x00057890
// "SetSplineEndPosition": the end arg 1 (0 to 1) of the spline path of the
// object's entity (kind 2): its AI object's, or a type_3DA6C0's,
// type_3DDB98's or type_3DAC58's.
void sub_5B8A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DAC58 *var_1C;
    type_3DDB98 *var18;
    type_3DA6C0 *stk_14;
    RwReal l10;
    type_67620 *local_C;
    type_3D3548 *lv_8;
    AIData *var_4;

    local_C = sub_67620(arg_0);
    SCRIPT_CHECK(local_C->vf_024() != 0);
    SCRIPT_CHECK(local_C->vf_024()->get_unk_14() == 2);
    lv_8 = local_C->vf_024()->get_unk_10();
    SCRIPT_CHECK(lv_8 != 0);
    l10 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = lv_8->vf_120();
    if (var_4 != 0)
        var_4->set_unk_D1C(l10);
    else if (lv_8->vf_01C() != 0) {
        stk_14 = (type_3DA6C0 *)lv_8;
        stk_14->set_unk_444(l10);
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_3DDB98 *)lv_8;
        var18->set_unk_738(l10);
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_3DAC58 *)lv_8;
        var_1C->set_unk_3C0(l10);
    }
    sub_44350(arg_4, 0);
}

// match: sub_5BAA0 @ 0x0005BAA0
// sp-match: sub_5BAA0 @ 0x00049C10
// "GetClosestPositionOnSpline": the position on the spline path of the
// object's entity (kind 2; its AI object's, else its own) closest to the
// entity (sub_BA450, with 100 and 1).
void sub_5BAA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_10;
    type_67620 *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    ebp_C = sub_67620(arg_0);
    SCRIPT_CHECK(ebp_C->vf_024() != 0);
    SCRIPT_CHECK(ebp_C->vf_024()->get_unk_14() == 2);
    v8 = ebp_C->vf_024()->get_unk_10();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    if (var_4 != 0) {
        SCRIPT_CHECK(var_4 != 0);
        SCRIPT_CHECK(var_4->get_unk_D14() != 0);
        var_10 = var_4->get_unk_D14()->sub_BA450(v8->sub_CD550(), 100.0f, 1.0f);
    } else {
        // This check reserves no slots.
        sub_44220(v8->vf_0F4() != 0);
        var_10 = v8->vf_0F4()->sub_BA450(v8->sub_CD550(), 100.0f, 1.0f);
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_5BBF0 @ 0x0005BBF0
// sp-match: sub_5BBF0 @ 0x00049E10
// "GetClosestPositionFromPlayerOnSpline": as "GetClosestPositionOnSpline",
// closest to player 0 (vf_0CC).
void sub_5BBF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal l14;
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->get_unk_D14() != 0);
    v8 = sub_1745A0(0);
    // This check and the ones below reserve no slots.
    sub_44220(v8 != 0);
    if (var_4 != 0) {
        sub_44220(var_4 != 0);
        sub_44220(var_4->get_unk_D14() != 0);
        l14 = var_4->get_unk_D14()->sub_BA450(v8->vf_0CC(), 100.0f, 1.0f);
    } else {
        sub_44220(ebp_C->vf_0F4() != 0);
        l14 = ebp_C->vf_0F4()->sub_BA450(v8->vf_0CC(), 100.0f, 1.0f);
    }
    sub_44350(arg_4, &l14);
}

// match: sub_5BDA0 @ 0x0005BDA0
// sp-match: sub_5BDA0 @ 0x0004A070
// "GetSplineLength": the length of the spline path of the object's entity
// (kind 2; its AI object's, else its own).
void sub_5BDA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    RwReal v8;
    AIData *var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = 0.0f;
    var_4 = ebp_C->vf_120();
    if (var_4 != 0) {
        SCRIPT_CHECK(var_4 != 0);
        SCRIPT_CHECK(var_4->get_unk_D14() != 0);
        v8 = var_4->get_unk_D14()->unk_24;
    } else {
        // This check reserves no slots.
        sub_44220(ebp_C->vf_0F4() != 0);
        v8 = ebp_C->vf_0F4()->unk_24;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_5BED0 @ 0x0005BED0
// sp-match: sub_5BED0 @ 0x0004A250
// "GetSplinePositionX": the x of the point at arg 1 along the spline path of
// the object's entity (kind 2; its AI object's, else its own).
void sub_5BED0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_1C;
    type_3D3548 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_1C = sub_67620(arg_0);
    SCRIPT_CHECK(var_1C->vf_024() != 0);
    SCRIPT_CHECK(var_1C->vf_024()->get_unk_14() == 2);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_18 = var_1C->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_18 != 0);
    lv_8 = local_18->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        SCRIPT_CHECK(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        // This check reserves no slots.
        sub_44220(local_18->vf_0F4() != 0);
        RpSplineFindPosition(local_18->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.x);
}

// match: sub_5C040 @ 0x0005C040
// sp-match: sub_5C040 @ 0x0004A460
// "GetSplinePositionY": the y of the point at arg 1 along the spline path of
// the object's entity (kind 2; its AI object's, else its own).
void sub_5C040(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_1C;
    type_3D3548 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_1C = sub_67620(arg_0);
    SCRIPT_CHECK(var_1C->vf_024() != 0);
    SCRIPT_CHECK(var_1C->vf_024()->get_unk_14() == 2);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_18 = var_1C->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_18 != 0);
    lv_8 = local_18->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        SCRIPT_CHECK(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        // This check reserves no slots.
        sub_44220(local_18->vf_0F4() != 0);
        RpSplineFindPosition(local_18->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.y);
}

// match: sub_5C1B0 @ 0x0005C1B0
// sp-match: sub_5C1B0 @ 0x0004A670
// "GetSplinePositionZ": the z of the point at arg 1 along the spline path of
// the object's entity (kind 2; its AI object's, else its own).
void sub_5C1B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_1C;
    type_3D3548 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_1C = sub_67620(arg_0);
    SCRIPT_CHECK(var_1C->vf_024() != 0);
    SCRIPT_CHECK(var_1C->vf_024()->get_unk_14() == 2);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_18 = var_1C->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_18 != 0);
    lv_8 = local_18->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        SCRIPT_CHECK(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        // This check reserves no slots.
        sub_44220(local_18->vf_0F4() != 0);
        RpSplineFindPosition(local_18->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.z);
}

// match: sub_5C320 @ 0x0005C320
// sp-match: sub_5C320 @ 0x0004A880
// "GetSplinePositionXFromName": as "GetSplinePositionX", for the entity of
// the kind-0x2E object under the key arg 1 (two slots), at arg 2.
void sub_5C320(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *local_24;
    type_3DF8D8_04 *local_20;
    type_3D3548 *var_1C;
    type_3DF8D8 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C = 0;
    local_20 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_20 != 0);
    local_18 = sub_198800(local_20);
    SCRIPT_CHECK(local_18 != 0);
    if (local_18 != 0 && local_18->vf_008() == 0x2E) {
        local_24 = (type_3DFEEC *)local_18;
        SCRIPT_CHECK(local_24->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&local_24->unk_24_id)->sub_D4910() != 0);
        var_1C = ((type_D48D0 *)&local_24->unk_24_id)->sub_D4910();
    } else
        sub_44220(0);
    lv_8 = var_1C->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        // This check and the one below reserve no slots.
        sub_44220(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        sub_44220(var_1C->vf_0F4() != 0);
        RpSplineFindPosition(var_1C->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.x);
}

// match: sub_5C4F0 @ 0x0005C4F0
// sp-match: sub_5C4F0 @ 0x0004AAD0
// "GetSplinePositionYFromName": as "GetSplinePositionY", for the entity of
// the kind-0x2E object under the key arg 1 (two slots), at arg 2.
void sub_5C4F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *local_24;
    type_3DF8D8_04 *local_20;
    type_3D3548 *var_1C;
    type_3DF8D8 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C = 0;
    local_20 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_20 != 0);
    local_18 = sub_198800(local_20);
    SCRIPT_CHECK(local_18 != 0);
    if (local_18 != 0 && local_18->vf_008() == 0x2E) {
        local_24 = (type_3DFEEC *)local_18;
        SCRIPT_CHECK(local_24->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&local_24->unk_24_id)->sub_D4910() != 0);
        var_1C = ((type_D48D0 *)&local_24->unk_24_id)->sub_D4910();
    } else
        sub_44220(0);
    lv_8 = var_1C->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        // This check and the one below reserve no slots.
        sub_44220(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        sub_44220(var_1C->vf_0F4() != 0);
        RpSplineFindPosition(var_1C->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.y);
}

// match: sub_5C6C0 @ 0x0005C6C0
// sp-match: sub_5C6C0 @ 0x0004AD20
// "GetSplinePositionZFromName": as "GetSplinePositionZ", for the entity of
// the kind-0x2E object under the key arg 1 (two slots), at arg 2.
void sub_5C6C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *local_24;
    type_3DF8D8_04 *local_20;
    type_3D3548 *var_1C;
    type_3DF8D8 *local_18;
    RwV3d local_14;
    AIData *lv_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C = 0;
    local_20 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_20 != 0);
    local_18 = sub_198800(local_20);
    SCRIPT_CHECK(local_18 != 0);
    if (local_18 != 0 && local_18->vf_008() == 0x2E) {
        local_24 = (type_3DFEEC *)local_18;
        SCRIPT_CHECK(local_24->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&local_24->unk_24_id)->sub_D4910() != 0);
        var_1C = ((type_D48D0 *)&local_24->unk_24_id)->sub_D4910();
    } else
        sub_44220(0);
    lv_8 = var_1C->vf_120();
    if (lv_8 != 0) {
        SCRIPT_CHECK(lv_8 != 0);
        // This check and the one below reserve no slots.
        sub_44220(lv_8->get_unk_D14() != 0);
        RpSplineFindPosition(lv_8->get_unk_D14()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    } else {
        sub_44220(var_1C->vf_0F4() != 0);
        RpSplineFindPosition(var_1C->vf_0F4()->unk_28, rpSPLINEPATHSMOOTH, var_4, &local_14, 0);
    }
    sub_44350(arg_4, &local_14.z);
}

// match: sub_5C890 @ 0x0005C890
// sp-match: sub_5C890 @ 0x0004AF70
// "SetSplinePosition": the position arg 1 on the spline path of the
// object's entity (kind 2; its AI object's, else its own, vf_0F8).
void sub_5C890(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_10;
    type_3D3548 *ebp_C;
    AIData *v8;
    RwReal var_4;

    var_10 = sub_67620(arg_0);
    SCRIPT_CHECK(var_10->vf_024() != 0);
    SCRIPT_CHECK(var_10->vf_024()->get_unk_14() == 2);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    ebp_C = var_10->vf_024()->get_unk_10();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_120();
    if (v8 != 0) {
        SCRIPT_CHECK(v8 != 0);
        SCRIPT_CHECK(v8->get_unk_D14() != 0);
        v8->unk_D18 = var_4;
    } else
        ebp_C->vf_0F8(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_5C9B0 @ 0x0005C9B0
// sp-match: sub_5C9B0 @ 0x0004B0F0
// "GetSplinePositionFromName": the position on its AI object's spline path
// of the entity of the kind-0x2E object under the key arg 1 (two slots), or
// 0.
void sub_5C9B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *stk_18;
    type_3DF8D8_04 *l14;
    type_3D3548 *var_10;
    type_3DF8D8 *ebp_C;
    AIData *v8;
    RwReal var_4;

    var_4 = 0.0f;
    var_10 = 0;
    l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(l14 != 0);
    ebp_C = sub_198800(l14);
    SCRIPT_CHECK(ebp_C != 0);
    if (ebp_C != 0 && ebp_C->vf_008() == 0x2E) {
        stk_18 = (type_3DFEEC *)ebp_C;
        SCRIPT_CHECK(stk_18->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&stk_18->unk_24_id)->sub_D4910() != 0);
        var_10 = ((type_D48D0 *)&stk_18->unk_24_id)->sub_D4910();
    } else
        sub_44220(0);
    v8 = var_10->vf_120();
    if (v8 != 0) {
        SCRIPT_CHECK(v8 != 0);
        // This check reserves no slots.
        sub_44220(v8->get_unk_D14() != 0);
        var_4 = v8->get_unk_D18();
    } else
        var_4 = 0.0f;
    sub_44350(arg_4, &var_4);
}

// match: sub_5CB00 @ 0x0005CB00
// sp-match: sub_5CB00 @ 0x0004B2C0
// "SetSplineIncrement": the spline increment arg 1 of the object's entity
// (kind 2).
void sub_5CB00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_3D3548 *local_8;
    RwReal var_4;

    varC = sub_67620(arg_0);
    SCRIPT_CHECK(varC->vf_024() != 0);
    SCRIPT_CHECK(varC->vf_024()->get_unk_14() == 2);
    local_8 = varC->vf_024()->get_unk_10();
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8->vf_124(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_5CBD0 @ 0x0005CBD0
// sp-match: sub_5CBD0 @ 0x0004B3E0
// "GetSplineIncrement": the spline increment of the object's entity (kind
// 2).
void sub_5CBD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    varC = var_4->vf_128();
    sub_44350(arg_4, &varC);
}

// match: sub_5CC80 @ 0x0005CC80
// sp-match: sub_5CC80 @ 0x0004B510
// "GetSplineIncrementFromName": the spline increment of the entity (a
// type_3DA6C0) of the kind-0x2E object under the key arg 1 (two slots).
void sub_5CC80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *l14;
    type_3DF8D8_04 *var_10;
    type_3DA6C0 *ebp_C;
    type_3DF8D8 *v8;
    RwReal var_4;

    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_10 != 0);
    v8 = sub_198800(var_10);
    SCRIPT_CHECK(v8 != 0);
    ebp_C = 0;
    if (v8 != 0 && v8->vf_008() == 0x2E) {
        l14 = (type_3DFEEC *)v8;
        SCRIPT_CHECK(l14->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&l14->unk_24_id)->sub_D4910() != 0);
        SCRIPT_CHECK(((type_D48D0 *)&l14->unk_24_id)->sub_D4910()->vf_01C() != 0);
        ebp_C = ((type_D48D0 *)&l14->unk_24_id)->sub_D4910()->vf_01C();
    } else
        sub_44220(0);
    // This check reserves no slots.
    sub_44220(ebp_C != 0);
    var_4 = ebp_C->vf_128();
    sub_44350(arg_4, &var_4);
}

// match: sub_5CDC0 @ 0x0005CDC0
// sp-match: sub_5CDC0 @ 0x0004B6F0
// "SetSplineMovementByAnimation": whether the object's entity (kind 2)
// moves along its spline by its animation (arg 1).
void sub_5CDC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4->vf_12C(varC);
    sub_44350(arg_4, 0);
}

// match: sub_5CE90 @ 0x0005CE90
// sp-match: sub_5CE90 @ 0x0004B810
// "SetSplineGoodToGo": whether the object's entity (kind 2), a type_3DDB98, may go along its spline
// (arg 1).
void sub_5CE90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    if (var_4->vf_024() != 0)
        ((type_3DDB98 *)var_4)->vf_234(varC);
    sub_44350(arg_4, 0);
}

// match: sub_5CF70 @ 0x0005CF70
// sp-match: sub_5CF70 @ 0x0004B940
// "SetPointGoodToGo": whether the object's entity (kind 2), a type_3DDB98, may go to its point
// (arg 1).
void sub_5CF70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    SCRIPT_CHECK(local_8->vf_024() != 0);
    SCRIPT_CHECK(local_8->vf_024()->get_unk_14() == 2);
    var_4 = local_8->vf_024()->get_unk_10();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    if (var_4->vf_024() != 0)
        ((type_3DDB98 *)var_4)->vf_238(varC);
    sub_44350(arg_4, 0);
}

// match: sub_5D050 @ 0x0005D050
// sp-match: sub_5D050 @ 0x0004BA70
// "GetTransitionDistance": how far the soldier's scene transition for the
// words (arg 2, arg 1) and the key byte arg 3 carries it: the performance
// set sub_EE360 picks is walked clip by clip, each clip's start offset
// (event 3) turned by the rotation so far and added up, and each clip's
// start rotation (event 4) composed on. The length of the offset plus 33,
// 0 when a clip lacks its events, 300 when the scene map has no entry.
// The frame holds six unused locals beyond the checks' five each
// (SCRIPT_CHECK2); the first check is given them, since unused slots leave
// no trace of which check had them.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_5D050(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d frm_A8;
    RwV3d ebp_9C;
    RtQuat q90;
    RtQuat r80;
#ifndef CODFH_SP
    RwInt32 s70;
    RwInt32 m_6C;
    RwInt32 q68;
    RwV3d var_64;
    RtQuat slot_58;
    RwInt32 w48;
#endif
    RwInt8 fp_41;
    type_EDA50_item *fp_40;
    type_3DAFC8 *ebp_3C;
    type_4B9304 *lcl_38;
    type_67620 *r34;
    type_5D4B0_2C lv_30;
    RwUInt8 *frm_24;
    RwInt8 m_1D;
    RwInt16 l1C;
    type_ED850 *m_18;
    type_3D3548 *ebp_14;
    RwInt16 lv_10;
    RwReal slot_C;
    RwInt32 bp_8;
    RwInt32 bp_4;

    slot_C = 300.0f;
    bp_8 = SCRIPT_ARG(arg_4, 1);
    bp_4 = SCRIPT_ARG(arg_4, 2);
    m_1D = SCRIPT_ARGT<RwInt8>(arg_4, 3);
    ebp_14 = sub_45170(arg_0);
    SCRIPT_CHECK2(ebp_14 != 0);
    frm_24 = ebp_14->vf_0E0();
    SCRIPT_CHECK(frm_24 != 0);
    lv_30 = *(type_5D4B0_2C *)frm_24;
    lv_30.unk_00 = (RwInt16)bp_4;
    lv_30.unk_02 = (RwInt16)bp_8;
    m_18 = dword_4B9300;
    SCRIPT_CHECK(m_18 != 0);
    l1C = 0;
    lv_10 = m_18->sub_ED850((RwUInt8 *)&lv_30, &l1C);
    if (l1C < 0)
        l1C = (RwInt16)ebp_14->vf_0AC();
    if (lv_10 == -1) {
        r34 = sub_67620(arg_0);
        sub_6B060(r34, "No matching Scene found!", 0);
        slot_C = 300.0f;
    } else {
        SCRIPT_CHECK(ebp_14->unk_2C_5);
        ebp_3C = static_cast<type_3DAFC8 *>(ebp_14);
        fp_41 = (RwInt8)ebp_3C->unk_3E0.sub_15F0A0();
        lcl_38 = dword_4B9304;
        fp_40 = (type_EDA50_item *)lcl_38->sub_EE360(m_1D, fp_41, (RwInt8)l1C);
        if (fp_40 != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 lays out the frame as SP 0x4BA70 does
            RwInt32 s70;
            RwInt32 m_6C;
            RwInt32 q68;
            RwV3d var_64;
            RtQuat slot_58;
            RwInt32 w48;

#endif
            w48 = 1;
            var_64.x = 0.0f;
            var_64.y = 0.0f;
            var_64.z = 0.0f;
            slot_58.imag.x = 0.0f;
            slot_58.imag.y = 0.0f;
            slot_58.imag.z = 0.0f;
            slot_58.real = 1.0f;
            for (q68 = 0; q68 < fp_40->unk_00; q68++) {
                if (sub_77B70(fp_40->unk_04[q68], (void **)(&s70), (void **)(&m_6C)) != 0
                    && ((type_783F0 *)m_6C)->sub_78550(0.0f, 3) != 0) {
                    frm_A8 = ((type_783F0 *)m_6C)->sub_78550(0.0f, 3)->unk_08_v;
                    r80 = ((type_783F0 *)m_6C)->sub_78550(0.0f, 4)->unk_08_q;
                    RtQuatTransformVectors(&ebp_9C, &frm_A8, 1, &slot_58);
                    RtQuatMultiplyMacro(&q90, &slot_58, &r80);
                    RwV3dAdd(&var_64, &var_64, &ebp_9C);
                    slot_58 = q90;
                } else
                    w48 = 0;
            }
            if (w48 != 0) {
                slot_C = RwV3dLength((RwV3d *)&var_64);
                if (slot_C > 0.0f)
                    slot_C = slot_C + 33.0f;
            } else
                slot_C = 0.0f;
        }
    }
    sub_44350(arg_4, &slot_C);
}

// match: sub_5D4B0 @ 0x0005D4B0
// sp-match: sub_5D4B0 @ 0x0004BF10
// "DoesSceneHaveTranstion": whether the scene performance the entity's
// scene map entry (vf_0E0) finds for the words (arg 2, arg 1) has a
// transition (sub_6CF50) with the entity's performance values.
void sub_5D4B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_6D380 *slot_44;
#ifndef CODFH_SP
    type_46840_30 l40;
#endif
    RwInt32 ebp_34;
    RwInt8 *var_30;
    type_5D4B0_2C bp_2C;
    RwUInt8 *local_20;
    RwInt16 var_1C;
    type_ED850 *var18;
    type_3D3548 *stk_14;
    RwInt16 l10;
    RwInt32 local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    stk_14 = sub_45170(arg_0);
    SCRIPT_CHECK(stk_14 != 0);
    local_C = SCRIPT_ARG(arg_4, 1);
    lv_8 = SCRIPT_ARG(arg_4, 2);
    local_20 = stk_14->vf_0E0();
    SCRIPT_CHECK(local_20 != 0);
    bp_2C = *(type_5D4B0_2C *)local_20;
    bp_2C.unk_00 = (RwInt16)lv_8;
    bp_2C.unk_02 = (RwInt16)local_C;
    var18 = dword_4B9300;
    SCRIPT_CHECK(var18 != 0);
    var_4 = 0;
    l10 = var18->sub_ED850((RwUInt8 *)&bp_2C, &var_1C);
    if (l10 != -1) {
        var_30 = (RwInt8 *)stk_14->vf_08C(1, 0);
        if (var_30 != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules its copy as SP 0x4BF10 does
            type_46840_30 l40 = *(type_46840_30 *)var_30;
#else
            l40 = *(type_46840_30 *)var_30;
#endif
            if (var_1C >= 0)
                l40.unk_00[2] = (RwInt8)var_1C;
            slot_44 = stk_14->vf_090();
            SCRIPT_CHECK(slot_44 != 0);
            ebp_34 = ((type_3D2CD0 *)slot_44)->sub_6CF50(l10, (type_6CF50_04 *)l40.unk_00, 0);
            if (ebp_34 != 0)
                var_4 = 1;
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_5D650 @ 0x0005D650
// sp-match: sub_5D650 @ 0x0004C110
// "DoesNameHaveOrientation": whether the object under the key arg 1 (two
// slots; kind 0x2C to 0x2E) has a direction (vf_010).
void sub_5D650(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFED8 *stk_18;
    type_3DF8D8_04 *l14;
    type_3DF8D8 *var_10;
    RwInt32 ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = sub_198800(l14);
    var_4 = 0;
    v8 = var_10->vf_008();
    ebp_C = var_10 != 0 && (v8 == 0x2E || v8 == 0x2D || v8 == 0x2C);
    if (ebp_C != 0) {
        stk_18 = (type_3DFED8 *)var_10;
        if (stk_18->vf_010() != 0)
            var_4 = 1;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_5D710 @ 0x0005D710
// sp-match: sub_5D710 @ 0x0004C1A0
// "GetLastPerformanceTypePlayed": the type of the entity's last
// performance.
void sub_5D710(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_6D380 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    varC = local_8->vf_090();
    SCRIPT_CHECK(varC != 0);
    var_4 = varC->get_unk_144();
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_5D780 @ 0x0005D780
// sp-match: sub_5D780 @ 0x0004C280
// "RestartLevel": sets bit 3 of dword_4B86F8.
void sub_5D780(RwUInt32 arg_0, type_44350 *arg_4)
{
    dword_4B86F8 |= 8;
    sub_44350(arg_4, 0);
}

// match: sub_5D7A0 @ 0x0005D7A0
// sp-match: sub_5D7A0 @ 0x0004C2B0
// "QuitLevel".
void sub_5D7A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_D8C20();
    sub_44350(arg_4, 0);
}

// match: sub_5D7C0 @ 0x0005D7C0
// sp-match: sub_5D7C0 @ 0x0004C2D0
// "GetGameFrame": the frame number dword_4B87D8.
void sub_5D7C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 var_4;

    var_4 = dword_4B87D8;
    sub_44350(arg_4, &var_4);
}

// match: sub_5D7E0 @ 0x0005D7E0
// sp-match: sub_5D7E0 @ 0x0004C320
// "QuitAndLoadNextLevel": quits and loads level arg 1 (1 to 8).
void sub_5D7E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
#ifdef CODFH_SP // single player has levels 1 to 38 (SP 0x4C320)
    SCRIPT_CHECK(var_4 > 0 && var_4 < 0x27);
#else
    SCRIPT_CHECK(var_4 > 0 && var_4 < 9);
#endif
    sub_D8CC0(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_5D850 @ 0x0005D850
// sp-match: sub_5D850 @ 0x0004C3A0
// "EnableEndLevelTrigger": enables the object's end-level trigger (kind
// 0x24) with arg 1.
void sub_5D850(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *var_10;
    type_712B0 *ebp_C;
    type_67620 *v8;
    RwInt32 var_4;

    v8 = sub_67620(arg_0);
    SCRIPT_CHECK(v8->vf_024() != 0);
    ebp_C = v8->vf_024()->sub_712B0();
    SCRIPT_CHECK(ebp_C != 0);
    SCRIPT_CHECK(ebp_C->vf_008() == 0x24);
    var_4 = SCRIPT_ARG(arg_4, 1);
    if (ebp_C->vf_008() == 0x24) {
        var_10 = ebp_C;
        ((EndLevelTrigger *)var_10)->sub_CC2A0(var_4);
    }
    sub_44350(arg_4, 0);
}

// match: sub_5D920 @ 0x0005D920
// sp-match: sub_5D920 @ 0x0004C4D0
// "DisableNamedCoverPoint": disables the cover node of the kind-0x2E object (flags 0x10) under
// the key arg 1 (two slots), which must be a cover kind (as
// "SetCoverPointFromName"), through sub_F7BA0.
void sub_5D920(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *varC;
    type_3DF8D8 *local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = sub_198800(var_4);
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK(local_8->vf_008() == 0x2E);
    varC = (type_3DFEEC *)local_8;
    SCRIPT_CHECK(varC->unk_10 == 0x10);
    SCRIPT_CHECK(((varC->get_unk_24_node()->unk_00 >> 1) & 1)
                 || ((varC->get_unk_24_node()->unk_00 >> 6) & 1)
                 || varC->get_unk_24_node()->unk_04 == 3
                 || varC->get_unk_24_node()->unk_04 == 4
                 || varC->get_unk_24_node()->unk_04 == 5
                 || varC->get_unk_24_node()->unk_04 == 9
                 || varC->get_unk_24_node()->unk_04 == 0xB
                 || varC->get_unk_24_node()->unk_04 == 0x13
                 || varC->get_unk_24_node()->unk_04 == 0xC
                 || varC->get_unk_24_node()->unk_04 == 0xE
                 || varC->get_unk_24_node()->unk_04 == 0xD
                 || varC->get_unk_24_node()->unk_04 == 0x11);
    sub_F7BA0(0, varC->get_unk_24_node(), 1);
    sub_44350(arg_4, 0);
}

// match: sub_5DB10 @ 0x0005DB10
// sp-match: sub_5DB10 @ 0x0004C660
// "EnableNamedCoverPoint": enables the cover node of the kind-0x2E object (flags 0x10) under
// the key arg 1 (two slots), which must be a cover kind (as
// "SetCoverPointFromName"), through sub_F7BA0.
void sub_5DB10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *varC;
    type_3DF8D8 *local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = sub_198800(var_4);
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK(local_8->vf_008() == 0x2E);
    varC = (type_3DFEEC *)local_8;
    SCRIPT_CHECK(varC->unk_10 == 0x10);
    SCRIPT_CHECK(((varC->get_unk_24_node()->unk_00 >> 1) & 1)
                 || ((varC->get_unk_24_node()->unk_00 >> 6) & 1)
                 || varC->get_unk_24_node()->unk_04 == 3
                 || varC->get_unk_24_node()->unk_04 == 4
                 || varC->get_unk_24_node()->unk_04 == 5
                 || varC->get_unk_24_node()->unk_04 == 9
                 || varC->get_unk_24_node()->unk_04 == 0xB
                 || varC->get_unk_24_node()->unk_04 == 0x13
                 || varC->get_unk_24_node()->unk_04 == 0xC
                 || varC->get_unk_24_node()->unk_04 == 0xE
                 || varC->get_unk_24_node()->unk_04 == 0xD
                 || varC->get_unk_24_node()->unk_04 == 0x11);
    sub_F7BA0(0, varC->get_unk_24_node(), 0);
    sub_44350(arg_4, 0);
}

// match: sub_5DD00 @ 0x0005DD00
// sp-match: sub_5DD00 @ 0x0004C7F0
// "EnableNamedPathNode": a door node's state (flag 7) of the path node the
// kind-0x2E object of kind 0x10 under the key arg 1 (two slots) holds: set
// when arg 2 is 0.
void sub_5DD00(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3DFEEC *ebp_C;
    type_3DF8D8 *v8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    v8 = sub_198800(var_4);
    SCRIPT_CHECK(v8 != 0);
    SCRIPT_CHECK(v8->vf_008() == 0x2E);
    ebp_C = (type_3DFEEC *)v8;
    SCRIPT_CHECK(ebp_C->unk_10 == 0x10);
    ebp_C->get_unk_24_node()->unk_00_7 = var_10 == 0;
    sub_44350(arg_4, 0);
}

// match: sub_5DDF0 @ 0x0005DDF0
// sp-match: sub_5DDF0 @ 0x0004C920
// "IsWithinDefendArea": whether the entity lies within its AI object's
// defend area (flag 13; sub_205E0).
void sub_5DDF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    varC = 0;
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK((var_4->unk_49C & 0x2000) != 0);
    if (var_4->sub_205E0(local_8->sub_CD550(), 0.0f))
        varC = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &varC);
}

// match: sub_5DE90 @ 0x0005DE90
// sp-match: sub_5DE90 @ 0x0004CA60
// "IsPointWithinDefendArea": whether (arg 1, arg 2, arg 3) lies within the
// entity's AI object's defend area (flag 13; sub_205E0).
void sub_5DE90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 stk_18;
    type_3D3548 *l14;
    AIData *var_10;
    RwV3d var_C;

    stk_18 = 0;
    l14 = sub_45170(arg_0);
    SCRIPT_CHECK(l14 != 0);
    var_10 = l14->vf_120();
    SCRIPT_CHECK(var_10 != 0);
    SCRIPT_CHECK((var_10->unk_49C & 0x2000) != 0);
    var_C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    if (var_10->sub_205E0(&var_C, 0.0f))
        stk_18 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &stk_18);
}

// match: sub_5DFA0 @ 0x0005DFA0
// sp-match: sub_5DFA0 @ 0x0004CBE0
// "IsTargetWithinDefendArea": whether the entity's AI object's tracked
// entity (a player at its eye height less unk_1A00) lies within its defend
// area (flag 13) widened by 150 and arg 1 (sub_20670).
void sub_5DFA0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwV3d ebp_20;
#endif
    RwInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    var_10 = 0;
    l14 = SCRIPT_ARG(arg_4, 1);
    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK((var_4->unk_49C & 0x2000) != 0);
    ebp_C = var_4->unk_1374.sub_D4910();
    if (ebp_C != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 schedules its copy as SP 0x4CBE0 does
        RwV3d ebp_20 = *ebp_C->sub_CD550();
#else
        ebp_20 = *ebp_C->sub_CD550();
#endif
        if (ebp_C->vf_00C() != 0)
            ebp_20.y -= ebp_C->vf_00C()->unk_1A00;
        if (var_4->sub_20670(&ebp_20, 150.0f, 150.0f, 0.0f, l14))
            var_10 = 1;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_5E0D0 @ 0x0005E0D0
// sp-match: sub_5E0D0 @ 0x0004CD90
// "SetupDefendAreaGotoPoint": the entity's AI object's defend area (flag 13) centre
// (unk_13A8) becomes its target point (unk_5B0).
void sub_5E0D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK((var_4->unk_49C & 0x2000) != 0);
    SCRIPT_CHECK(varC = &var_4->unk_13A8);
    var_4->unk_5B0 = *varC;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E180 @ 0x0005E180
// sp-match: sub_5E180 @ 0x0004CEE0
// "SetupDefendAreaAnchorPosGotoPoint": the entity's AI object's defend area (flag 13) anchor position
// (unk_13D0) becomes its target point (unk_5B0).
void sub_5E180(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK((var_4->unk_49C & 0x2000) != 0);
    SCRIPT_CHECK(varC = &var_4->unk_13D0);
    var_4->unk_5B0 = *varC;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E230 @ 0x0005E230
// sp-match: sub_5E230 @ 0x0004D030
// "SetDefendArea": the entity's AI object defends the object under the key
// arg 1 (two slots) within arg 2 (sub_1FF10).
void sub_5E230(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_4->sub_1FF10(var_10, ebp_C, 0.0f, 0.0f);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E2F0 @ 0x0005E2F0
// sp-match: sub_5E2F0 @ 0x0004D110
// "SetDefendAreaCurrentPosition": the entity's AI object defends its
// current point (vf_0CC) within arg 1 (sub_20370).
void sub_5E2F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10 = v8->vf_0CC();
    var_4->sub_20370(var_10, ebp_C, 0.0f, 0.0f);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E3A0 @ 0x0005E3A0
// sp-match: sub_5E3A0 @ 0x0004D200
// "SetDefendAreaCylinder": as "SetDefendArea", a cylinder of radius arg 2
// and heights arg 3 and arg 4.
void sub_5E3A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal stk_18;
    RwReal l14;
    type_3DF8D8_04 *var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 2);
    l14 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    stk_18 = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_4->sub_1FF10(var_10, ebp_C, l14, stk_18);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E4B0 @ 0x0005E4B0
// sp-match: sub_5E4B0 @ 0x0004D2F0
// "SetDefendAreaCylinderCurrentPosition": as
// "SetDefendAreaCurrentPosition", a cylinder of radius arg 1 and heights
// arg 2 and arg 3.
void sub_5E4B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *stk_18;
    RwReal l14;
    RwReal var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    ebp_C = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    l14 = SCRIPT_ARGT<RwReal>(arg_4, 3);
    stk_18 = v8->vf_0CC();
    var_4->sub_20370(stk_18, ebp_C, var_10, l14);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E5B0 @ 0x0005E5B0
// sp-match: sub_5E5B0 @ 0x0004D400
// "ClearDefendArea": clears the entity's AI object's defend area
// (sub_204E0).
void sub_5E5B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_204E0();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_5E610 @ 0x0005E610
// sp-match: sub_5E610 @ 0x0004D4C0
// "GetDefendAreaRadius": the radius of the entity's AI object's defend area
// (flag 13).
void sub_5E610(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwReal local_8;
    AIData *var_4;

    varC = sub_45170(arg_0);
    SCRIPT_CHECK(varC != 0);
    var_4 = varC->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK((var_4->unk_49C & 0x2000) != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    local_8 = var_4->get_unk_13B4();
    sub_44350(arg_4, &local_8);
}

// match: sub_5E6A0 @ 0x0005E6A0
// sp-match: sub_5E6A0 @ 0x0004D5F0
// "StartPrimedAudioStream": starts the primed stream of voice type arg 1
// (0 to 2; state 0xC), formatting a complaint no one sees first.
void sub_5E6A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    sprintf(Buffer, "StartPrimedAudioStream: Invalid Stream Voice Type :%d", var_4);
    SCRIPT_CHECK(var_4 >= 0 && var_4 < 3);
    dword_44E8D8[var_4].unk_180 = 0xC;
    sub_44350(arg_4, 0);
}

// match: sub_5E730 @ 0x0005E730
// sp-match: sub_5E730 @ 0x0004D690
// "PrimeAudioStream": primes the stream alias (kind 0x2A) under the key
// arg 1 (two slots) for its voice type (0 to 2), formatting each complaint
// no one sees before its check.
void sub_5E730(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_10;
    type_3DF8D8 *ebp_C;
    RwInt32 v8;
    type_5E730 *var_4;

    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_10 != 0);
    ebp_C = sub_198800(var_10);
    sprintf(Buffer, "PrimeAudioStream: God Asset 0x%x, 0x%x is not valid!", var_10->unk_00,
            var_10->unk_04);
    SCRIPT_CHECK(ebp_C != 0);
    sprintf(Buffer, "PrimeAudioStream: Alias 0x%x, 0x%x is not a Stream Alias!!!", var_10->unk_00,
            var_10->unk_04);
    SCRIPT_CHECK(ebp_C->vf_008() == 0x2A);
    var_4 = (type_5E730 *)ebp_C;
    v8 = var_4->unk_20;
    sprintf(Buffer, "PrimeAudioStream:Invalid Voice Type!! Alias 0x%x,0x%x", var_10->unk_00,
            var_10->unk_04);
    SCRIPT_CHECK(v8 < 3 && v8 >= 0);
    dword_44E8D8[v8].unk_244 = 1;
    dword_4B1E98.sub_8A980(var_10, 0, 0, 0, 0, 0);
    sub_44350(arg_4, 0);
}

// match: sub_5E880 @ 0x0005E880
// sp-match: sub_5E880 @ 0x0004D840
// "EfuncPlaySound": plays the sound alias (kind 0x19, 0x1B, 0x1C, 0x1E or
// 0x2A) under the key arg 1 (two slots) with arg 3, from the entity (arg 2
// = 0), player 0 (1) or nowhere (2) at its position; returns its id, or 0.
// Its complaints go to a local buffer no one reads.
void sub_5E880(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l120;
    type_3D3548 *var11C;
    RwInt32 v118;
    RwInt32 v114;
    RwInt32 v110;
    type_3DF8D8 *var_10C;
    RwChar local_108[0x100];
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10C = sub_198800(var_4);
    v110 = 0;
    if (var_10C == 0) {
        {
            // Two locals the image reserves and never uses.
            RwInt32 unused_1;
            RwInt32 unused_0;
        }
        if (dword_44E860 != 0 && dword_44E86C != 0)
            sprintf(local_108, "EfuncPlaySound: Error! This Sound Alias is not Loaded! 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
    } else {
        v118 = var_10C->vf_008();
        if (v118 != 0x19 && v118 != 0x1B && v118 != 0x1E && v118 != 0x2A
            && v118 != 0x1C)
            sprintf(local_108,
                    "EfuncPlaySound: Error! This God ID is not for a Sound Alias! (Don't forget "
                    "to use EfuncPlayIndexSound or EfuncPlayIndexSoundOnNamedEntity for index "
                    "aliases!) 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
        l120 = SCRIPT_ARG(arg_4, 2);
        v114 = SCRIPT_ARG(arg_4, 3);
        var11C = 0;
        sub_19A750(0, 1, *var_4, 2);
        if (l120 == 0) {
            var11C = sub_45170(arg_0);
            SCRIPT_CHECK(var11C != 0);
            v110 = var11C->unk_1C0.sub_8A980(var_4, var11C, 0, var11C->sub_CD550(), v114, 0);
        } else if (l120 == 1) {
            var11C = sub_1745A0(0);
            SCRIPT_CHECK(var11C != 0);
            v110 = var11C->unk_1C0.sub_8A980(var_4, var11C, 0, var11C->sub_CD550(), v114, 0);
        } else if (l120 == 2) {
            var11C = sub_45170(arg_0);
            SCRIPT_CHECK(var11C != 0);
            v110 = dword_4B1E98.sub_8A980(var_4, 0, 0, var11C->sub_CD550(), v114, 0);
        }
    }
    sub_44350(arg_4, &v110);
}

// match: sub_5EB50 @ 0x0005EB50
// sp-match: sub_5EB50 @ 0x0004DA10
// "EfuncPlaySoundAndFacialAnim": for a sound from the entity (arg 2 = 0),
// first plays the facial animation arg 4 on it; then as "EfuncPlaySound".
void sub_5EB50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 2);
    if (var_4 == 0) {
        varC = sub_45170(arg_0);
        local_8 = SCRIPT_ARG(arg_4, 4);
        if (varC->vf_024() != 0)
            sub_5ACE0(local_8, varC->vf_024());
        else if (varC->vf_008() != 0)
            sub_5AC50(local_8, varC->vf_008());
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_5E880(arg_0, arg_4);
}

// match: sub_5EC30 @ 0x0005EC30
// sp-match: sub_5EC30 @ 0x0004DAB0
// "EfuncPlaySoundOnNamedEntity": as "EfuncPlaySound", from the entity of the
// kind-0x2E object under the key arg 2 (two slots), with arg 3.
void sub_5EC30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *bp_128;
    type_3DFEEC *l124;
    type_3D3548 *l120;
    type_3DF8D8 *var11C;
    RwInt32 v118;
    RwInt32 v114;
    RwInt32 v110;
    type_3DF8D8 *var_10C;
    RwChar local_108[0x100];
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10C = sub_198800(var_4);
    v110 = 0;
    if (var_10C == 0) {
        if (dword_44E860 != 0 && dword_44E86C != 0)
            sprintf(local_108, "EfuncPlaySound: Error! This Sound Alias is not Loaded! 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
    } else {
        v118 = var_10C->vf_008();
        if (v118 != 0x19 && v118 != 0x1B && v118 != 0x1E && v118 != 0x2A
            && v118 != 0x1C)
            sprintf(local_108,
                    "EfuncPlaySoundOnNamedEntity: Error! This God ID is not for a Sound Alias! "
                    "(Don't forget to use EfuncPlayIndexSound or "
                    "EfuncPlayIndexSoundOnNamedEntity for index aliases!) 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
        l120 = 0;
        bp_128 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
        v114 = SCRIPT_ARG(arg_4, 3);
        var11C = sub_198800(bp_128);
        SCRIPT_CHECK(var11C != 0);
        SCRIPT_CHECK(var11C->vf_008() == 0x2E);
        l124 = (type_3DFEEC *)var11C;
        SCRIPT_CHECK(l124->unk_10 != 0);
        l120 = ((type_D48D0 *)&l124->unk_24_id)->sub_D4910();
        SCRIPT_CHECK(l120 != 0);
        if (l120 != 0)
            v110 = l120->unk_1C0.sub_8A980(var_4, l120, 0, l120->sub_CD550(), v114, 0);
    }
    sub_44350(arg_4, &v110);
}

// match: sub_5EE80 @ 0x0005EE80
// sp-match: sub_5EE80 @ 0x0004DD10
// "EfuncPlaySoundAndFacialAnimOnNamedEntity": plays the facial animation
// arg 4 on the entity of the kind-0x2E object under the key arg 2 (two
// slots); then as "EfuncPlaySoundOnNamedEntity".
void sub_5EE80(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *l14;
    type_3DFEEC *var_10;
    type_3D3548 *ebp_C;
    type_3DF8D8 *v8;
    RwInt32 var_4;

    ebp_C = 0;
    l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    v8 = sub_198800(l14);
    SCRIPT_CHECK(v8 != 0);
    SCRIPT_CHECK(v8->vf_008() == 0x2E);
    var_10 = (type_3DFEEC *)v8;
    SCRIPT_CHECK(var_10->unk_10 != 0);
    ebp_C = ((type_D48D0 *)&var_10->unk_24_id)->sub_D4910();
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = SCRIPT_ARG(arg_4, 4);
    if (ebp_C != 0) {
        if (ebp_C->vf_024() != 0)
            sub_5ACE0(var_4, ebp_C->vf_024());
        else if (ebp_C->vf_008() != 0)
            sub_5AC50(var_4, ebp_C->vf_008());
    }
    sub_5EC30(arg_0, arg_4);
}

// match: sub_5EFC0 @ 0x0005EFC0
// sp-match: sub_5EFC0 @ 0x0004DEB0
// "EfuncPlayIndexSound": plays the index sound alias (kind 0x1D) under the
// key arg 1 (two slots), at the entry the entity's tag selects (arg 3 = 0:
// the surface's, 1: its own; a tagless entity uses 0 and warns), from the
// entity (arg 2 = 0), player 0 (1) or nowhere (2) with arg 4; returns its
// id, or 0.
void sub_5EFC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 stk_130;
    type_3D3548 *loc12C;
    type_4E5E40 *l128;
    RwInt32 l124;
    type_4E5E40_08 *l120;
    RwInt32 var11C;
    RwInt32 v118;
    RwInt32 v114;
    RwInt32 v110;
    type_3DF8D8 *var_10C;
    RwChar local_108[0x100];
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10C = sub_198800(var_4);
    v110 = 0;
    if (var_10C == 0) {
        if (dword_44E860 != 0 && dword_44E86C != 0)
            sprintf(local_108, "EfuncPlaySound: Error! This Sound Alias is not Loaded! 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
    } else {
        l124 = var_10C->vf_008();
        if (l124 != 0x1D)
            sprintf(local_108,
                    "EfuncPlayIndexSound: Error! This God ID is not for an Index Sound Alias! "
                    "0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
        stk_130 = SCRIPT_ARG(arg_4, 2);
        v118 = SCRIPT_ARG(arg_4, 3);
        var11C = SCRIPT_ARG(arg_4, 4);
        l128 = &dword_4E5E40;
        l120 = l128->unk_08;
        loc12C = sub_45170(arg_0);
        v114 = 0;
        if (v118 == 0) {
            if (l120[loc12C->unk_290].unk_00 < 0) {
                if (dword_44E838 != 0) {
                    type_3DF8D8_04 var_13C;
                    type_3D3548 *var_134;

                    var_13C.unk_00 = 0x9FAFD39B;    // not an address: a key
                    var_13C.unk_04 = 0xAB43C2E3;    // not an address: a key
                    var_134 = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&var_13C, 0, 0, var_134->sub_CD550(), 1, 0);
                }
                if (dword_44E860 != 0 && dword_44E874 != 0) {
                    RwChar var_240[0x100];

                    sprintf(var_240,
                            "EfuncPlayIndexSound: WARNING! Entity playing index sound using "
                            "self for index has no tag... calling index alias 0x%x, 0x%x! Using "
                            "0 for Index Alias purposes",
                            var_4->unk_00, var_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
                    sub_19A750(var_240);
#endif
                }
                loc12C->unk_290 = 0;
            }
            v114 = l120[loc12C->unk_290].unk_00;
        } else if (v118 == 1) {
            if (loc12C->unk_294 < 0) {
                if (dword_44E838 != 0) {
                    type_3DF8D8_04 var_24C;
                    type_3D3548 *var_244;

                    var_24C.unk_00 = 0x9FAFD39B;    // not an address: a key
                    var_24C.unk_04 = 0xAB43C2E3;    // not an address: a key
                    var_244 = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&var_24C, 0, 0, var_244->sub_CD550(), 1, 0);
                }
                if (dword_44E860 != 0 && dword_44E874 != 0) {
                    RwChar var_350[0x100];

                    sprintf(var_350,
                            "EfuncPlayIndexSound: WARNING! Entity on non-tagged surface calling "
                            "index alias 0x%x, 0x%x! Using 0 for Index Alias purposes",
                            var_4->unk_00, var_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
                    sub_19A750(var_350);
#endif
                }
                loc12C->unk_294 = 0;
            }
            v114 = l120[loc12C->unk_294].unk_00;
        }
        if (stk_130 == 0) {
            loc12C = sub_45170(arg_0);
            SCRIPT_CHECK(loc12C != 0);
            v110 = loc12C->unk_1C0.sub_8AA70(var_4, v114, loc12C, 0, loc12C->sub_CD550(), var11C, 0);
        } else if (stk_130 == 1) {
            loc12C = sub_1745A0(0);
            SCRIPT_CHECK(loc12C != 0);
            v110 = loc12C->unk_1C0.sub_8AA70(var_4, v114, loc12C, 0, loc12C->sub_CD550(), var11C, 0);
        } else if (stk_130 == 2) {
            loc12C = sub_45170(arg_0);
            SCRIPT_CHECK(loc12C != 0);
            v110 = dword_4B1E98.sub_8AA70(var_4, v114, 0, 0, loc12C->sub_CD550(), var11C, 0);
        }
    }
    {
        // Thirteen locals the image reserves and never uses.
        RwInt32 unused_C;
        RwInt32 unused_B;
        RwInt32 unused_A;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v110);
}

// match: sub_5F4B0 @ 0x0005F4B0
// sp-match: sub_5F4B0 @ 0x0004E1E0
// "EfuncPlayIndexSoundOnNamedEntity": as "EfuncPlayIndexSound", from the
// entity of the kind-0x2E object under the key arg 2 (two slots), with
// arg 4; nothing without that entity.
void sub_5F4B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_130;
    type_3DF8D8 *loc12C;
    type_4E5E40 *l128;
    RwInt32 l124;
    type_4E5E40_08 *l120;
    RwInt32 var11C;
    RwInt32 v118;
    RwInt32 v114;
    RwInt32 v110;
    type_3DF8D8 *var_10C;
    RwChar local_108[0x100];
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_10C = sub_198800(var_4);
    v110 = 0;
    if (var_10C == 0) {
        if (dword_44E860 != 0 && dword_44E86C != 0)
            sprintf(local_108, "EfuncPlaySound: Error! This Sound Alias is not Loaded! 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
    } else {
        type_3DF8D8_04 *var_138;
        type_3DFEEC *var_134;

        l124 = var_10C->vf_008();
        if (l124 != 0x1D)
            sprintf(local_108,
                    "EfuncPlayIndexSoundOnNamedEntity: Error! This God ID is not for an Index "
                    "Sound Alias! 0x%X, 0x%X",
                    var_4->unk_00, var_4->unk_04);
        stk_130 = 0;
        var_138 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
        loc12C = sub_198800(var_138);
        SCRIPT_CHECK(loc12C != 0);
        SCRIPT_CHECK(loc12C->vf_008() == 0x2E);
        var_134 = (type_3DFEEC *)loc12C;
        SCRIPT_CHECK(var_134->unk_10 != 0);
        stk_130 = ((type_D48D0 *)&var_134->unk_24_id)->sub_D4910();
        SCRIPT_CHECK(stk_130 != 0);
        if (stk_130 == 0) {
            sub_44350(arg_4, 0);
            return;
        }
        v118 = SCRIPT_ARG(arg_4, 3);
        var11C = SCRIPT_ARG(arg_4, 4);
        l128 = &dword_4E5E40;
        l120 = l128->unk_08;
        v114 = 0;
        if (v118 == 0) {
            if (l120[stk_130->unk_290].unk_00 < 0) {
                if (dword_44E838 != 0) {
                    type_3DF8D8_04 l144;
                    type_3D3548 *var_13C;

                    l144.unk_00 = 0x9FAFD39B;    // not an address: a key
                    l144.unk_04 = 0xAB43C2E3;    // not an address: a key
                    var_13C = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&l144, 0, 0, var_13C->sub_CD550(), 1, 0);
                }
                if (dword_44E860 != 0 && dword_44E874 != 0) {
                    RwChar var_248[0x100];

                    sprintf(var_248,
                            "EfuncPlayIndexSoundOnNamedEntity: WARNING! Entity playing index "
                            "sound using self for index has no tag... calling index alias 0x%x, "
                            "0x%x! Using 0 for Index Alias purposes",
                            var_4->unk_00, var_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
                    sub_19A750(var_248);
#endif
                }
                stk_130->unk_290 = 0;
            }
            v114 = l120[stk_130->unk_290].unk_00;
        } else if (v118 == 1) {
            if (stk_130->unk_294 < 0) {
                if (dword_44E838 != 0) {
                    type_3DF8D8_04 var_254;
                    type_3D3548 *var_24C;

                    var_254.unk_00 = 0x9FAFD39B;    // not an address: a key
                    var_254.unk_04 = 0xAB43C2E3;    // not an address: a key
                    var_24C = sub_1745A0(0);
                    dword_4B1E98.sub_8A980(&var_254, 0, 0, var_24C->sub_CD550(), 1, 0);
                }
                if (dword_44E860 != 0 && dword_44E874 != 0) {
                    RwChar var_358[0x100];

                    sprintf(var_358,
                            "EfuncPlayIndexSoundOnNamedEntity: WARNING! Entity on non-tagged "
                            "surface calling index alias 0x%x, 0x%x! Using 0 for Index Alias "
                            "purposes",
                            var_4->unk_00, var_4->unk_04);
#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player compiles the debug print out
                    sub_19A750(var_358);
#endif
                }
                stk_130->unk_294 = 0;
            }
            v114 = l120[stk_130->unk_294].unk_00;
        } else
            SCRIPT_CHECK(0);
        v110 = stk_130->unk_1C0.sub_8AA70(var_4, v114, stk_130, 0, stk_130->sub_CD550(), var11C, 0);
    }
    sub_44350(arg_4, &v110);
}

// match: sub_5F950 @ 0x0005F950
// sp-match: sub_5F950 @ 0x0004E5A0
// "FadeSubstreamVolume": fades the two substreams of the stream of voice
// type arg 1 (0 to 2) to the volumes arg 2 and arg 3 (percent, scaled by the
// stream's sound's volume and clamped to 0 to 1) over the times arg 4 and
// arg 5, all through globals.
void sub_5F950(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    dword_428A2C = SCRIPT_ARG(arg_4, 1);
    flt_439E70[0] = (RwReal)SCRIPT_ARG(arg_4, 2);
    flt_439E70[1] = (RwReal)SCRIPT_ARG(arg_4, 3);
    dword_439E68[0] = SCRIPT_ARG(arg_4, 4);
    dword_439E68[1] = SCRIPT_ARG(arg_4, 5);
    if (flt_439E70[0] > 0.0f)
        flt_439E70[0] /= 100.0f;
    if (flt_439E70[1] > 0.0f)
        flt_439E70[1] /= 100.0f;
    SCRIPT_CHECK(flt_439E70[0] >= 0.0f && flt_439E70[0] <= 1.0f);
    SCRIPT_CHECK(flt_439E70[1] >= 0.0f && flt_439E70[1] <= 1.0f);
    SCRIPT_CHECK(dword_428A2C >= 0 && dword_428A2C <= 2);
    for (var_4 = 0; var_4 < 2; var_4++) {
        dword_428A28 = flt_439E70[var_4];
        if (dword_44E8D8[dword_428A2C].unk_248 != 0)
            dword_428A28 = dword_44E8D8[dword_428A2C].unk_248->unk_18 / 100.0f * dword_428A28;
        if (dword_428A28 < 0.0)
            dword_428A28 = 0.0f;
        if (dword_428A28 > 1.0f)
            dword_428A28 = 1.0f;
        dword_44E8D8[dword_428A2C].unk_190[var_4] = dword_428A28;
        dword_44E8D8[dword_428A2C].unk_1F0[var_4] = dword_428A28;
        dword_44E8D8[dword_428A2C].unk_1D0[var_4] = 1.0f / dword_439E68[var_4];
    }
    sub_44350(arg_4, 0);
}

// match: sub_5FC30 @ 0x0005FC30
// sp-match: sub_5FC30 @ 0x0004E880
// "SoundStillPlaying": whether the sound arg 1 (a handle; 0 and -1 for
// none) still plays.
void sub_5FC30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_5FC30 *local_8;
    RwInt32 var_4;

    local_8 = (type_5FC30 *)SCRIPT_ARG(arg_4, 1);
    var_4 = 0;
    if (local_8 != 0 && local_8 != (type_5FC30 *)-1)
        var_4 = (local_8->unk_34 & 2) != 0;
    sub_44350(arg_4, &var_4);
}

// match: sub_5FCA0 @ 0x0005FCA0
// sp-match: sub_5FCA0 @ 0x0004E8F0
// "AddObjective": adds the objective under the key arg 1 (two slots) with
// arg 2 and arg 3, or formats the key for a message no one sees.
void sub_5FCA0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwChar slot_34[0x20];
    type_3DF8D8 *loc10;
    type_3DF8D8_04 *bp_C;
    RwInt32 frm_8;
    RwInt32 bp_4;

    bp_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    frm_8 = SCRIPT_ARG(arg_4, 2);
    bp_4 = SCRIPT_ARG(arg_4, 3);
    loc10 = sub_198800(bp_C);
    if (loc10 == 0)
        sprintf(slot_34, "0x%08x, 0x%08x", bp_C->unk_00, bp_C->unk_04);
    else
        sub_1703B0(bp_C, frm_8, bp_4);
    sub_44350(arg_4, 0);
}

// match: sub_5FD90 @ 0x0005FD90
// sp-match: sub_5FD90 @ 0x0004E990
// "RemoveObjective": removes the objective under the key arg 1 (two slots),
// returning sub_170500's result.
void sub_5FD90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = sub_170500(var_4);
    sub_44350(arg_4, &local_8);
}

// match: sub_5FDF0 @ 0x0005FDF0
// sp-match: sub_5FDF0 @ 0x0004EA00
// "GetObjectiveFlags": the flags of the objective under the key arg 1.
void sub_5FDF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_1706A0(local_8);
    sub_44350(arg_4, &var_4);
}

// match: sub_5FE50 @ 0x0005FE50
// sp-match: sub_5FE50 @ 0x0004EA70
// "SetObjectiveFlags": sets the flags arg 2 of the objective under the key
// arg 1.
void sub_5FE50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    sub_170710(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_5FED0 @ 0x0005FED0
// sp-match: sub_5FED0 @ 0x0004EAC0
// "ClearObjectiveFlags": clears the flags arg 2 of the objective under the
// key arg 1.
void sub_5FED0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    sub_170790(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_5FF50 @ 0x0005FF50
// sp-match: sub_5FF50 @ 0x0004EB10
// "GetObjectiveCounter": the counter of the objective under the key arg 1.
void sub_5FF50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = sub_170810(local_8);
    sub_44350(arg_4, &var_4);
}

// match: sub_5FFB0 @ 0x0005FFB0
// sp-match: sub_5FFB0 @ 0x000564F0
// "SetObjectiveCounter" and "ModifyObjectiveCounter" (both entries): hand
// the key arg 1 and arg 2 to an empty function.
void sub_5FFB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    sub_19A750(local_8, var_4);
    sub_44350(arg_4, 0);
}

#ifdef CODFH_SP
void sp_sub_10D060(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
void sp_sub_10D160(type_3DF8D8_04 *arg_0, RwInt32 arg_4);
void sp_sub_10D2B0(type_3DF8D8_04 *arg_0);

// sp-match: ?sp_sub_4EB80@@YAXIPAUtype_44350@@@Z @ 0x0004EB80
// "SetObjectiveCounter": hands the key arg 1 and arg 2 to sp_sub_10D060.
void sp_sub_4EB80(RwUInt32 arg_0, type_44350 *arg_4)
{
    sp_sub_10D060((type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1), SCRIPT_ARG(arg_4, 2));
#ifdef CODFH_SP_LOGS
    sub_19A750((type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1), SCRIPT_ARG(arg_4, 2)); // (multiplayer's log, sub_5FFB0)
#endif
    sub_44350(arg_4, 0);
}
#endif

#ifdef CODFH_SP
// sp-match: ?sp_sub_4EBD0@@YAXIPAUtype_44350@@@Z @ 0x0004EBD0
// "ModifyObjectiveCounter": hands the key arg 1 and arg 2 to sp_sub_10D160.
void sp_sub_4EBD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    sp_sub_10D160((type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1), SCRIPT_ARG(arg_4, 2));
#ifdef CODFH_SP_LOGS
    sub_19A750((type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1), SCRIPT_ARG(arg_4, 2)); // (multiplayer's log, sub_5FFB0)
#endif
    sub_44350(arg_4, 0);
}
#endif

// match: sub_60030 @ 0x00060030
// sp-match: sub_60030 @ 0x0004EC20
// "SetActivateMessage": the activate message arg 2 of the objective under the key arg 1
// (two slots); returns sub_170940's result.
void sub_60030(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170940(var_4, local_8);
    sub_44350(arg_4, &varC);
}

// match: sub_600B0 @ 0x000600B0
// sp-match: sub_600B0 @ 0x0004EC90
// "SetCompleteMessage": the complete message arg 2 of the objective under the key arg 1
// (two slots); returns sub_170A30's result.
void sub_600B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170A30(var_4, local_8);
    sub_44350(arg_4, &varC);
}

// match: sub_60130 @ 0x00060130
// sp-match: sub_60130 @ 0x0004ED00
// "SetFailMessage": the fail message arg 2 of the objective under the key arg 1
// (two slots); returns sub_170B20's result.
void sub_60130(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170B20(var_4, local_8);
    sub_44350(arg_4, &varC);
}

// match: sub_601B0 @ 0x000601B0
// sp-match: sub_601B0 @ 0x0004ED70
// "SetIncrementCounterMessage": the increment-counter message arg 2 of the objective under the key arg 1
// (two slots); returns sub_170C10's result.
void sub_601B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170C10(var_4, local_8);
    sub_44350(arg_4, &varC);
}

// match: sub_60230 @ 0x00060230
// sp-match: sub_60230 @ 0x0004EDE0
// "SetDecrementCounterMessage": the decrement-counter message arg 2 of the objective under the key arg 1
// (two slots); returns sub_170D00's result.
void sub_60230(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    local_8 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170D00(var_4, local_8);
    sub_44350(arg_4, &varC);
}

// match: sub_602B0 @ 0x000602B0
// sp-match: sub_602B0 @ 0x0004EE50
// "SetObjectiveNagTimer": the nag timer arg 2 of the objective under the
// key arg 1 (two slots); returns sub_170FD0's result.
void sub_602B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3DF8D8_04 *local_8;
#ifdef CODFH_SP // shape: the timer read as a real (SP 0x4EE50: fld/fstp)
    RwReal var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    varC = sub_170FD0(local_8, var_4);
#else
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    varC = sub_170FD0(local_8, *(RwReal *)&var_4);
#endif
    sub_44350(arg_4, &varC);
}

// match: sub_60330 @ 0x00060330
// sp-match: sub_60330 @ 0x0004EED0
// "SetObjectiveTarget": the target of the objective under the key arg 1:
// the entity (flag 2) or trigger (flag 1) of the object under the key arg 2
// (kind 0x2C to 0x2E).
void sub_60330(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0 *local_20;
    type_3D3548 *var_1C;
    type_3DFEEC *var18;
    type_3DF8D8_04 *stk_14;
    type_3DF8D8_04 *l10;
    type_3DF8D8 *local_C;
    RwInt32 lv_8;
    RwInt32 var_4;

    l10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    stk_14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    local_C = sub_198800(stk_14);
    var_4 = local_C->vf_008();
    lv_8 = local_C != 0 && (var_4 == 0x2E || var_4 == 0x2D || var_4 == 0x2C);
    if (lv_8 != 0) {
        var18 = (type_3DFEEC *)local_C;
        if (var18->unk_10 & 2) {
            var_1C = ((type_D48D0 *)&var18->unk_24_id)->sub_D4910();
            sub_171110(l10, var_1C);
        } else if (var18->unk_10 & 1) {
            local_20 = var18->unk_2C_trigger;
            sub_171070(l10, local_20);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_60440 @ 0x00060440
// sp-match: sub_60440 @ 0x0004EF60
// "PrintObjective": hands the key arg 1 (two slots) to an empty function.
void sub_60440(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
#ifdef CODFH_SP // single player prints the objective (SP 0x4EF78 calls sp_sub_10D2B0)
    sp_sub_10D2B0(var_4);
#ifdef CODFH_SP_LOGS
    sub_19A750(var_4); // (and multiplayer's log of its key)
#endif
#else
    sub_19A750(var_4);
#endif
    sub_44350(arg_4, 0);
}

// match: sub_60490 @ 0x00060490
// sp-match: sub_60490 @ 0x0004EFA0
// "EnableObjectiveTargetSystem": turns the objective target system on or
// off (arg 1).
void sub_60490(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_4E5648 = var_4;
    sub_44350(arg_4, 0);
}

// match: sub_604E0 @ 0x000604E0
// sp-match: sub_604E0 @ 0x0004EFD0
// "SetObjectiveSplinePath": the spline path of the objective under the key
// arg 1: none for the key (-1, -1) in arg 2, else the spline of the object
// under it (kind 0x2C to 0x2E; its test ORs flag 0x80 in rather than
// masking it, so any such object passes), or a message no one sees.
void sub_604E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwChar bp_40[0x20];
    SplinePath *bp_1C;
    type_3DFEEC *frm_18;
    type_3DF8D8 *local_14;
    RwInt32 loc10;
    RwInt32 bp_C;
    type_3DF8D8_04 *frm_8;
    type_3DF8D8_04 *bp_4;

    bp_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    frm_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    if (frm_8->unk_00 == -1 && frm_8->unk_04 == -1)
        sub_1711B0(bp_4, 0);
    else {
        local_14 = sub_198800(frm_8);
        bp_C = local_14->vf_008();
        loc10 = local_14 != 0 && (bp_C == 0x2E || bp_C == 0x2D || bp_C == 0x2C);
        if (loc10 != 0) {
            frm_18 = (type_3DFEEC *)local_14;
            if (frm_18->unk_10 | 0x80) {
                bp_1C = frm_18->unk_24;
                if (bp_1C == 0)
                    sprintf(bp_40, "0x%08x, 0x%08x", frm_8->unk_00, frm_8->unk_04);
                else
                    sub_1711B0(bp_4, bp_1C);
            }
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_60630 @ 0x00060630
// sp-match: sub_60630 @ 0x0004F0A0
// "SetObjectiveLookaheadDistance": the lookahead distance arg 2 of the
// objective under the key arg 1.
void sub_60630(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwReal var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    sub_171230(local_8, var_4);
    sub_44350(arg_4, 0);
}

// match: sub_606B0 @ 0x000606B0
// sp-match: sub_606B0 @ 0x0004F0F0
// "AddSubObjectiveTarget": adds the entity (flag 2) of the object under the key arg 1
// (kind 0x2C to 0x2E) as a sub-objective target.
void sub_606B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_18;
    type_3DFEEC *l14;
    type_3DF8D8_04 *var_10;
    type_3DF8D8 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_198800(var_10);
    var_4 = ebp_C->vf_008();
    v8 = ebp_C != 0 && (var_4 == 0x2E || var_4 == 0x2D || var_4 == 0x2C);
    if (v8 != 0) {
        l14 = (type_3DFEEC *)ebp_C;
        if (l14->unk_10 & 2) {
            stk_18 = ((type_D48D0 *)&l14->unk_24_id)->sub_D4910();
            sub_171380(stk_18);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_60770 @ 0x00060770
// sp-match: sub_60770 @ 0x0004F160
// "ClearSubObjectiveTarget": clears the entity (flag 2) of the object under the key arg 1
// (kind 0x2C to 0x2E) as a sub-objective target.
void sub_60770(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_18;
    type_3DFEEC *l14;
    type_3DF8D8_04 *var_10;
    type_3DF8D8 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    var_10 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    ebp_C = sub_198800(var_10);
    var_4 = ebp_C->vf_008();
    v8 = ebp_C != 0 && (var_4 == 0x2E || var_4 == 0x2D || var_4 == 0x2C);
    if (v8 != 0) {
        l14 = (type_3DFEEC *)ebp_C;
        if (l14->unk_10 & 2) {
            stk_18 = ((type_D48D0 *)&l14->unk_24_id)->sub_D4910();
            sub_1713F0(stk_18);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_60830 @ 0x00060830
// sp-match: sub_60830 @ 0x0004F1D0
// "ClearAllSubObjectiveTargets".
void sub_60830(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_171440();
    sub_44350(arg_4, 0);
}

// match: sub_60850 @ 0x00060850
// sp-match: sub_60850 @ 0x0004F1F0
// "DisplayHelpMessage": shows the help message under the key arg 1 (two
// slots) with arg 2 and arg 3, when help messages may show.
void sub_60850(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    varC = SCRIPT_ARG(arg_4, 3);
    if (dword_4F28F0->get_unk_28())
        sub_17C500(local_8, var_4, varC);
    sub_44350(arg_4, 0);
}

// match: sub_60910 @ 0x00060910
// sp-match: sub_60910 @ 0x0004F250
// "KillHelpMessage": removes the help message under the key arg 1.
void sub_60910(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *var_4;

    var_4 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    sub_17C640(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_60960 @ 0x00060960
// sp-match: sub_60960 @ 0x0004F290
// "ClearAllHelpMessages": with arg 1.
void sub_60960(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    sub_17C6C0(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_609B0 @ 0x000609B0
// sp-match: sub_609B0 @ 0x0004F2D0
// "GetLocalYawAngleToPathPoint": the heading from the entity to its AI
// object's path point, in degrees brought into range.
void sub_609B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    (varC = var_4->sub_2C040()) *= 57.295776f;
    varC = sub_13F9E0(varC);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &varC);
}

// match: sub_60A30 @ 0x00060A30
// sp-match: sub_60A30 @ 0x0004F3D0
// "GetWorldYawAngleToTargetFrompPathPoint": the turn, in degrees, from the
// heading towards the entity's AI object's path point to the heading
// towards its tracked entity (RWS::DegAngDiff), both from the entity; 1e37
// without a tracked entity.
void sub_60A30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d *ebp_34;
    RwV3d var_30;
    RwV3d fp_24;
    RwReal stk_18;
    RwReal l14;
    type_3D3548 *var_10;
    type_3D3548 *ebp_C;
    RwReal v8;
    AIData *var_4;

    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8 = 1e37f;
    var_10 = var_4->unk_1374.sub_D4910();
    if (var_10 != 0) {
        ebp_34 = &var_4->unk_D70;
        RwV3dSubMacro(&var_30, ebp_34, ebp_C->sub_CD550());
        RwV3dNormalize(&var_30, &var_30);
#ifdef CODFH_SP // sub_2C1E0 expanded inline (SP 0x4F3D0: fpatan)
        l14 = (RwReal)atan2(var_30.z, var_30.x) * 57.295776f;
#else
        l14 = sub_2C1E0(&var_30) * 57.295776f;
#endif
        l14 = sub_13F9E0(l14);
        RwV3dSubMacro(&fp_24, var_10->sub_CD550(), ebp_C->sub_CD550());
        RwV3dNormalize(&fp_24, &fp_24);
#ifdef CODFH_SP // sub_2C1E0 expanded inline (SP 0x4F3D0: fpatan)
        stk_18 = (RwReal)atan2(fp_24.z, fp_24.x) * 57.295776f;
#else
        stk_18 = sub_2C1E0(&fp_24) * 57.295776f;
#endif
        stk_18 = sub_13F9E0(stk_18);
        v8 = RWS::DegAngDiff(stk_18, l14);
    }
    {
        // Five locals the image reserves and never uses.
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_60BF0 @ 0x00060BF0
// sp-match: sub_60BF0 @ 0x0004F5D0
// "SetVisionMultiplier": the vision multiplier arg 1 and the flag arg 2 of
// a soldier (vf_008) or vehicle (vf_010); the arguments are copied as
// dwords either way, and the soldier tests the second as an integer.
void sub_60BF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DBC78 *l14;
    type_3DAFC8 *var_10;
    RwInt32 ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4->vf_008() != 0 || var_4->vf_010() != 0) {
        v8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
        ebp_C = SCRIPT_ARGT<RwInt32>(arg_4, 2);
        if (var_4->vf_008() != 0) {
            var_10 = (type_3DAFC8 *)var_4;
            var_10->vf_238(v8);
            var_10->vf_240(ebp_C);
        } else if (var_4->vf_010() != 0) {
            l14 = (type_3DBC78 *)var_4;
            l14->vf_23C(v8);
            l14->vf_244(ebp_C);
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_60D10 @ 0x00060D10
// sp-match: sub_60D10 @ 0x0004F6C0
// "GetTeam": the team (the low three bits of unk_2C) of the entity of the
// object the handle arg 1 names, or 0.
void sub_60D10(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_10 != 0);
    v8 = var_10->sub_71300();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    if (v8 != 0)
        var_4 = v8->unk_2C & 7;
    sub_44350(arg_4, &var_4);
}

// match: sub_60DB0 @ 0x00060DB0
// sp-match: sub_60DB0 @ 0x0004F7C0
// "GetPositionXFromAIObj": the x of the position of the entity of the
// object the handle arg 1 names.
void sub_60DB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwV3d *v8;
    RwReal var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    l14 = (type_3D2E7C *)sub_67620(var_10);
    SCRIPT_CHECK(l14 != 0);
    ebp_C = l14->sub_71300();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->sub_CD550();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->x;
    sub_44350(arg_4, &var_4);
}

// match: sub_60E50 @ 0x00060E50
// sp-match: sub_60E50 @ 0x0004F8F0
// "GetPositionYFromAIObj": the y of the position of the entity of the
// object the handle arg 1 names.
void sub_60E50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwV3d *v8;
    RwReal var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    l14 = (type_3D2E7C *)sub_67620(var_10);
    SCRIPT_CHECK(l14 != 0);
    ebp_C = l14->sub_71300();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->sub_CD550();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->y;
    sub_44350(arg_4, &var_4);
}

// match: sub_60F00 @ 0x00060F00
// sp-match: sub_60F00 @ 0x0004FA20
// "GetPositionZFromAIObj": the z of the position of the entity of the
// object the handle arg 1 names.
void sub_60F00(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwV3d *v8;
    RwReal var_4;

    var_10 = SCRIPT_ARG(arg_4, 1);
    l14 = (type_3D2E7C *)sub_67620(var_10);
    SCRIPT_CHECK(l14 != 0);
    ebp_C = l14->sub_71300();
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->sub_CD550();
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->z;
    sub_44350(arg_4, &var_4);
}

// match: sub_60FB0 @ 0x00060FB0
// sp-match: sub_60FB0 @ 0x0004FB50
// "GetOffsetPositionXFromAIObj": the x of the offset (arg 2, arg 3, arg 4)
// in the frame of the entity of the object the handle arg 1 names, or of
// the offset from its volume's point without a frame.
void sub_60FB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal *local_28;
    RwMatrix *local_24;
    type_3D2E7C *local_20;
    RwInt32 var_1C;
    RwReal local_18;
    type_3D3548 *local_14;
    RwV3d local_10;
    RwFrame *var_4;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_20 = (type_3D2E7C *)sub_67620(var_1C);
    SCRIPT_CHECK(local_20 != 0);
    local_14 = local_20->sub_71300();
    SCRIPT_CHECK(local_14 != 0);
    local_10.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_10.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    local_10.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_4 = local_14->get_unk_340();
    if (var_4 != 0) {
        local_24 = RwFrameGetLTM(var_4);
        local_18 = local_10.x * local_24->right.x + local_10.y * local_24->up.x + local_10.z * local_24->at.x
                 + local_24->pos.x;
    } else {
        local_28 = local_14->vf_0C4();
        local_18 = local_10.x + local_28[0];
    }
    sub_44350(arg_4, &local_18);
}

// match: sub_61120 @ 0x00061120
// sp-match: sub_61120 @ 0x0004FCB0
// "GetOffsetPositionYFromAIObj": the y of the offset (arg 2, arg 3, arg 4)
// in the frame of the entity of the object the handle arg 1 names, or of
// the offset from its volume's point without a frame.
void sub_61120(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal *local_28;
    RwMatrix *local_24;
    type_3D2E7C *local_20;
    RwInt32 var_1C;
    type_3D3548 *local_18;
    RwReal local_14;
    RwV3d local_10;
    RwFrame *var_4;

    var_1C = SCRIPT_ARG(arg_4, 1);
    local_20 = (type_3D2E7C *)sub_67620(var_1C);
    SCRIPT_CHECK(local_20 != 0);
    local_18 = local_20->sub_71300();
    SCRIPT_CHECK(local_18 != 0);
    local_10.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_10.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    local_10.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_4 = local_18->get_unk_340();
    if (var_4 != 0) {
        local_24 = RwFrameGetLTM(var_4);
        local_14 = local_10.x * local_24->right.y + local_10.y * local_24->up.y + local_10.z * local_24->at.y
                 + local_24->pos.y;
    } else {
        local_28 = local_18->vf_0C4();
        local_14 = local_10.y + local_28[1];
    }
    sub_44350(arg_4, &local_14);
}

// match: sub_61290 @ 0x00061290
// sp-match: sub_61290 @ 0x0004FE10
// "GetOffsetPositionZFromAIObj": the z of the offset (arg 2, arg 3, arg 4)
// in the frame of the entity of the object the handle arg 1 names, or of
// the offset from its volume's point without a frame.
void sub_61290(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal *local_28;
    RwMatrix *local_24;
    type_3D2E7C *local_20;
    RwReal var_1C;
    RwInt32 local_18;
    type_3D3548 *local_14;
    RwV3d local_10;
    RwFrame *var_4;

    local_18 = SCRIPT_ARG(arg_4, 1);
    local_20 = (type_3D2E7C *)sub_67620(local_18);
    SCRIPT_CHECK(local_20 != 0);
    local_14 = local_20->sub_71300();
    SCRIPT_CHECK(local_14 != 0);
    local_10.x = SCRIPT_ARGT<RwReal>(arg_4, 2);
    local_10.y = SCRIPT_ARGT<RwReal>(arg_4, 3);
    local_10.z = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_4 = local_14->get_unk_340();
    if (var_4 != 0) {
        local_24 = RwFrameGetLTM(var_4);
        var_1C = local_10.x * local_24->right.z + local_10.y * local_24->up.z + local_10.z * local_24->at.z
                 + local_24->pos.z;
    } else {
        local_28 = local_14->vf_0C4();
        var_1C = local_10.z + local_28[2];
    }
    sub_44350(arg_4, &var_1C);
}

// match: sub_61400 @ 0x00061400
// sp-match: sub_61400 @ 0x0004FF70
// "GetHierarchyPositionXFromAIObj": the x of the position of bone arg 2 of
// the entity of the object the handle arg 1 names (its animation's
// hierarchy).
void sub_61400(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_1C;
    RwMatrix *var18;
    RwInt32 stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    RpHAnimHierarchy *lv_8;
    RwReal var_4;

    stk_14 = SCRIPT_ARG(arg_4, 1);
    var_1C = (type_3D2E7C *)sub_67620(stk_14);
    SCRIPT_CHECK(var_1C != 0);
    l10 = var_1C->sub_71300();
    SCRIPT_CHECK(l10 != 0);
    SCRIPT_CHECK(l10->unk_284 != 0);
    lv_8 = l10->unk_284->unk_18;
    local_C = RpHAnimIDGetIndex(lv_8, SCRIPT_ARG(arg_4, 2));
    var18 = RpHAnimHierarchyGetMatrixArray(lv_8);
    var_4 = var18[local_C].pos.x;
    sub_44350(arg_4, &var_4);
}

// match: sub_61500 @ 0x00061500
// sp-match: sub_61500 @ 0x000500D0
// "GetHierarchyPositionYFromAIObj": the y of the position of bone arg 2 of
// the entity of the object the handle arg 1 names (its animation's
// hierarchy).
void sub_61500(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_1C;
    RwMatrix *var18;
    RwInt32 stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    RpHAnimHierarchy *lv_8;
    RwReal var_4;

    stk_14 = SCRIPT_ARG(arg_4, 1);
    var_1C = (type_3D2E7C *)sub_67620(stk_14);
    SCRIPT_CHECK(var_1C != 0);
    l10 = var_1C->sub_71300();
    SCRIPT_CHECK(l10 != 0);
    SCRIPT_CHECK(l10->unk_284 != 0);
    lv_8 = l10->unk_284->unk_18;
    local_C = RpHAnimIDGetIndex(lv_8, SCRIPT_ARG(arg_4, 2));
    var18 = RpHAnimHierarchyGetMatrixArray(lv_8);
    var_4 = var18[local_C].pos.y;
    sub_44350(arg_4, &var_4);
}

// match: sub_61600 @ 0x00061600
// sp-match: sub_61600 @ 0x00050230
// "GetHierarchyPositionZFromAIObj": the z of the position of bone arg 2 of
// the entity of the object the handle arg 1 names (its animation's
// hierarchy).
void sub_61600(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_1C;
    RwMatrix *var18;
    RwInt32 stk_14;
    type_3D3548 *l10;
    RwInt32 local_C;
    RpHAnimHierarchy *lv_8;
    RwReal var_4;

    stk_14 = SCRIPT_ARG(arg_4, 1);
    var_1C = (type_3D2E7C *)sub_67620(stk_14);
    SCRIPT_CHECK(var_1C != 0);
    l10 = var_1C->sub_71300();
    SCRIPT_CHECK(l10 != 0);
    SCRIPT_CHECK(l10->unk_284 != 0);
    lv_8 = l10->unk_284->unk_18;
    local_C = RpHAnimIDGetIndex(lv_8, SCRIPT_ARG(arg_4, 2));
    var18 = RpHAnimHierarchyGetMatrixArray(lv_8);
    var_4 = var18[local_C].pos.z;
    sub_44350(arg_4, &var_4);
}

// match: sub_61700 @ 0x00061700
// sp-match: sub_61700 @ 0x00050390
RwInt32 sub_61700(type_3D3548 *arg_0, RwV3d *arg_4, RwV3d *arg_8, RwReal *arg_C, RwInt32 arg_10)
{
    RwV3d bp_2C;
    RwInt32 local_20;
    RwV3d var_1C;
    RwV3d local_10;
    RwReal var_4;

    local_20 = 0;
    var_1C = *arg_4;
    local_10 = *arg_8;
    var_1C.y += arg_0->unk_40 + 33.0f;
    local_10.y += 100.0f;
    local_20 = !arg_0->sub_D2FC0(&var_1C, &local_10, 0, arg_C, 1, 0, arg_10, 1, 0x20000, 0, 0); // not an address: a flag
    RwV3dSubMacro(&bp_2C, &local_10, &var_1C);
    var_4 = RwV3dLength((RwV3d *)&bp_2C);
    *arg_C = var_4 * *arg_C;
    return local_20;
}

// match: sub_617D0 @ 0x000617D0
// sp-match: sub_617D0 @ 0x00050460
// "CanTurnToTurnLocation": whether the line from the entity to its AI
// object's target point is clear, or blocked further than 150 along.
void sub_617D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwReal ebp_C;
    type_3D3548 *v8;
    AIData *var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = v8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    SCRIPT_CHECK(var_4->unk_4F0 != 0);
    var_10 = sub_61700(v8, v8->sub_CD550(), var_4->unk_4F0, &ebp_C, 0);
    if (var_10 == 0 && ebp_C > 150.0f)
        var_10 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_10);
}

// match: sub_61890 @ 0x00061890
// sp-match: sub_61890 @ 0x000505C0
// "CanTurnTo": whether the line from the entity to (arg 1, arg 2, arg 3) is
// clear (with the flag arg 4), or blocked further than 150 along.
void sub_61890(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d var_1C;
    RwInt32 l10;
    RwReal local_C;
    RwInt32 lv_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    var_1C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_1C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    lv_8 = SCRIPT_ARG(arg_4, 4);
    l10 = sub_61700(var_4, var_4->sub_CD550(), &var_1C, &local_C, lv_8);
    if (l10 == 0 && local_C > 150.0f)
        l10 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &l10);
}

// match: sub_619B0 @ 0x000619B0
// sp-match: sub_619B0 @ 0x000506D0
// "SetTurnLocationTo": the entity's AI object's turn location (arg 1, arg
// 2, arg 3), which becomes its target point.
void sub_619B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_4F4.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4->unk_4F4.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_4->unk_4F4.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_4->sub_17140(&var_4->unk_4F4);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_61AB0 @ 0x00061AB0
// sp-match: sub_61AB0 @ 0x000507E0
// "SetTurnLocationOverrideTo": the entity's AI object's turn location
// override (arg 1, arg 2, arg 3; unk_500).
void sub_61AB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwV3d var_10;
    AIData *var_4;

    l14 = sub_45170(arg_0);
    SCRIPT_CHECK(l14 != 0);
    var_4 = l14->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_10.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_4->unk_500 = var_10;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_61BA0 @ 0x00061BA0
// sp-match: sub_61BA0 @ 0x000508F0
RwInt32 sub_61BA0(type_3D3548 *arg_0, RwV3d *arg_4)
{
    RwFrame *local_20;
    RwV3d var_1C;
    RwInt32 l10;
    RwMatrix *local_C;
    RwReal lv_8;
    RwV3d *var_4;

    l10 = 0;
    var_4 = arg_0->sub_CD550();
    SCRIPT_CHECK(var_4 != 0);
    local_20 = arg_0->get_unk_340();
    local_C = RwFrameGetLTM(local_20);
    RwV3dSubMacro(&var_1C, arg_4, var_4);
    var_1C.y = 0.0f;
    RwV3dNormalize(&var_1C, &var_1C);
    lv_8 = RwV3dDotProductMacro(&var_1C, &local_C->at);
    if (lv_8 <= 0.866f)
        l10 = 1;
    return l10;
}

// match: sub_61C80 @ 0x00061C80
// sp-match: sub_61C80 @ 0x000509C0
// "ShouldITurnToPos": whether the entity should turn to (arg 1, arg 2,
// arg 3) (sub_61BA0).
void sub_61C80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    RwV3d var_10;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    var_10.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    l14 = sub_61BA0(var_4, &var_10);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &l14);
}

// match: sub_61D50 @ 0x00061D50
// sp-match: sub_61D50 @ 0x00050AA0
// "ShouldITurnToTurnLocation": for a soldier, whether it should turn to its
// AI object's target point (sub_61BA0); 0 otherwise.
void sub_61D50(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = 0;
    if (var_4->vf_008() != 0) {
        varC = var_4->vf_120();
        SCRIPT_CHECK(varC != 0);
        if (varC->unk_4F0 != 0)
            local_8 = sub_61BA0(var_4, varC->unk_4F0);
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_61DF0 @ 0x00061DF0
// sp-match: sub_61DF0 @ 0x00050BA0
// "ShouldITurnToTarget": for a soldier, whether it should turn to its AI
// object's tracked entity (sub_61BA0); 0 otherwise.
void sub_61DF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    AIData *ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    v8 = 0;
    if (var_4->vf_008() != 0) {
        ebp_C = var_4->vf_120();
        SCRIPT_CHECK(ebp_C != 0);
        var_10 = ebp_C->unk_1374.sub_D4910();
        if (var_10 != 0)
            v8 = sub_61BA0(var_4, var_10->sub_CD550());
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_61E90 @ 0x00061E90
// sp-match: sub_61E90 @ 0x00050CB0
// "CanSee": whether the entity sees the entity of the object the handle
// arg 1 names: by either one's AI memory record of the other, else by the
// vision tests within its view range; with arg 2, also by the remembered
// record (sub_18F80).
void sub_61E90(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwReal var_3C;
#endif
    RwReal v38;
#ifndef CODFH_SP
    RwBool v34;
#endif
    type_154C0_80 *v30;
    RwInt32 var_2C;
    type_154C0_80 *loc28;
    RwBool slot_24;
    AIData *v20;
    AIData *slot_1C;
    RwInt32 local_18;
    type_3D3548 *local_14;
    RwInt32 local_10;
    type_3D3548 *fp_C;
    RwInt32 lv_8;
    type_3D2E7C *var_4;

    local_18 = 0;
    fp_C = sub_45170(arg_0);
    SCRIPT_CHECK(fp_C != 0);
    local_10 = SCRIPT_ARG(arg_4, 1);
    lv_8 = SCRIPT_ARG(arg_4, 2);
    var_4 = (type_3D2E7C *)sub_67620(local_10);
    SCRIPT_CHECK(var_4 != 0);
    local_14 = var_4->sub_71300();
    SCRIPT_CHECK(local_14 != 0);
    if (local_14 != 0) {
        slot_1C = fp_C->vf_120();
        if (slot_1C != 0) {
            var_2C = 1;
            v20 = local_14->vf_120();
            loc28 = slot_1C->sub_16ED0(local_14, &slot_24);
            if (v20 != 0) {
                if (loc28 != 0 && slot_24 != 0) {
                    var_2C = 0;
                    local_18 = loc28->unk_04 & 1;
                } else {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot as SP 0x50CB0 does
                    RwBool v34;
#endif
                    v30 = v20->sub_16ED0(fp_C, &v34);
                    if (v30 != 0 && v34 != 0) {
                        var_2C = 0;
                        local_18 = v30->unk_04 & 1;
                    }
                }
            }
            if (var_2C != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot as SP 0x50CB0 does
                RwReal var_3C;
#endif
                (v38 = fp_C->vf_10C()) *= v38;
                if (sub_414F0(fp_C, local_14, v38, &var_3C)) {
                    if (sub_413E0(fp_C, local_14)) {
                        if (sub_41AD0(fp_C, local_14))
                            local_18 = 1;
                    } else if (sub_415E0(fp_C, local_14) && sub_421C0(fp_C, local_14))
                        local_18 = 1;
                }
            }
            if (lv_8 != 0 && local_18 == 0 && loc28 != 0 && slot_24 != 0
                && slot_1C->sub_18F80(local_14, loc28))
                local_18 = 1;
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_18);
}

// match: sub_620E0 @ 0x000620E0
// sp-match: sub_620E0 @ 0x00050F20
// "CanPotentiallySee": as "CanSee", by the records' bit 1 and without the
// line check sub_415E0.
void sub_620E0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwReal var_3C;
#endif
    RwReal v38;
#ifndef CODFH_SP
    RwBool v34;
#endif
    type_154C0_80 *v30;
    RwInt32 var_2C;
    type_154C0_80 *loc28;
    RwBool slot_24;
    AIData *v20;
    AIData *slot_1C;
    type_3D3548 *local_18;
    RwInt32 local_14;
    RwInt32 local_10;
    type_3D3548 *fp_C;
    RwInt32 lv_8;
    type_3D2E7C *var_4;

    local_14 = 0;
    fp_C = sub_45170(arg_0);
    SCRIPT_CHECK(fp_C != 0);
    local_10 = SCRIPT_ARG(arg_4, 1);
    lv_8 = SCRIPT_ARG(arg_4, 2);
    var_4 = (type_3D2E7C *)sub_67620(local_10);
    if (var_4 != 0) {
        local_18 = var_4->sub_71300();
        SCRIPT_CHECK(local_18 != 0);
        if (local_18 != 0) {
            slot_1C = fp_C->vf_120();
            if (slot_1C != 0) {
                var_2C = 1;
                v20 = local_18->vf_120();
                loc28 = slot_1C->sub_16ED0(local_18, &slot_24);
                if (v20 != 0) {
                    if (loc28 != 0 && slot_24 != 0) {
                        var_2C = 0;
                        local_14 = (loc28->unk_04 >> 1) & 1;
                    } else {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot as SP 0x50F20 does
                        RwBool v34;
#endif
                        v30 = v20->sub_16ED0(fp_C, &v34);
                        if (v30 != 0 && v34 != 0) {
                            var_2C = 0;
                            local_14 = (v30->unk_04 >> 1) & 1;
                        }
                    }
                }
                if (var_2C != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 shares its slot as SP 0x50F20 does
                    RwReal var_3C;
#endif
                    (v38 = fp_C->vf_10C()) *= v38;
                    if (sub_414F0(fp_C, local_18, v38, &var_3C)) {
                        if (sub_413E0(fp_C, local_18)) {
                            if (sub_41AD0(fp_C, local_18))
                                local_14 = 1;
                        } else if (sub_421C0(fp_C, local_18))
                            local_14 = 1;
                    }
                }
                if (lv_8 != 0 && local_14 == 0 && loc28 != 0 && slot_24 != 0
                    && slot_1C->sub_18F80(local_18, loc28))
                    local_14 = 1;
            }
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_14);
}

// match: sub_62310 @ 0x00062310
// sp-match: sub_62310 @ 0x00051150
// "GetCollisionDistanceToPoint": how far the line from the entity to
// (arg 1, arg 2, arg 3) is clear (sub_61700).
void sub_62310(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d lv_14;
    RwReal local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    lv_14.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    lv_14.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    lv_14.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    sub_61700(var_4, var_4->sub_CD550(), &lv_14, &local_8, 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_623E0 @ 0x000623E0
// sp-match: sub_623E0 @ 0x00051240
// "SetPlayerPosture": player 0's posture arg 1.
void sub_623E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(0);
    SCRIPT_CHECK(var_4 != 0);
    var_4->vf_238(local_8);
    sub_44350(arg_4, 0);
}

// match: sub_62450 @ 0x00062450
// sp-match: sub_62450 @ 0x000512D0
// "GetPlayerPosture": player 0's posture (vf_0BC).
void sub_62450(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_1745A0(0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = var_4->vf_0BC();
    sub_44350(arg_4, &local_8);
}

// match: sub_624A0 @ 0x000624A0
// sp-match: sub_624A0 @ 0x00051370
// "SetPosture": the entity's posture arg 1.
void sub_624A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_0B0(local_8, 1);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_62520 @ 0x00062520
// sp-match: sub_62520 @ 0x00051400
// "GetPosture": the entity's posture.
void sub_62520(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = var_4->vf_0AC();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_62570 @ 0x00062570
// sp-match: sub_62570 @ 0x000514A0
// "SetAttackStandHoldCount": the entity's AI object's attack stand hold
// count arg 1.
void sub_62570(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwReal var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    SCRIPT_CHECK(local_8->vf_120() != 0);
    local_8->vf_120()->set_unk_74(var_4);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_62610 @ 0x00062610
// sp-match: sub_62610 @ 0x00051580
// "GetAttackStandPosture": the attack posture for the entity's posture:
// 0x12 when standing (7, 0x12, 0x18, 0x2A), 8 when crouching (8, 0x17,
// 0x2B, 0x40), else 4.
void sub_62610(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    varC = var_4->vf_0AC();
    switch (varC) {
    case 7:
    case 0x12:
    case 0x18:
    case 0x2A:
        local_8 = 0x12;
        break;
    case 8:
    case 0x17:
    case 0x2B:
    case 0x40:
        local_8 = 8;
        break;
    default:
        local_8 = 4;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_626E0 @ 0x000626E0
// sp-match: sub_626E0 @ 0x000516A0
// "SetFireAtNoTarget": whether a soldier fires at no target (arg 1), which
// also refreshes it (vf_1B4).
void sub_626E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4->vf_008() != 0) {
        var_4->vf_008()->vf_24C(local_8);
        var_4->vf_008()->unk_3E0.set_unk_A0(local_8 == 0);
        var_4->vf_008()->vf_1B4(1);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_627C0 @ 0x000627C0
// sp-match: sub_627C0 @ 0x00051770
// "IsValidAIObj": whether the handle arg 1 names an object with an entity.
void sub_627C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    type_3D2E7C *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    var_4 = 0;
    v8 = SCRIPT_ARG(arg_4, 1);
    if (v8 != 0) {
        ebp_C = (type_3D2E7C *)sub_67620(v8);
        if (ebp_C != 0) {
            var_10 = ebp_C->sub_71300();
            if (var_10 != 0)
                var_4 = 1;
        }
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_62840 @ 0x00062840
// sp-match: sub_62840 @ 0x00051800
// "SetThrobbing": whether the entity throbs (arg 1).
void sub_62840(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;
    type_3D3548 *local_8;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8->vf_1E8(var_4);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_628C0 @ 0x000628C0
// sp-match: sub_628C0 @ 0x00051890
// "SetActionItem": the entity's action item arg 1.
void sub_628C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4->vf_1D8(local_8);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_62940 @ 0x00062940
// sp-match: sub_62940 @ 0x00051920
// "SetAlerted": whether the entity's AI object is alerted (arg 1).
void sub_62940(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    AIData *local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        local_8 = var_4->vf_120();
        SCRIPT_CHECK(local_8 != 0);
        if (local_8 != 0) {
            varC = SCRIPT_ARG(arg_4, 1);
            local_8->unk_520 = varC;
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_629E0 @ 0x000629E0
// sp-match: sub_629E0 @ 0x000519F0
// "IsAlerted": whether the entity's AI object is alerted.
void sub_629E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0) {
        varC = var_4->vf_120();
        SCRIPT_CHECK(varC != 0);
        if (varC != 0)
            local_8 = varC->get_unk_520();
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_62A60 @ 0x00062A60
// sp-match: sub_62A60 @ 0x00051AE0
// "SetCameraMode": the camera's mode arg 1 (keeping the previous one); its
// flags become 0x14 for mode 0, else 0x10.
void sub_62A60(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_62A60 *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 != 0);
    if ((local_8->unk_2C & 0x3FFFFF0) == 0x100000) {  // not an address: entity kind bits
        varC = (type_62A60 *)local_8;
        varC->unk_418 = varC->unk_414;
        varC->unk_414 = var_4;
        sub_157680();
        if (var_4 == 0)
            varC->unk_28 = 0x14;
        else
            varC->unk_28 = 0x10;
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_62B20 @ 0x00062B20
// sp-match: sub_62B20 @ 0x00051BA0
// "SetCameraAlignTargetFromNamedPoint": for the camera, the matrix of the
// object under the key arg 1 (two slots; kind 0x2E: its entity's frame or
// its trigger's matrix; kind 0x2D: its own): with arg 2 the bits of 1.0f,
// moves the camera onto it (RwFrameTransform) and sends "IHaveArrived"
// with the time step, else aims at it with arg 2.
void sub_62B20(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_3C;
    RwMatrix *v38;
    type_3D2E7C *v34;
    RwFrame *v30;
    type_3DFED8 *var_2C;
    type_712B0 *loc28;
    RwFrame *slot_24;
    type_3DFEEC *v20;
    type_3DF8D8_04 *slot_1C;
    RwInt32 local_18;
    type_3D3548 *local_14;
    type_3DF8D8 *local_10;
    type_62A60 *fp_C;
    RwMatrix *lv_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if ((var_4->unk_2C & 0x3FFFFF0) == 0x100000) {  // not an address: entity kind bits
        fp_C = (type_62A60 *)var_4;
        lv_8 = 0;
        slot_1C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
        SCRIPT_CHECK(slot_1C != 0);
        local_10 = sub_198800(slot_1C);
        SCRIPT_CHECK(local_10 != 0);
        local_14 = 0;
        if (local_10 != 0 && local_10->vf_008() == 0x2E) {
            v20 = (type_3DFEEC *)local_10;
            SCRIPT_CHECK(v20->unk_10 != 0);
            local_14 = ((type_D48D0 *)&v20->unk_24_id)->sub_D4910();
            if (local_14 != 0) {
                slot_24 = local_14->get_unk_340();
                lv_8 = RwFrameGetLTM(slot_24);
            } else {
                loc28 = v20->unk_2C_trigger;
                lv_8 = (RwMatrix *)loc28->unk_60;
            }
            sub_44220(lv_8 != 0);
        } else if (local_10 != 0 && local_10->vf_008() == 0x2D) {
            var_2C = (type_3DFED8 *)local_10;
            lv_8 = (RwMatrix *)var_2C->unk_10;
            sub_44220(lv_8 != 0);
        } else
            sub_44220(0);
#ifdef CODFH_SP // single player compares arg 2 as a real with 1.0f (SP 0x51BA0: fucompp)
        if (SCRIPT_ARGT<RwReal>(arg_4, 2) == 1.0f) {
#else
        local_18 = SCRIPT_ARG(arg_4, 2);
        if (local_18 == 0x3F800000) {     // not an address: the bits of 1.0f
#endif
            v30 = fp_C->get_unk_340();
            RwFrameTransform(v30, lv_8, rwCOMBINEREPLACE);
            RwFrameUpdateObjects(v30);
            v38 = RwFrameGetMatrix(v30);
            ((type_3DD948 *)fp_C)->sub_1752A0(v38);
            v34 = fp_C->vf_098();
            if (v34 != 0) {
                var_3C = deltaTime;
                sub_6B5F0("IHaveArrived", (type_67620 *)v34, 0, 0, (RwInt32 *)(&var_3C), 1, 1, 0);
            }
        } else {
            ((type_3DD948 *)fp_C)->sub_175F00(lv_8);
            fp_C->set_unk_410(SCRIPT_ARG(arg_4, 2));
        }
        {
            // A local the image reserves and never uses.
            RwInt32 unused_0;
        }
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out
    }
#else
    } else
        sub_19A750("Attempting to set the camera align target on a non-camera entity\n");
#endif
    sub_44350(arg_4, 0);
}

// match: sub_62DD0 @ 0x00062DD0
// sp-match: sub_62DD0 @ 0x00051E30
// "SetCameraSplinePathFromName": the camera's spline path, that of the
// kind-0x2E object (flags 0x80) under the key arg 1 (two slots).
void sub_62DD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *l14;
    type_3DFEEC *var_10;
    type_3DF8D8 *ebp_C;
    type_62A60 *v8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if ((var_4->unk_2C & 0x3FFFFF0) == 0x100000) {  // not an address: entity kind bits
        v8 = (type_62A60 *)var_4;
        l14 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
        ebp_C = sub_198800(l14);
        SCRIPT_CHECK(ebp_C != 0);
        SCRIPT_CHECK(ebp_C->vf_008() == 0x2E);
        var_10 = (type_3DFEEC *)ebp_C;
        SCRIPT_CHECK(var_10->unk_10 == 0x80);
        // These two checks reserve no slots.
        sub_44220(var_10->unk_24 != 0);
        sub_44220(var_10->unk_24 != 0);
        {
            // A local the image reserves and never uses.
            RwInt32 unused_0;
        }
        v8->unk_42C = var_10->get_unk_24();
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out
    }
#else
    } else
        sub_19A750("Attempting to set the camera spline on a non-camera entity");
#endif
    sub_44350(arg_4, 0);
}

// match: sub_62EF0 @ 0x00062EF0
// sp-match: sub_62EF0 @ 0x00052010
// "ResetCameraZoom": player 0's camera zoom.
void sub_62EF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *var_4;

    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0)
        var_4->sub_104F70();
    sub_44350(arg_4, 0);
}

// match: sub_62F30 @ 0x00062F30
// sp-match: sub_62F30 @ 0x00052040
// "SetPlayerBumpRadius": the entity's bump radius arg 1.
void sub_62F30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4 != 0)
        var_4->set_unk_380(SCRIPT_ARG(arg_4, 1));
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_62FB0 @ 0x00062FB0
// sp-match: sub_62FB0 @ 0x000520C0
// "GetClosestAlarmPoint": the entity's AI object's closest alarm point
// (sub_28780), or 0.
void sub_62FB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    local_8 = 0;
    if (var_4 != 0) {
        varC = var_4->vf_120();
        SCRIPT_CHECK(varC != 0);
        if (varC != 0)
            local_8 = varC->sub_28780();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_63030 @ 0x00063030
// sp-match: sub_63030 @ 0x000521B0
// "SetAlarmPathNodeOccupied": marks the alarm node (filter 0xF) nearest the
// entity within 2000 occupied or free (arg 1).
void sub_63030(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_68;
    type_3D3548 *local_64;

    var_68 = SCRIPT_ARG(arg_4, 1);
    local_64 = sub_45170(arg_0);
    type_154C0_1048 local_60;
    local_60.unk_04 = *local_64->sub_CD550();
    local_60.unk_10 = 2000.0f;
    local_60.unk_00 = 0;
    local_60.unk_18 = sub_F7E80(0xF);
    local_60.unk_1C = 0;
    sub_F8970(&local_60, 1, 0);
    if (local_60.unk_34 != 0)
        local_60.unk_34->unk_00_2 = var_68;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63110 @ 0x00063110
// sp-match: sub_63110 @ 0x00052270
// "GetClosestAlarmObject": finds the handle of the AI object of the alarm
// (an animated background entity of type 1) nearest the entity, if one is
// within 300, but passes 0 to sub_44350 rather than it, so the command
// always gives 0.
// Local names state their slots; plain var_N names reorder them (docs/toolchain.md).
void sub_63110(RwUInt32 arg_0, type_44350 *arg_4)
{
    // A local the image reserves and never uses.
    RwInt32 ebp_34;
    RwUInt32 var_30;
    RwV3d bp_2C;
    RwReal local_20;
    type_545C0 *var_1C;
    type_3D3548 *var18;
    RwInt32 stk_14;
    type_545C0 *l10;
    RwReal local_C;
    type_3D3548 *lv_8;
    RwUInt32 var_4;

    var_4 = 0;
    lv_8 = sub_45170(arg_0);
    local_C = 1.0e37f;
    l10 = 0;
    for (stk_14 = 0; stk_14 < 16; stk_14++) {
        for (var18 = dword_4B8600[stk_14].unk_00; var18 != 0; var18 = var18->unk_10) {
            if (var18->unk_2C_8) {
                var_1C = (type_545C0 *)var18;
                if (var_1C->get_unk_3D4() == 1) {
                    bp_2C = *var_1C->sub_CD550();
                    RwV3dSub(&bp_2C, &bp_2C, lv_8->sub_CD550());
                    local_20 = RwV3dDotProduct(&bp_2C, &bp_2C);
                    if (local_20 < local_C) {
                        local_C = local_20;
                        l10 = var_1C;
                    }
                }
            }
        }
    }
    if (l10 != 0 && local_C < 90000.0f && l10->vf_098() != 0) {
        var_30 = l10->vf_098()->get_unk_04_d();
        var_4 = var_30;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63290 @ 0x00063290
// sp-match: sub_63290 @ 0x000523A0
// "GetPlayerEntity": the handle of player arg 1, or 0.
void sub_63290(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    ebp_C = 0;
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = sub_1745A0(var_4);
    if (v8 != 0) {
        var_10 = v8->unk_384;
        ebp_C = var_10;
    }
    sub_44350(arg_4, &ebp_C);
}

// match: sub_63310 @ 0x00063310
// sp-match: sub_63310 @ 0x00052420
// "GetPlayerAIObject": the handle of player arg 1's object.
void sub_63310(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = sub_1745A0(var_4);
    varC = local_8->vf_098()->get_unk_04();
    sub_44350(arg_4, &varC);
}

// match: sub_63390 @ 0x00063390
// sp-match: sub_63390 @ 0x00052490
// "DisableAnimBlending": the object must blend (vf_014 1); clears its blend
// flag and weight.
void sub_63390(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *var_4;

    var_4 = sub_67620(arg_0);
    SCRIPT_CHECK(var_4->vf_014() == 1);
    var_4->set_unk_129(0);
    var_4->unk_124 = 0.0f;
    sub_44350(arg_4, 0);
}

// match: sub_633F0 @ 0x000633F0
// sp-match: sub_633F0 @ 0x00052510
// "SetHudVisible": shows or hides (arg 1) the HUD's elements 0x61 (or 3),
// 0x1D and 0x7A, passes its own state to 0x6A to 0x73, and shows 0x90 while
// that state is set.
void sub_633F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    if (dword_4B9190 != 0) {
#ifdef CODFH_SP // single player's HUD element numbers (SP 0x52510)
        if (dword_4B9190->unk_08 != 0)
            dword_4B9190->sub_E09E0(0x38, var_4);
        else
            dword_4B9190->sub_E09E0(3, var_4);
        dword_4B9190->sub_E09E0(0x1D, var_4);
        dword_4B9190->sub_E09E0(0x4B, var_4);
        for (local_8 = 0x41; local_8 < 0x4B; local_8++)
            dword_4B9190->sub_E09E0(local_8, dword_4B9190->unk_00);
        if (dword_4B9190->unk_00 != 0)
            dword_4B9190->sub_E09E0(0x61, var_4);
#else
        if (dword_4B9190->unk_08 != 0)
            dword_4B9190->sub_E09E0(0x61, var_4);
        else
            dword_4B9190->sub_E09E0(3, var_4);
        dword_4B9190->sub_E09E0(0x1D, var_4);
        dword_4B9190->sub_E09E0(0x7A, var_4);
        for (local_8 = 0x6A; local_8 < 0x74; local_8++)
            dword_4B9190->sub_E09E0(local_8, dword_4B9190->unk_00);
        if (dword_4B9190->unk_00 != 0)
            dword_4B9190->sub_E09E0(0x90, var_4);
#endif
    }
    sub_44350(arg_4, 0);
}

// match: sub_634E0 @ 0x000634E0
// sp-match: sub_634E0 @ 0x000525B0
// "Breakpoint": takes the object's entity and fails its check, for a
// debugger to stop on.
void sub_634E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *local_8;
    type_3D3548 *var_4;

    local_8 = sub_67620(arg_0);
    var_4 = 0;
    if (local_8 != 0)
        var_4 = local_8->vf_024()->sub_71300();
    SCRIPT_CHECK(0);
    sub_44350(arg_4, 0);
}

// match: sub_63540 @ 0x00063540
// sp-match: sub_63540 @ 0x00052620
// "SetVehicleCoverPoint": the entity's AI object takes up its vehicle cover point (sub_231B0).
void sub_63540(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_231B0();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_635A0 @ 0x000635A0
// sp-match: sub_635A0 @ 0x000526E0
// "ClearVehicleCoverPoint": the entity's AI object leaves its vehicle cover point (sub_23860).
void sub_635A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_23860();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63600 @ 0x00063600
// sp-match: sub_63600 @ 0x000527A0
// "GetVehicleAIObjFromVehicleCoverPoint": the handle of the vehicle whose
// cover point the entity's AI object holds (sub_232F0), or 0.
void sub_63600(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwUInt32 stk_18;
    type_3D2E7C *l14;
    type_3D3548 *var_10;
    type_3D3548 *ebp_C;
    RwUInt32 v8;
    AIData *var_4;

    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    var_4 = ebp_C->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    v8 = 0;
    var_10 = var_4->sub_232F0();
    if (var_10 != 0) {
        l14 = var_10->vf_098();
        if (l14 != 0) {
            stk_18 = l14->unk_04;
            v8 = stk_18;
        }
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_636A0 @ 0x000636A0
// sp-match: sub_636A0 @ 0x000528A0
// "SetVehicleToFollow": the entity's AI object follows the vehicle (flags
// 0x40080) of the object the handle arg 1 names, or nothing.
void sub_636A0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    AIData *v8;
    type_3D2E7C *var_4;

    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_120();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    var_10 = SCRIPT_ARG(arg_4, 1);
    if (var_10 != 0) {
        var_4 = (type_3D2E7C *)sub_67620(var_10);
        SCRIPT_CHECK(var_4 != 0);
    }
    if (var_4 != 0) {
        l14 = var_4->sub_71300();
        if (l14->unk_2C & 0x40080)   // not an address: entity kind bits
            v8->unk_1370.sub_D48D0(l14);
        else {
            v8->unk_1370.sub_D48D0(0);
            SCRIPT_CHECK(0);
        }
    } else
        v8->unk_1370.sub_D48D0(0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_637B0 @ 0x000637B0
// sp-match: sub_637B0 @ 0x00052A20
// "SetCurrentEntityFollowed": the entity's AI object follows the entity of
// the object the handle arg 1 names in mode arg 2 (0 to 4, or -1), or
// nothing (sub_20C50).
void sub_637B0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *stk_18;
    RwInt32 l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    AIData *v8;
    type_3D2E7C *var_4;

    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_120();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    l14 = SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK((var_10 >= 0 && var_10 < 5) || var_10 == -1);
    if (l14 != 0) {
        var_4 = (type_3D2E7C *)sub_67620(l14);
        SCRIPT_CHECK(var_4 != 0);
    }
    if (var_4 != 0) {
        stk_18 = var_4->sub_71300();
        if (stk_18 != 0)
            v8->sub_20C50(stk_18, var_10);
        else {
            // This check reserves no slots.
            sub_44220(0);
            v8->sub_20C50(0, var_10);
        }
    } else
        v8->sub_20C50(0, -1);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63900 @ 0x00063900
// sp-match: sub_63900 @ 0x00052BE0
// "SetCurrentEntityFollowedOnSpline": the entity's AI object follows the
// entity of the object the handle arg 1 names along the spline of the
// object under the key arg 6 (sub_20DA0: mode arg 2, 0 or 1; follow mode
// arg 3; leashes arg 4 and arg 5), or nothing.
void sub_63900(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_28;
    RwInt32 local_24;
    RwReal local_20;
    type_3DF8D8_04 *var_1C;
    RwInt32 var18;
    type_3D3548 *stk_14;
    RwInt32 l10;
    RwReal local_C;
    AIData *lv_8;
    type_3D2E7C *var_4;

    stk_14 = sub_45170(arg_0);
    SCRIPT_CHECK(stk_14 != 0);
    lv_8 = stk_14->vf_120();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = 0;
    local_24 = SCRIPT_ARG(arg_4, 1);
    l10 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(l10 >= 0 && l10 < 2);
    var18 = SCRIPT_ARG(arg_4, 3);
    SCRIPT_CHECK((var18 >= 0 && var18 < 5) || var18 == -1);
    local_C = SCRIPT_ARGT<RwReal>(arg_4, 4);
    local_20 = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_1C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 6);
    // This check and the next reserve no slots.
    sub_44220(var_1C != 0);
    if (local_24 != 0) {
        var_4 = (type_3D2E7C *)sub_67620(local_24);
        sub_44220(var_4 != 0);
    }
    if (var_4 != 0) {
        local_28 = var_4->sub_71300();
        if (local_28 != 0)
            lv_8->sub_20DA0(local_28, l10, var18, local_C, local_20, var_1C);
        else {
            sub_44220(0);
            lv_8->sub_20C50(0, -1);
        }
    } else
        lv_8->sub_20C50(0, -1);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63B40 @ 0x00063B40
// sp-match: sub_63B40 @ 0x00052E50
// "RegisterEntityFollowed": the entity's AI object registers the entity of
// the object the handle arg 1 names as followed (sub_20BA0), or none
// (sub_20C00).
void sub_63B40(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    AIData *v8;
    type_3D2E7C *var_4;

    ebp_C = sub_45170(arg_0);
    SCRIPT_CHECK(ebp_C != 0);
    v8 = ebp_C->vf_120();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    var_10 = SCRIPT_ARG(arg_4, 1);
    if (var_10 != 0) {
        var_4 = (type_3D2E7C *)sub_67620(var_10);
        SCRIPT_CHECK(var_4 != 0);
    }
    if (var_4 != 0) {
        l14 = var_4->sub_71300();
        if (l14 != 0)
            v8->sub_20BA0(l14);
        else {
            SCRIPT_CHECK(0);
            v8->sub_20C00();
        }
    } else
        v8->sub_20C00();
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63C30 @ 0x00063C30
// sp-match: sub_63C30 @ 0x00052F90
// "UnRegisterEntityFollowed": the entity's AI object follows no one
// (sub_20C00).
void sub_63C30(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    var_4->sub_20C00();
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63C90 @ 0x00063C90
// sp-match: sub_63C90 @ 0x00053050
// "GetAngularYDiffToObj": the turn, in degrees, from the entity's heading
// (sub_CD5A0) to the heading towards the entity of the object the handle
// arg 1 names; 1e37 without one.
void sub_63C90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal ebp_34;
    RwReal var_30;
    RwV3d bp_2C;
    RwV3d ebp_20;
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3D2E7C *ebp_C;
    type_3D3548 *v8;
    RwReal var_4;

    v8 = sub_45170(arg_0);
    SCRIPT_CHECK(v8 != 0);
    var_4 = 1e37f;
    if (v8 != 0) {
        ebp_C = 0;
        var_10 = SCRIPT_ARG(arg_4, 1);
        if (var_10 != 0)
            ebp_C = (type_3D2E7C *)sub_67620(var_10);
        if (ebp_C != 0) {
            l14 = ebp_C->sub_71300();
            if (l14 != 0) {
                RwV3dSubMacro(&ebp_20, l14->sub_CD550(), v8->sub_CD550());
                ebp_20.y = 0.0f;
                RwV3dNormalize(&ebp_20, &ebp_20);
#ifdef CODFH_SP // sub_2C1E0 expanded inline (SP 0x53050: fpatan)
                var_30 = (RwReal)atan2(ebp_20.z, ebp_20.x) * 57.295776f;
#else
                var_30 = sub_2C1E0(&ebp_20) * 57.295776f;
#endif
                var_30 = sub_13F9E0(var_30);
                bp_2C = *v8->sub_CD5A0();
                bp_2C.y = 0.0f;
                RwV3dNormalize(&bp_2C, &bp_2C);
#ifdef CODFH_SP // sub_2C1E0 expanded inline (SP 0x53050: fpatan)
                ebp_34 = (RwReal)atan2(bp_2C.z, bp_2C.x) * 57.295776f;
#else
                ebp_34 = sub_2C1E0(&bp_2C) * 57.295776f;
#endif
                ebp_34 = sub_13F9E0(ebp_34);
                var_4 = RWS::DegAngDiff(var_30, ebp_34);
            }
        }
    }
    {
        // Five locals the image reserves and never uses.
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_63E50 @ 0x00063E50
// sp-match: sub_63E50 @ 0x00053220
// "GetAIAction": the entity's AI object's action (unk_5C), or 0.
void sub_63E50(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = 0;
    if (local_8 != 0) {
        varC = local_8->vf_120();
        if (varC != 0)
            var_4 = varC->unk_5C;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_63EC0 @ 0x00063EC0
// sp-match: sub_63EC0 @ 0x000532D0
// "SetCoverPointSearch": the entity's AI object's cover point search arg 1 (sub_22EF0).
void sub_63EC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4->sub_22EF0(varC);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_63F50 @ 0x00063F50
// sp-match: sub_63F50 @ 0x000533A0
// "GetCoverPointSearch": the entity's AI object's cover point search
// (unk_DD4).
void sub_63F50(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    varC = var_4->get_unk_DD4();
    sub_44350(arg_4, &varC);
}

// match: sub_63FC0 @ 0x00063FC0
// sp-match: sub_63FC0 @ 0x00053480
// "SetVehicleCoverPointSearch": the entity's AI object's vehicle cover point search arg 1 (sub_22F30).
void sub_63FC0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    var_4->sub_22F30(varC);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64050 @ 0x00064050
// sp-match: sub_64050 @ 0x00053550
// "GetVehicleCoverPointSearch": the entity's AI object's vehicle cover point search (unk_136C).
void sub_64050(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    varC = var_4->get_unk_136C();
    sub_44350(arg_4, &varC);
}

// match: sub_640C0 @ 0x000640C0
// sp-match: sub_640C0 @ 0x00053630
// "SetCoverPointSearchType": the entity's AI object's cover point search
// type arg 1 (0 to 2; sub_23CD0).
void sub_640C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC >= 0 && varC < 3);
    var_4->sub_23CD0(varC, 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64170 @ 0x00064170
// sp-match: sub_64170 @ 0x00053740
// "GetCoverPointSearchType": the entity's AI object's cover point search type (unk_DD0).
void sub_64170(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    varC = var_4->get_unk_DD0();
    sub_44350(arg_4, &varC);
}

// match: sub_641E0 @ 0x000641E0
// sp-match: sub_641E0 @ 0x00053820
// "SetCoverPointSearchRadius": the entity's AI object's cover point search
// radius arg 1.
void sub_641E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal varC;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    SCRIPT_CHECK(var_4 != 0);
    varC = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4->unk_F6C = varC;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64270 @ 0x00064270
// sp-match: sub_64270 @ 0x000538F0
// "IsDefendAreaSelectedBetter": sub_25A50 of the entity's AI object, or 0.
void sub_64270(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        varC = var_4->vf_120();
        SCRIPT_CHECK(varC != 0);
        local_8 = varC->sub_25A50();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_642E0 @ 0x000642E0
// sp-match: sub_642E0 @ 0x000539A0
// "GetEntityType": the kind bits (unk_2C & 0x3FFFFF0) of the entity of the
// object the handle arg 1 names, or 0.
void sub_642E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3D2E7C *ebp_C;
    type_3D3548 *v8;
    RwInt32 var_4;

    v8 = sub_45170(arg_0);
    var_4 = 0;
    if (v8 != 0) {
        var_10 = SCRIPT_ARG(arg_4, 1);
        ebp_C = (type_3D2E7C *)sub_67620(var_10);
        if (ebp_C != 0) {
            l14 = ebp_C->sub_71300();
            if (l14 != 0)
                var_4 = l14->unk_2C & 0x3FFFFF0;     // not an address: entity kind bits
        }
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_64380 @ 0x00064380
// sp-match: sub_64380 @ 0x00053A40
// "OccupyVehicleCoverpointSelected": whether the entity's AI object takes
// the vehicle cover point it selected (unk_133C; sub_23050).
void sub_64380(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_154C0_12F4 *l14;
    AIData *var_10;
    type_14D180 *ebp_C;
    RwInt32 v8;
    type_3D3548 *var_4;

    v8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        var_10 = var_4->vf_120();
        SCRIPT_CHECK(var_10 != 0);
        l14 = &var_10->unk_133C;
        ebp_C = var_10->sub_23050(l14);
        if (ebp_C != 0)
            v8 = 1;
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_64400 @ 0x00064400
// sp-match: sub_64400 @ 0x00053B00
// "EnableVehicleCoverPoints": turns the cover points of the vehicle entity
// of the object the handle arg 1 names on or off (arg 2).
void sub_64400(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 l14;
    type_3DBC78 *var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    type_3D2E7C *var_4;

    var_4 = 0;
    v8 = SCRIPT_ARG(arg_4, 1);
    if (v8 != 0) {
        var_4 = (type_3D2E7C *)sub_67620(v8);
        SCRIPT_CHECK(var_4 != 0);
    }
    if (var_4 != 0) {
        var_10 = 0;
        ebp_C = var_4->sub_71300();
        if (ebp_C != 0)
            var_10 = ebp_C->vf_010();
        if (var_10 != 0) {
            l14 = SCRIPT_ARG(arg_4, 2);
            var_10->sub_154E30(l14);
        }
    }
    sub_44350(arg_4, 0);
}

// match: sub_644E0 @ 0x000644E0
// sp-match: sub_644E0 @ 0x00053BB0
// "OccupyDefendAreaCoverPointSelected": sub_233B0 of the entity's AI object, or 0.
void sub_644E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    AIData *varC;
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        varC = var_4->vf_120();
        SCRIPT_CHECK(varC != 0);
        local_8 = varC->sub_233B0();
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &local_8);
}

// match: sub_64550 @ 0x00064550
// sp-match: sub_64550 @ 0x00053C60
// "SetUpdateCallBack": the entity's update callback (arg 1, arg 2, arg 3;
// vf_204).
void sub_64550(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_10;
    type_3D3548 *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    ebp_C = sub_45170(arg_0);
    var_4 = SCRIPT_ARG(arg_4, 1);
    var_10 = SCRIPT_ARG(arg_4, 2);
    v8 = SCRIPT_ARG(arg_4, 3);
    if (ebp_C != 0)
        ebp_C->vf_204(var_4, var_10, v8);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64620 @ 0x00064620
// sp-match: sub_64620 @ 0x00053CD0
// "DistanceToDestination": from its entity to its AI object's destination.
void sub_64620(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_4;
    type_3D3548 *var_8;
    AIData *var_C;
    RwV3d var_18;

    var_4 = 0.0f;
    var_8 = sub_45170(arg_0);
    if (var_8)
    {
        var_C = var_8->vf_120();
        if (var_C)
        {
            RwV3dSubMacro(&var_18, var_8->sub_CD550(), &var_C->unk_4E4);
            var_4 = RwV3dDotProductMacro(&var_18, &var_18);
            do
            {
                __m128 var_40 = _mm_set_ss(var_4);
                __m128 var_70 = _mm_sqrt_ss(var_40);
                _mm_store_ss(&var_4, var_70);
            } while (0);
        }
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_64740 @ 0x00064740
// sp-match: sub_64740 @ 0x00053DD0
// "DistanceToEnemy": from its entity to its AI object's target of the kind
// arg 1 (sub_1FCC0); -1 without one.
void sub_64740(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_4;
    type_3D3548 *var_8;
    RwInt32 var_C;
    AIData *var_10;
    type_3D3548 *var_14;
    RwV3d var_24;

    var_4 = -1.0f;
    var_8 = sub_45170(arg_0);
    var_C = SCRIPT_ARG(arg_4, 1);
    if (var_8)
    {
        var_10 = var_8->vf_120();
        if (var_10)
        {
            var_14 = var_10->sub_1FCC0(var_C, 0);
            if (var_14)
            {
                RwV3dSubMacro(&var_24, var_8->sub_CD550(), var_14->sub_CD550());
                var_4 = RwV3dDotProductMacro(&var_24, &var_24);
                do
                {
                    __m128 var_50 = _mm_set_ss(var_4);
                    __m128 var_80 = _mm_sqrt_ss(var_50);
                    _mm_store_ss(&var_4, var_80);
                } while (0);
            }
            else
            {
                sub_44220(0);
            }
        }
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_648C0 @ 0x000648C0
// sp-match: sub_648C0 @ 0x00053F40
// "DistanceToEnemyDeadOrAlive": as "DistanceToEnemy", counting dead ones.
void sub_648C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal var_4;
    type_3D3548 *var_8;
    RwInt32 var_C;
    AIData *var_10;
    type_3D3548 *var_14;
    RwV3d var_24;

    var_4 = -1.0f;
    var_8 = sub_45170(arg_0);
    var_C = SCRIPT_ARG(arg_4, 1);
    if (var_8)
    {
        var_10 = var_8->vf_120();
        if (var_10)
        {
            var_14 = var_10->sub_1FCC0(var_C, 1);
            if (var_14)
            {
                RwV3dSubMacro(&var_24, var_8->sub_CD550(), var_14->sub_CD550());
                var_4 = RwV3dDotProductMacro(&var_24, &var_24);
                do
                {
                    __m128 var_50 = _mm_set_ss(var_4);
                    __m128 var_80 = _mm_sqrt_ss(var_50);
                    _mm_store_ss(&var_4, var_80);
                } while (0);
            }
            else
            {
                sub_44220(0);
            }
        }
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_64A40 @ 0x00064A40
// sp-match: sub_64A40 @ 0x000540B0
// "GetDistanceFromObject": the distance from the entity to the entity of
// the object the handle arg 1 names.
void sub_64A40(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d ebp_20;
    type_3D3548 *l14;
    RwInt32 var_10;
    type_3D2E7C *ebp_C;
    RwReal v8;
    type_3D3548 *var_4;

    v8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        var_10 = SCRIPT_ARG(arg_4, 1);
        ebp_C = (type_3D2E7C *)sub_67620(var_10);
        if (ebp_C != 0) {
            l14 = ebp_C->sub_71300();
            if (l14 != 0) {
                RwV3dSubMacro(&ebp_20, l14->sub_CD550(), var_4->sub_CD550());
                v8 = RwV3dLength((RwV3d *)&ebp_20);
            } else
                SCRIPT_CHECK(0);
        } else
            SCRIPT_CHECK(0);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_64B60 @ 0x00064B60
// sp-match: sub_64B60 @ 0x000541F0
// "GetDistanceFromCurrentCoverPoint": the distance from the entity to its
// AI object's cover node (unk_F60), or 0.
void sub_64B60(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d var_1C;
    type_F8350 *l10;
    AIData *local_C;
    RwReal lv_8;
    type_3D3548 *var_4;

    lv_8 = 0.0f;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        local_C = var_4->vf_120();
        SCRIPT_CHECK(local_C != 0);
        l10 = local_C->unk_F60;
        if (l10 != 0) {
            RwV3dSubMacro(&var_1C, &l10->unk_10, var_4->sub_CD550());
            lv_8 = RwV3dLength((RwV3d *)&var_1C);
#if defined(CODFH_SP) && !defined(CODFH_SP_LOGS) // single player compiles the debug print out
        }
#else
        } else
            sub_19A750("GetDistanceFromCurrentCoverPoint: no current coverpoint to get distance from!\n");
#endif
    }
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_64C40 @ 0x00064C40
// sp-match: sub_64C40 @ 0x000542F0
// "IsWithinRangeOfObject": whether the entity of the object the handle
// arg 1 names lies within distance arg 2 and height arg 3 of the entity
// (sub_35D90).
void sub_64C40(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifndef CODFH_SP
    RwReal local_20;
#endif
    RwReal var_1C;
    RwReal var18;
    type_3D3548 *stk_14;
    RwInt32 l10;
    type_3D2E7C *local_C;
    RwInt32 lv_8;
    type_3D3548 *var_4;

    lv_8 = 0;
    var_4 = sub_45170(arg_0);
    if (var_4 != 0) {
        l10 = SCRIPT_ARG(arg_4, 1);
        local_C = (type_3D2E7C *)sub_67620(l10);
        if (local_C != 0) {
            stk_14 = local_C->sub_71300();
            if (stk_14 != 0) {
#ifdef CODFH_SP // shape: block-scoped, so /O2 gives it lv_8's slot (SP 0x542F0's one-slot frame)
                RwReal local_20 = 0.0f;
#else
                local_20 = 0.0f;
#endif
                var_1C = SCRIPT_ARGT<RwReal>(arg_4, 2);
                var18 = SCRIPT_ARGT<RwReal>(arg_4, 3);
                lv_8 = sub_35D90(var_4, stk_14, var_1C * var_1C, var18 * var18, &local_20);
            } else
                SCRIPT_CHECK(0);
        } else
            SCRIPT_CHECK(0);
    }
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &lv_8);
}

// match: sub_64D70 @ 0x00064D70
// sp-match: sub_64D70 @ 0x00054420
// "PlayerStealthMessageActive": whether player 0's stealth message shows
// (arg 1).
void sub_64D70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(0);
    SCRIPT_CHECK(var_4 != 0);
    var_4->unk_2250 = (bool)(local_8 != 0);
    sub_44350(arg_4, 0);
}

// match: sub_64DF0 @ 0x00064DF0
// sp-match: sub_64DF0 @ 0x000544B0
// "SetGimpVehicleMoveState": the gimp vehicle's (vf_02C) unk_638 arg 1.
void sub_64DF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4->vf_02C() != 0)
        ((type_3DE0E0 *)var_4)->unk_638 = local_8;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64E70 @ 0x00064E70
// sp-match: sub_64E70 @ 0x00054540
// "SetGimpVehicleFireState": the gimp vehicle's (vf_02C) unk_63C arg 1.
void sub_64E70(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = sub_45170(arg_0);
    SCRIPT_CHECK(var_4 != 0);
    if (var_4->vf_02C() != 0)
        ((type_3DE0E0 *)var_4)->unk_63C = local_8;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64EF0 @ 0x00064EF0
// sp-match: sub_64EF0 @ 0x000545D0
// "SetGimpVehicleMoveSpeed": the gimp vehicle's (vf_02C) unk_650 arg 1.
void sub_64EF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    if (local_8->vf_02C() != 0)
        ((type_3DE0E0 *)local_8)->unk_650 = var_4;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64F70 @ 0x00064F70
// sp-match: sub_64F70 @ 0x00054670
// "SetGimpVehicleRotSpeed": the gimp vehicle's (vf_02C) unk_654 arg 1.
void sub_64F70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwReal var_4;

    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    local_8 = sub_45170(arg_0);
    SCRIPT_CHECK(local_8 != 0);
    if (local_8->vf_02C() != 0)
        ((type_3DE0E0 *)local_8)->unk_654 = var_4;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_64FF0 @ 0x00064FF0
// sp-match: sub_64FF0 @ 0x00054710
// "SetSplineOffsetXYZ": the offset (arg 1, arg 2, arg 3) of the entity from
// its spline path: its AI object's (unk_D30), or a type_3DAC58's,
// type_3DDB98's or type_3DA6C0's.
void sub_64FF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d lv_14;
    type_3D3548 *local_8;
    AIData *var_4;

    local_8 = sub_45170(arg_0);
    lv_14.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    lv_14.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    lv_14.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    SCRIPT_CHECK(local_8 != 0);
    var_4 = local_8->vf_120();
    if (var_4 != 0)
        RwMatrixTranslate(&var_4->unk_D30, &lv_14, rwCOMBINEREPLACE);
    else if (local_8->vf_020() != 0)
        RwMatrixTranslate(local_8->vf_020()->get_unk_3D0(), &lv_14, rwCOMBINEREPLACE);
    else if (local_8->vf_024() != 0)
        RwMatrixTranslate(local_8->vf_024()->get_unk_6F0(), &lv_14, rwCOMBINEREPLACE);
    else if (local_8->vf_01C() != 0)
        RwMatrixTranslate(local_8->vf_01C()->get_unk_3F0(), &lv_14, rwCOMBINEREPLACE);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, 0);
}

// match: sub_65180 @ 0x00065180
// sp-match: sub_65180 @ 0x00054820
// "SetSplineOffsetXYZIJK": the offset of the entity from its spline path at
// (arg 1, arg 2, arg 3) facing the direction (arg 4, arg 5, arg 6), upright:
// its AI object's (unk_D30), or a type_3DAC58's, type_3DDB98's or
// type_3DA6C0's.
void sub_65180(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;
    RwV3d var_10;
    RwV3d var_1C;
    RwV3d var_28;
    RwMatrix var_70;
    AIData *var_74;

    var_4 = sub_45170(arg_0);
    var_10.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_10.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_10.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    var_1C.x = SCRIPT_ARGT<RwReal>(arg_4, 4);
    var_1C.y = SCRIPT_ARGT<RwReal>(arg_4, 5);
    var_1C.z = SCRIPT_ARGT<RwReal>(arg_4, 6);
    var_28.x = 0.0f;
    var_28.y = 1.0f;
    var_28.z = 0.0f;
    SCRIPT_CHECK(var_4 != 0);
    RwV3dNormalize(&var_1C, &var_1C);
    RwMatrixSetIdentityMacro(&var_70);
    var_70.at = var_1C;
    RwV3dCrossProductMacro(&var_70.right, &var_28, &var_1C);
    RwV3dCrossProductMacro(&var_28, &var_70.right, &var_1C);
    var_70.pos = var_10;
    var_74 = var_4->vf_120();
    if (var_74)
    {
        RwMatrixTransform(&var_74->unk_D30, &var_70, rwCOMBINEREPLACE);
    }
    else if (var_4->vf_020())
    {
        RwMatrixTransform(var_4->vf_020()->get_unk_3D0(), &var_70, rwCOMBINEREPLACE);
    }
    else if (var_4->vf_024())
    {
        RwMatrixTransform(var_4->vf_024()->get_unk_6F0(), &var_70, rwCOMBINEREPLACE);
    }
    else if (var_4->vf_01C())
    {
        RwMatrixTransform(var_4->vf_01C()->get_unk_3F0(), &var_70, rwCOMBINEREPLACE);
    }
    sub_44350(arg_4, 0);
}

// match: sub_654C0 @ 0x000654C0
// sp-match: sub_654C0 @ 0x00054A00
// "SetSplineOffsetMatrix": the offset matrix arg 1 of the entity from its
// spline path; only a type_3DA6C0 takes it (with an AI object or as the
// vf_024 subclass it does nothing).
void sub_654C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *varC;
    RwMatrix *local_8;
    AIData *var_4;

    varC = sub_45170(arg_0);
    local_8 = (RwMatrix *)SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(varC != 0);
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    var_4 = varC->vf_120();
    if (var_4 != 0)
        ;
    else if (varC->vf_024() != 0)
        ;
    else if (varC->vf_01C() != 0)
        RwMatrixTransform(varC->vf_01C()->get_unk_3F0(), local_8, rwCOMBINEREPLACE);
    sub_44350(arg_4, 0);
}

// match: sub_65580 @ 0x00065580
// sp-match: sub_65580 @ 0x00054AC0
// "SetProceduralRollOnSpline": whether the entity (a type_3DA6C0) rolls
// procedurally on its spline (arg 1).
void sub_65580(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(var_4 != 0);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    if (var_4->vf_01C() != 0)
        var_4->vf_01C()->vf_240(local_8 != 0);
    sub_44350(arg_4, 0);
}

// match: sub_65620 @ 0x00065620
// sp-match: sub_65620 @ 0x00054B60
// "GetMatrixFromAIObj": the matrix of the entity of the object the handle
// arg 1 names.
void sub_65620(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D2E7C *var_10;
    RwInt32 ebp_C;
    type_3D3548 *v8;
    RwMatrix *var_4;

    ebp_C = SCRIPT_ARG(arg_4, 1);
    var_10 = (type_3D2E7C *)sub_67620(ebp_C);
    SCRIPT_CHECK(var_10 != 0);
    v8 = var_10->sub_71300();
    SCRIPT_CHECK(v8 != 0);
    var_4 = 0;
    SCRIPT_CHECK(v8 != 0);
    var_4 = RwFrameGetMatrix(v8->get_unk_340());
    sub_44350(arg_4, &var_4);
}

// match: sub_656D0 @ 0x000656D0
// sp-match: sub_656D0 @ 0x00054C90
// "GetMatrixFromName": the matrix of the entity the kind-0x2E object under
// the key arg 1 (two slots) holds.
void sub_656D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DFEEC *var_10;
    type_3DF8D8_04 *ebp_C;
    type_3DF8D8 *v8;
    RwMatrix *var_4;

    var_4 = 0;
    ebp_C = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(ebp_C != 0);
    v8 = sub_198800(ebp_C);
    SCRIPT_CHECK(v8 != 0);
    if (v8 != 0 && v8->vf_008() == 0x2E) {
        var_10 = (type_3DFEEC *)v8;
        SCRIPT_CHECK(var_10->unk_10 != 0);
        SCRIPT_CHECK(((type_D48D0 *)&var_10->unk_24_id)->sub_D4910() != 0);
        var_4 = RwFrameGetMatrix(((type_D48D0 *)&var_10->unk_24_id)->sub_D4910()->get_unk_340());
    } else
        SCRIPT_CHECK(0);
    sub_44220(var_4 != 0);
    sub_44350(arg_4, &var_4);
}

// match: sub_657D0 @ 0x000657D0
// sp-match: sub_657D0 @ 0x00054E40
// "GetGlobalRegister_AsInt": global script register arg 1 as an int.
void sub_657D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    var_4 = 0;
    sub_71DB0(local_8, 1, &var_4);
    sub_44350(arg_4, &var_4);
}

// match: sub_65850 @ 0x00065850
// sp-match: sub_65850 @ 0x00054F30
// "GetGlobalRegister_AsFloat": global script register arg 1 as a float.
void sub_65850(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwReal var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    var_4 = 0;
    sub_71DB0(local_8, 2, &var_4);
    sub_44350(arg_4, &var_4);
}

// match: sub_658D0 @ 0x000658D0
// sp-match: sub_658D0 @ 0x00055020
// "GetGlobalRegister_AsOther": global script register arg 1 as an untyped value.
void sub_658D0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    var_4 = 0;
    sub_71DB0(local_8, 0, &var_4);
    sub_44350(arg_4, &var_4);
}

// match: sub_65950 @ 0x00065950
// sp-match: sub_65950 @ 0x00055110
// "GetGlobalRegister_AsGodName": global script register arg 1 as a god name
// (an 8-byte key).
void sub_65950(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_C;

    local_C = SCRIPT_ARG(arg_4, 1);
    SCRIPT_CHECK(local_C >= 0);
    SCRIPT_CHECK(local_C < 101);
    type_3DF8D8_04 var_8;
    var_8.unk_00 = 0;
    var_8.unk_04 = 0;
    sub_71DB0(local_C, 3, &var_8);
    sub_44350(arg_4, &var_8);
}

// match: sub_659F0 @ 0x000659F0
// sp-match: sub_659F0 @ 0x00055200
// "SetGlobalRegister_AsInt": global script register arg 1 to arg 2, as an int.
void sub_659F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    sub_71E40(local_8, 1, &var_4);
    sub_44350(arg_4, 0);
}

// match: sub_65A90 @ 0x00065A90
// sp-match: sub_65A90 @ 0x000552D0
// "SetGlobalRegister_AsFloat": global script register arg 1 to arg 2, as a float.
void sub_65A90(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwReal var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARGT<RwReal>(arg_4, 2);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    sub_71E40(local_8, 2, &var_4);
    sub_44350(arg_4, 0);
}

// match: sub_65B30 @ 0x00065B30
// sp-match: sub_65B30 @ 0x000553A0
// "SetGlobalRegister_AsOther": global script register arg 1 to arg 2, as an untyped value.
void sub_65B30(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    RwInt32 var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(local_8 >= 0);
    SCRIPT_CHECK(local_8 < 101);
    sub_71E40(local_8, 0, &var_4);
    sub_44350(arg_4, 0);
}

// match: sub_65BD0 @ 0x00065BD0
// sp-match: sub_65BD0 @ 0x00055470
// "SetGlobalRegister_AsGodName": global script register arg 1 to the god
// name (an 8-byte key) arg 2 (two slots).
void sub_65BD0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3DF8D8_04 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = (type_3DF8D8_04 *)&SCRIPT_ARG(arg_4, 2);
    SCRIPT_CHECK(var_4 >= 0);
    SCRIPT_CHECK(var_4 < 101);
    sub_71E40(var_4, 3, local_8);
    sub_44350(arg_4, 0);
}

// match: sub_65C70 @ 0x00065C70
// sp-match: sub_65C70 @ 0x00055530
// "RemoveInterrupt": removes the interrupt arg 1 from the script's own
// task.
void sub_65C70(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_67620 *varC;
    type_46120 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    varC = sub_67620(arg_0);
    local_8 = varC->vf_034();
    SCRIPT_CHECK(local_8 != 0);
    ((type_3D2E20 *)local_8)->sub_70170(var_4);
    sub_44350(arg_4, 0);
}

// match: sub_65CF0 @ 0x00065CF0
// sp-match: sub_65CF0 @ 0x000555C0
// "SetCanAlliesDamage": sets (arg 2) whether allies may damage the entity
// of the object the handle arg 1 names (a flag of its trigger, by its kind).
void sub_65CF0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        stk_14->unk_128 = var_4;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var18->unk_124 = var_4;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_1C->unk_FC = var_4;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        local_20->unk_E8 = var_4;
    } else
        sub_44220(0);
    sub_44350(arg_4, 0);
}

// match: sub_65EB0 @ 0x00065EB0
// sp-match: sub_65EB0 @ 0x00055760
// "SetCanEnemiesDamage": sets (arg 2) whether enemies may damage the entity
// of the object the handle arg 1 names (a flag of its trigger, by its kind).
void sub_65EB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        stk_14->unk_12C = var_4;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var18->unk_128 = var_4;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_1C->unk_100 = var_4;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        local_20->unk_EC = var_4;
    } else
        sub_44220(0);
    sub_44350(arg_4, 0);
}

// match: sub_66070 @ 0x00066070
// sp-match: sub_66070 @ 0x00055900
// "SetCanBulletsDamage": sets (arg 2) whether bullets may damage the entity
// of the object the handle arg 1 names (a flag of its trigger, by its kind).
void sub_66070(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        stk_14->unk_130 = var_4;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var18->unk_12C = var_4;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_1C->unk_104 = var_4;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        local_20->unk_F0 = var_4;
    } else
        sub_44220(0);
    sub_44350(arg_4, 0);
}

// match: sub_66230 @ 0x00066230
// sp-match: sub_66230 @ 0x00055AA0
// "SetCanExplosionsDamage": sets (arg 2) whether explosions may damage the entity
// of the object the handle arg 1 names (a flag of its trigger, by its kind).
void sub_66230(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = SCRIPT_ARG(arg_4, 2);
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        stk_14->unk_134 = var_4;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var18->unk_130 = var_4;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_1C->unk_108 = var_4;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        local_20->unk_F4 = var_4;
    } else
        sub_44220(0);
    sub_44350(arg_4, 0);
}

// match: sub_663F0 @ 0x000663F0
// sp-match: sub_663F0 @ 0x00055C40
// "GetCanBulletsDamage": gets whether bullets may damage the entity of the
// object the handle arg 1 names (a flag of its trigger, by its kind). The
// command table gives "GetCanAlliesDamage" and "GetCanEnemiesDamage" this
// function too.
void sub_663F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = 0;
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        var_4 = stk_14->unk_130;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var_4 = var18->unk_12C;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_4 = var_1C->unk_104;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        var_4 = local_20->unk_F0;
    } else
        sub_44220(0);
    sub_44350(arg_4, &var_4);
}

// match: sub_66590 @ 0x00066590
// sp-match: sub_66590 @ 0x00055E10
// "GetCanExplosionsDamage": gets whether explosions may damage the entity of
// the object the handle arg 1 names (a flag of its trigger, by its kind).
void sub_66590(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_712B0_034 *local_20;
    type_712B0_3DAC58 *var_1C;
    type_712B0_3DDB98 *var18;
    type_712B0_3DA6C0 *stk_14;
    type_3D2E7C *l10;
    RwInt32 local_C;
    type_3D3548 *lv_8;
    RwInt32 var_4;

    local_C = SCRIPT_ARG(arg_4, 1);
    l10 = (type_3D2E7C *)sub_67620(local_C);
    SCRIPT_CHECK(l10 != 0);
    lv_8 = l10->sub_71300();
    SCRIPT_CHECK(lv_8 != 0);
    var_4 = 0;
    if (lv_8->vf_01C() != 0) {
        stk_14 = (type_712B0_3DA6C0 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(stk_14 != 0);
        var_4 = stk_14->unk_134;
    } else if (lv_8->vf_024() != 0) {
        var18 = (type_712B0_3DDB98 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var18 != 0);
        var_4 = var18->unk_130;
    } else if (lv_8->vf_020() != 0) {
        var_1C = (type_712B0_3DAC58 *)lv_8->get_unk_34C();
        SCRIPT_CHECK(var_1C != 0);
        var_4 = var_1C->unk_108;
    } else if (lv_8->vf_034() != 0) {
        local_20 = (type_712B0_034 *)lv_8->get_unk_34C();
        sub_44220(local_20 != 0);
        var_4 = local_20->unk_F4;
    } else
        sub_44220(0);
    sub_44350(arg_4, &var_4);
}

// match: sub_66730 @ 0x00066730
// sp-match: sub_66730 @ 0x00055FE0
// "GetNumberOfRestarts": dword_4B8720.
void sub_66730(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_44350(arg_4, &dword_4B8720);
}

// match: sub_66750 @ 0x00066750
// sp-match: sub_66750 @ 0x00056020
// "GetNumberOfActiveObjects": the number of entities in list arg 1 of
// dword_4B8600; lists 9 and 10 skip those with flag 9 of unk_28.
void sub_66750(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 varC;
    type_3D3548 *local_8;
    RwInt32 var_4;

    varC = SCRIPT_ARG(arg_4, 1);
    var_4 = 0;
    local_8 = dword_4B8600[varC].unk_00;
    while (local_8 != 0) {
        if (varC == 9 || varC == 10) {
            SCRIPT_CHECK(local_8->vf_008() != 0);
            if (((local_8->unk_28 >> 9) & 1) == 0)
                var_4++;
        } else
            var_4++;
        local_8 = local_8->unk_10;
    }
    sub_44350(arg_4, &var_4);
}

// match: sub_66810 @ 0x00066810
// sp-match: sub_66810 @ 0x000560F0
// "ShouldIContinueLeadingToPoint": whether the entity should go on leading
// player 0 to the point (arg 1, arg 2, arg 3): when, flattened, the
// directions from the player and from the entity to the point disagree, or
// the player is nearer the point.
void sub_66810(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwV3d l38;
    RwV3d lcl_2C;
    RwReal *local_20;
    RwV3d var_1C;
    RwInt32 l10;
    type_3D3548 *local_C;
    RwReal *lv_8;
    RwReal var_4;

    l10 = 0;
    local_C = sub_45170(arg_0);
    var_1C.x = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_1C.y = SCRIPT_ARGT<RwReal>(arg_4, 2);
    var_1C.z = SCRIPT_ARGT<RwReal>(arg_4, 3);
    SCRIPT_CHECK(local_C != 0);
    lv_8 = sub_1745A0(0)->vf_0C4();
    local_20 = local_C->vf_0C4();
    SCRIPT_CHECK(lv_8 != 0);
    SCRIPT_CHECK(local_20 != 0);
    RwV3dSubMacro(&lcl_2C, &var_1C, (RwV3d *)lv_8);
    RwV3dSubMacro(&l38, &var_1C, (RwV3d *)local_20);
    lcl_2C.y = l38.y = 0.0f;
    var_4 = RwV3dDotProductMacro(&lcl_2C, &l38);
    if (var_4 < 0.0f)
        l10 = 1;
    else if (RwV3dDotProductMacro(&lcl_2C, &lcl_2C) < RwV3dDotProductMacro(&l38, &l38))
        l10 = 1;
    {
        // A local the image reserves and never uses.
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &l10);
}

// match: sub_669F0 @ 0x000669F0
// sp-match: sub_669F0 @ 0x000562C0
// "GetCollisionWidth": the radius (unk_4C) of the entity of the object the
// handle arg 1 names, or 0.
void sub_669F0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_10;
    RwInt32 ebp_C;
    RwReal v8;
    type_3D2E7C *var_4;

    var_4 = 0;
    ebp_C = SCRIPT_ARG(arg_4, 1);
    if (ebp_C != 0)
        var_4 = (type_3D2E7C *)sub_67620(ebp_C);
    v8 = 0.0f;
    if (var_4 != 0) {
        var_10 = var_4->sub_71300();
        if (var_10 != 0)
            v8 = var_10->unk_4C;
    }
    sub_44350(arg_4, &v8);
}

// match: sub_66A80 @ 0x00066A80
// sp-match: sub_66A80 @ 0x00056350
// "SetPlayerConfined": whether player 0 is confined (unk_1A1C), arg 1.
void sub_66A80(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0)
        var_4->unk_1A1C = local_8;
    sub_44350(arg_4, 0);
}

// match: sub_66AE0 @ 0x00066AE0
// sp-match: sub_66AE0 @ 0x000563A0
// "SetPlayerHealthPercentage": player 0's health, the percentage arg 1
// (vf_23C).
void sub_66AE0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwReal local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARGT<RwReal>(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(0);
    if (var_4 != 0)
        var_4->vf_23C(local_8);
    sub_44350(arg_4, 0);
}

// match: sub_66B50 @ 0x00066B50
// sp-match: sub_66B50 @ 0x000563F0
// "DisablePlayerDamage": whether player 0's damage is off (unk_19FC), arg 1.
void sub_66B50(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_10F710 *local_8;
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    local_8 = (type_10F710 *)sub_1745A0(0);
    if (local_8 != 0)
        local_8->unk_19FC = var_4;
    sub_44350(arg_4, 0);
}

// match: sub_66BB0 @ 0x00066BB0
// sp-match: sub_66BB0 @ 0x00056440
// "IsOnlyLiveOnce": whether the entities of the entity's trigger live only
// once (vf_014), or 0 outside one.
void sub_66BB0(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    RwInt32 var_4;

    local_8 = sub_45170(arg_0);
    var_4 = 0;
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    if (local_8->get_unk_34C() != 0)
        var_4 = local_8->get_unk_34C()->vf_014();
    sub_44350(arg_4, &var_4);
}

// match: sub_66C20 @ 0x00066C20
// sp-match: sub_66C20 @ 0x000564B0
// "CausePlayerPainOnHUD": shows pain on the HUD from the entity.
void sub_66C20(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *var_4;

    var_4 = sub_45170(arg_0);
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_10;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    dword_4B9190->sub_DFB40(var_4, 0);
    sub_44350(arg_4, 0);
}

// match: sub_66C60 @ 0x00066C60
// "SetBombSiteInProximity": whether the entity's player is near the bomb
// site of performance map arg 1 (-1 or out of range for none; arg 2).
void sub_66C60(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "SetBombSiteInProximity" the empty command (SP 0x320AC8 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    RwInt32 l14;
    type_3D3548 *var_10;
    type_10F710 *ebp_C;
    type_4CFE30 *v8;
    RwInt32 var_4;

    l14 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    v8 = 0;
    if (l14 != -1) {
        if (l14 >= 0 && l14 < 2000)
            v8 = dword_4CFE30[l14];
        else
            v8 = 0;
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_10;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    var_10 = sub_45170(arg_0);
    ebp_C = var_10->vf_00C();
    ((type_17DBD0_player *)ebp_C)->sub_1BA910((type_712B0 *)v8, var_4 != 0);
    sub_44350(arg_4, 0);
#endif
}

// match: sub_66D30 @ 0x00066D30
// "CreateBomb": moves the child entity of the script's trigger to (arg 1,
// arg 2, arg 3).
void sub_66D30(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "CreateBomb" the empty command (SP 0x320AD0 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    RwReal bp_2C;
    RwV3d local_28;
    RwReal var_1C;
    RwReal var18;
    RwUInt32 stk_14;
    type_712B0 *l10;
    type_67620 *local_C;
    type_3D2E7C *lv_8;
    type_3D3548 *var_4;

    stk_14 = 0;
    local_C = sub_67620(arg_0);
    lv_8 = local_C->vf_024();
    l10 = lv_8->sub_712B0();
    var_4 = l10->vf_020();
    if (var_4 != 0) {
        type_3D2E7C *var_30 = var_4->vf_098();
        if (var_30 != 0)
            stk_14 = var_30->get_unk_04();
        var_1C = SCRIPT_ARGT<RwReal>(arg_4, 1);
        var18 = SCRIPT_ARGT<RwReal>(arg_4, 2);
        bp_2C = SCRIPT_ARGT<RwReal>(arg_4, 3);
        local_28.x = var_1C;
        local_28.y = var18;
        local_28.z = bp_2C;
        var_4->vf_0C0(&local_28);
    }
    sub_44350(arg_4, 0);
#endif
}

// match: sub_66E60 @ 0x00066E60
// "DeclareBombSite": declares bomb site arg 1 at the script's trigger.
void sub_66E60(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "DeclareBombSite" the empty command (SP 0x320AD8 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    type_712B0 *var_10;
    type_67620 *ebp_C;
    type_3D2E7C *v8;
    RwInt32 var_4;

    ebp_C = sub_67620(arg_0);
    v8 = ebp_C->vf_024();
    var_10 = v8->sub_712B0();
    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_4F6950.sub_1A48B0(var_4, var_10);
    sub_44350(arg_4, 0);
#endif
}

// match: sub_66EE0 @ 0x00066EE0
// "DeclareBombPlanted": declares the bomb planted by the script's object
// (arg 1, arg 2).
void sub_66EE0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "DeclareBombPlanted" the empty command (SP 0x320B00 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    type_67620 *var_10;
    type_3D2E7C *ebp_C;
    RwInt32 v8;
    RwInt32 var_4;

    var_10 = sub_67620(arg_0);
    ebp_C = var_10->vf_024();
    var_4 = SCRIPT_ARG(arg_4, 1);
    v8 = SCRIPT_ARG(arg_4, 2);
    dword_4F6950.sub_1A47B0(ebp_C, var_4, v8);
    sub_44350(arg_4, 0);
#endif
}

// match: sub_66F80 @ 0x00066F80
// "RequestSaveGame", "DeclareCaptureFlagBase" and "CreateFlag": nothing
// (the command table gives all three this function).
void sub_66F80(RwUInt32 arg_0, type_44350 *arg_4)
{
    sub_44350(arg_4, 0);
}

// match: sub_66FA0 @ 0x00066FA0
// "SetCaptureFlagBaseInProximity": whether the entity's player is near the
// capture-flag base of performance map arg 1 (-1 or out of range for none;
// arg 2).
void sub_66FA0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "SetCaptureFlagBaseInProximity" the empty command (SP 0x320AF0 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    RwInt32 l14;
    type_3D3548 *var_10;
    type_10F710 *ebp_C;
    type_4CFE30 *v8;
    RwInt32 var_4;

    l14 = SCRIPT_ARG(arg_4, 1);
    var_4 = SCRIPT_ARG(arg_4, 2);
    v8 = 0;
    if (l14 != -1) {
        if (l14 >= 0 && l14 < 2000)
            v8 = dword_4CFE30[l14];
        else
            v8 = 0;
    }
    {
        // Eleven locals the image reserves and never uses.
        RwInt32 unused_10;
        RwInt32 unused_9;
        RwInt32 unused_8;
        RwInt32 unused_7;
        RwInt32 unused_6;
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    var_10 = sub_45170(arg_0);
    ebp_C = var_10->vf_00C();
    ((type_17DBD0_player *)ebp_C)->sub_1BA980((Trigger *)v8, var_4 != 0);
    sub_44350(arg_4, 0);
#endif
}

// match: sub_67070 @ 0x00067070
// "FlagRenderTimeOut": times out the rendering of the script's flag entity.
void sub_67070(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "FlagRenderTimeOut" the empty command (SP 0x320AF8 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    type_67620 *varC;
    type_3D2E7C *local_8;
    type_3D3548 *var_4;

    varC = sub_67620(arg_0);
    local_8 = varC->vf_024();
    var_4 = local_8->sub_71300();
    dword_4F6A7C.sub_1A5970(var_4);
    sub_44350(arg_4, 0);
#endif
}

// match: sub_670C0 @ 0x000670C0
// sp-match: sub_670C0 @ 0x00056510
// "GetGameType": the game type (dword_4FB9E0's unk_08).
void sub_670C0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

#ifdef CODFH_SP // single player has no game type: always 0 (SP 0x56510)
    var_4 = 0;
#else
    var_4 = dword_4FB9E0.get_unk_08();
#endif
    sub_44350(arg_4, &var_4);
}

// match: sub_670F0 @ 0x000670F0
// "SDObjectivesComplete": completes the search-and-destroy objectives.
void sub_670F0(RwUInt32 arg_0, type_44350 *arg_4)
{
#ifdef CODFH_SP // single player's command table gives "SDObjectivesComplete" the empty command (SP 0x320B10 points at 0x564F0, the folded empty command): multiplayer's game modes only
    sub_44350(arg_4, 0);
#else
    dword_4FB9E0.sub_1B6530();
    sub_44350(arg_4, 0);
#endif
}

// match: sub_67110 @ 0x00067110
// sp-match: sub_67110 @ 0x00056560
// "EnableFrustumCheck": the frustum check on or off (arg 1).
void sub_67110(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = SCRIPT_ARG(arg_4, 1);
    dword_4B69F0 = 1 - var_4;
    sub_44350(arg_4, 0);
}

// match: sub_67160 @ 0x00067160
// sp-match: sub_67160 @ 0x000565A0
// "SetLadderMovement": the ladder movement arg 1 of the player
// (dword_429EB0), when on a ladder.
void sub_67160(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 local_8;
    type_10F710 *var_4;

    local_8 = SCRIPT_ARG(arg_4, 1);
    var_4 = (type_10F710 *)sub_1745A0(dword_429EB0);
    if (var_4 != 0 && var_4->unk_2178 != 0)
        var_4->unk_2178->set_unk_D8(local_8);
    sub_44350(arg_4, 0);
}

// match: sub_671E0 @ 0x000671E0
// sp-match: sub_671E0 @ 0x00056600
// "GetGameDifficulty": dword_42B714.
void sub_671E0(RwUInt32 arg_0, type_44350 *arg_4)
{
    RwInt32 var_4;

    var_4 = dword_42B714;
    sub_44350(arg_4, &var_4);
}

// match: sub_67200 @ 0x00067200
// sp-match: sub_67200 @ 0x00056650
// "GetWeaponType": the weapon type of the entity (a soldier, vf_008).
void sub_67200(RwUInt32 arg_0, type_44350 *arg_4)
{
    type_3D3548 *local_8;
    type_3DAFC8 *var_4;

    var_4 = 0;
    local_8 = sub_45170(arg_0);
    var_4 = local_8->vf_008();
    SCRIPT_CHECK(var_4 != 0);
    {
        // Six locals the image reserves and never uses.
        RwInt32 unused_5;
        RwInt32 unused_4;
        RwInt32 unused_3;
        RwInt32 unused_2;
        RwInt32 unused_1;
        RwInt32 unused_0;
    }
    sub_44350(arg_4, &var_4->unk_3E0.unk_04);
}

#ifdef CODFH_WIN32
extern "C" void port_debug_print(const RwChar *arg_0, ...);
extern "C" RwInt32 port_log_verbose;   // (port/src/xpal_core.cpp: -verbose)
#endif

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

// ??0type_439A48@@QAE@XZ (folded into 0x67260)
type_439A48::type_439A48()
{
    unk_00 = 0;
    unk_04 = 0;
    memset(unk_08, 0, sizeof(unk_08));
    unk_00 = 1;
    unk_04 = 0;
    unk_38 = 0;
    unk_3C = 0;
    unk_40 = 0;
    unk_44 = 0;
    unk_48 = 0;
    unk_4C = 0;
}

// Functions /OPT:ICF folded into another body (config/aliases.txt), defined here for the
// authentic link (PLAN M7) with that body; the placement link takes the folded one.

#if !defined(CODFH_SP) || defined(CODFH_SP_LOGS) // single player calls these out of line (SP 0x4D840, 0x4EF60): only declared there
// ?sub_19A750@@YAXPAUtype_3D3548@@HUtype_3DF8D8_04@@H@Z (folded into 0x19A750)
void sub_19A750(struct type_3D3548 * arg_0, RwInt32 arg_4, struct type_3DF8D8_04 arg_8, RwInt32 arg_C)
{
#ifdef CODFH_WIN32
    // The sound log (an entity, a level, the sound's key, how it was asked for): the port prints
    // it with -verbose.
    if (port_log_verbose)
        port_debug_print("sound 0x%X 0x%X (entity %p, %d, %d)", ((const RwUInt32 *)&arg_8)[0],
                         ((const RwUInt32 *)&arg_8)[1], arg_0, arg_4, arg_C);
#endif
}

// ?sub_19A750@@YAXPAUtype_3DF8D8_04@@@Z (folded into 0x19A750)
void sub_19A750(struct type_3DF8D8_04 * arg_0)
{
#ifdef CODFH_WIN32
    // "PrintObjective": the port prints the objective's key.
    port_debug_print("objective 0x%X 0x%X", ((const RwUInt32 *)arg_0)[0], ((const RwUInt32 *)arg_0)[1]);
#endif
}
#endif

// ?sub_19A750@@YAXPAUtype_3DF8D8_04@@H@Z (folded into 0x19A750)
void sub_19A750(struct type_3DF8D8_04 * arg_0, RwInt32 arg_4)
{
#ifdef CODFH_WIN32
    // "SetObjectiveCounter", "ModifyObjectiveCounter": the port prints the key and the count.
    port_debug_print("objective 0x%X 0x%X counter %d", ((const RwUInt32 *)arg_0)[0],
                     ((const RwUInt32 *)arg_0)[1], arg_4);
#endif
}
