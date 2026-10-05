; codfh-match: XDK XGraphics code (repacked)
; An XDK stand-in repacked from the image (PLAN M3: library code the installed
; libraries do not hold in the image version, extracted byte for byte by
; tools/img2masm.py, never decompiled).

        .686p
        .model flat

EXTERN ??_GPixelShaderVerifier@XGRAPHICS@@QAEPAXI@Z:NEAR
EXTERN ?DecodeRegister@CD3DXAssembler@XGRAPHICS@@QAEKPADKH@Z:NEAR
EXTERN ??0Buffer@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??0CD3DXAssembler@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_0:NEAR
EXTERN ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_1:NEAR
EXTERN ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_2:NEAR
EXTERN ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_3:NEAR
EXTERN ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_4:NEAR
EXTERN ??1Buffer@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??1CD3DXAssembler@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??1InstructionGraph@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ:NEAR
EXTERN ??1PreProcessor@XGRAPHICS@@QAE@XZ:NEAR
EXTERN ??1Reader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ:NEAR
EXTERN ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ:NEAR
EXTERN ??_GBuffer@XGRAPHICS@@QAEPAXI@Z:NEAR
EXTERN ?Add@Map@PreProcessor@XGRAPHICS@@QAEJPBDK0K@Z:NEAR
EXTERN ?Append@Buffer@XGRAPHICS@@QAEJAAV12@@Z:NEAR
EXTERN ?Append@Buffer@XGRAPHICS@@QAEJD@Z:NEAR
EXTERN ?Append@Buffer@XGRAPHICS@@QAEJPBD@Z:NEAR
EXTERN ?Append@Buffer@XGRAPHICS@@QAEJPBXK@Z:NEAR
EXTERN ?Assemble@CD3DXAssembler@XGRAPHICS@@QAEJPBXIPBDIKPAPAUXGBuffer@@2PAUXD3DXErrorLog@2@PAK@Z:NEAR
EXTERN ?Clean@Entry@Map@PreProcessor@XGRAPHICS@@QAEXXZ:NEAR
EXTERN ?Cleanup@Map@PreProcessor@XGRAPHICS@@QAEXXZ:NEAR
EXTERN ?CompileShaderToUCode@Assembler@XGRAPHICS@@AAEJ_N0000KPAUXGBuffer@@PAPAU3@PAVBuffer@2@PAUXD3DXErrorLog@2@00@Z:NEAR
EXTERN ?DecodeSwizzle@CD3DXAssembler@XGRAPHICS@@QAEKPAD@Z:NEAR
EXTERN ?DoDefine@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoElif@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoElse@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoEndif@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoIf@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoIfdef@PreProcessor@XGRAPHICS@@AAEJPBD_N@Z:NEAR
EXTERN ?DoInclude@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?DoUndef@PreProcessor@XGRAPHICS@@AAEJPBD@Z:NEAR
EXTERN ?Error@PreProcessor@XGRAPHICS@@AAAX_NKPBDZZ:NEAR
EXTERN ?FindLine@PreProcessor@XGRAPHICS@@AAEJAAVBuffer@2@@Z:NEAR
EXTERN ?GetText@Buffer@XGRAPHICS@@QAEPADXZ:NEAR
EXTERN ?GetToken@PreProcessor@XGRAPHICS@@CGJAAVToken@12@AAPBD_N@Z:NEAR
EXTERN ?GetUsed@Buffer@XGRAPHICS@@QAEKXZ:NEAR
EXTERN ?GrowTo@Buffer@XGRAPHICS@@QAEJK@Z:NEAR
EXTERN ?Initialize@Buffer@XGRAPHICS@@QAEJK@Z:NEAR
EXTERN ?Initialize@MyErrorLog@XGRAPHICS@@QAEJPBD@Z:NEAR
EXTERN ?IsEqual@Token@PreProcessor@XGRAPHICS@@QAE_NKPBDK@Z:NEAR
EXTERN ?IsLegalMacroDeclaration@PreProcessor@XGRAPHICS@@AAEJPBD0PA_N@Z:NEAR
EXTERN ?ListD3DTokens@XGRAPHICS@@YGJPAVBuffer@1@PBKK@Z:NEAR
EXTERN ?Lookup@Map@PreProcessor@XGRAPHICS@@QAEPBDPBDK@Z:NEAR
EXTERN ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z:NEAR
EXTERN ?Printf@Buffer@XGRAPHICS@@QAAJPBDZZ:NEAR
EXTERN ?ProcessIncDec@PreProcessor@XGRAPHICS@@AAEJAAVBuffer@2@AAPBDAAVMap@12@H@Z:NEAR
EXTERN ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z:NEAR
EXTERN ?Push@XAsmCD3DXSzStack@XGRAPHICS@@QAEJPAD@Z:NEAR
EXTERN ?RecordInputMask@DeadCodeStripper@XGRAPHICS@@QAEJABU_D3DVsInstruction@@ABURegMask@12@PBD@Z:NEAR
EXTERN ?Remove@Map@PreProcessor@XGRAPHICS@@QAEXPBDK@Z:NEAR
EXTERN ?SkipWS@PreProcessor@XGRAPHICS@@CGJAAPBD@Z:NEAR
EXTERN ?StripDebugInfo@Assembler@XGRAPHICS@@AAEJPAUXGBuffer@@@Z:NEAR
EXTERN ?UpdateDebugFileLine@CD3DXAssembler@XGRAPHICS@@QAEXXZ:NEAR
EXTERN ?ValidateSrcRegister@CD3DXAssembler@XGRAPHICS@@QAEXK@Z:NEAR
EXTERN ?XGBufferCreateFromBuffer@XGRAPHICS@@YGJPAVBuffer@1@PAPAUXGBuffer@@@Z:NEAR
EXTERN ?XGPreprocess@XGRAPHICS@@YGJPBDP6GJPAXH00PADKPAPAUXGBuffer@@@Z1PAU2@3PAUXD3DXErrorLog@1@@Z:NEAR
EXTERN ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z:NEAR
EXTERN ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:NEAR
EXTERN ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ:NEAR
EXTERN ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:NEAR
EXTERN ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z:NEAR
EXTERN ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_0:NEAR
EXTERN ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_1:NEAR
EXTERN ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_2:NEAR
EXTERN ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_4:NEAR
EXTERN ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_0:NEAR
EXTERN ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_1:NEAR
EXTERN ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_2:NEAR
EXTERN ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_3:NEAR
EXTERN ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_4:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_0:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_2:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_3:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_4:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_0:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_1:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_2:NEAR
EXTERN ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_3:NEAR
EXTERN ?insert@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVInstruction@23@PAV4123@@Z:NEAR
EXTERN _XGBufferCreate@8:NEAR
EXTERN _XGBuffer_AddRef@4:NEAR
EXTERN _XGBuffer_GetBufferPointer@4:NEAR
EXTERN _XGBuffer_GetBufferSize@4:NEAR
EXTERN _XGBuffer_Release@4:NEAR
EXTERN _XMemAlloc@8:NEAR
EXTERN _XMemFree@8:NEAR
EXTERN __EH_prolog:NEAR
EXTERN _atexit:NEAR
EXTERN _atoi:NEAR
EXTERN _isalpha:NEAR
EXTERN _isdigit:NEAR
EXTERN _loc_300030:BYTE
EXTERN _lstrcmpiA@8:NEAR
EXTERN _sprintf:NEAR
EXTERN _sscanf:NEAR
EXTERN _strncmp:NEAR
EXTERN _sub_30902A:BYTE
EXTERN _sub_3094AE:BYTE
EXTERN _sub_309633:BYTE
EXTERN _sub_394608:NEAR
EXTERN _sub_394631:NEAR
EXTERN _sub_394702:NEAR
EXTERN _sub_395661:NEAR
EXTERN _sub_395ED8:NEAR
EXTERN _sub_396039:NEAR
EXTERN _sub_397990:NEAR
EXTERN _sub_397E05:NEAR
EXTERN _sub_398259:NEAR
EXTERN _sub_398D42:NEAR
EXTERN _sub_39B0CF:NEAR
EXTERN _sub_39B389:NEAR
EXTERN _sub_39D085:NEAR
EXTERN _sub_39D099:NEAR
EXTERN _sub_3A19AB:NEAR
EXTERN _sub_3A19C5:NEAR
EXTERN _sub_3A20AA:NEAR
EXTERN _sub_3A222F:NEAR
EXTERN _sub_3A3E0D:NEAR
EXTERN _sub_3A47CF:NEAR
EXTERN _sub_3A6426:NEAR
EXTERN _sub_3A7328:NEAR
EXTERN _unk_3A77E0:BYTE
EXTERN _unk_3A7800:BYTE
EXTERN _unk_3A7810:BYTE
EXTERN _unk_3A7928:BYTE
EXTERN _unk_3A7930:BYTE
EXTERN _unk_3A7934:BYTE
EXTERN _unk_3A793C:BYTE
EXTERN _unk_3A7940:BYTE
EXTERN _unk_3A7944:BYTE
EXTERN _unk_3A7948:BYTE
EXTERN _unk_3A7950:BYTE
EXTERN _unk_3A7954:BYTE
EXTERN _unk_3A7958:BYTE
EXTERN _unk_3A795C:BYTE
EXTERN _unk_3A7960:BYTE
EXTERN _unk_3A7964:BYTE
EXTERN _unk_3A7968:BYTE
EXTERN _unk_3A7D70:BYTE
EXTERN _unk_3A7D74:BYTE
EXTERN _unk_3A7D78:BYTE
EXTERN _unk_3A7D80:BYTE
EXTERN _unk_3A7D88:BYTE
EXTERN _unk_3A7D90:BYTE
EXTERN _unk_3A7D9C:BYTE
EXTERN _unk_3A7DAC:BYTE
EXTERN _unk_3A7DB8:BYTE
EXTERN _unk_3A7DBC:BYTE
EXTERN _unk_3A7DC0:BYTE
EXTERN _unk_3A7DC8:BYTE
EXTERN _unk_3A7DCC:BYTE
EXTERN _unk_3A7DE0:BYTE
EXTERN _unk_3A7DF8:BYTE
EXTERN _unk_3A7E0C:BYTE
EXTERN _unk_3A7E10:BYTE
EXTERN _unk_3A7E14:BYTE
EXTERN _unk_3A7E18:BYTE
EXTERN _unk_3A7E1C:BYTE
EXTERN _unk_3A7E20:BYTE
EXTERN _unk_3A7E24:BYTE
EXTERN _unk_3A7E28:BYTE
EXTERN _unk_3A7E2C:BYTE
EXTERN _unk_3A7E30:BYTE
EXTERN _unk_3A7E34:BYTE
EXTERN _unk_3A7E38:BYTE
EXTERN _unk_3A7E40:BYTE
EXTERN _unk_3A7E48:BYTE
EXTERN _unk_3A7E4C:BYTE
EXTERN _unk_3A7E50:BYTE
EXTERN _unk_3A7E54:BYTE
EXTERN _unk_3A7E58:BYTE
EXTERN _unk_3A7E5C:BYTE
EXTERN _unk_3A7E64:BYTE
EXTERN _unk_3A7E74:BYTE
EXTERN _unk_3A80F0:BYTE
EXTERN _unk_3A8970:BYTE
EXTERN _unk_3A8998:BYTE
EXTERN _unk_3A89B4:BYTE
EXTERN _unk_3A89D0:BYTE
EXTERN _unk_3A89F8:BYTE
EXTERN _unk_3A8A20:BYTE
EXTERN _unk_3A8A54:BYTE
EXTERN _unk_3A8A5C:BYTE
EXTERN _unk_3A8A88:BYTE
EXTERN _unk_3A8A90:BYTE
EXTERN _unk_3A8AB8:BYTE
EXTERN _unk_3A8AEC:BYTE
EXTERN _unk_3A8B20:BYTE
EXTERN _unk_3A8B50:BYTE
EXTERN _unk_3A8B70:BYTE
EXTERN _unk_3A8B90:BYTE
EXTERN _unk_3A8BE8:BYTE
EXTERN _unk_3A8C10:BYTE
EXTERN _unk_3A8C28:BYTE
EXTERN _unk_3A8C54:BYTE
EXTERN _unk_3A8C80:BYTE
EXTERN _unk_3A8CA8:BYTE
EXTERN _unk_3A8CD4:BYTE
EXTERN _unk_3A8CE8:BYTE
EXTERN _unk_3A8D04:BYTE
EXTERN _unk_3A8D1C:BYTE
EXTERN _unk_3A8D40:BYTE
EXTERN _unk_3A8D48:BYTE
EXTERN _unk_3A8D6C:BYTE
EXTERN _unk_3A8DA0:BYTE
EXTERN _unk_3A8DAC:BYTE
EXTERN _unk_3A8DB8:BYTE
EXTERN _unk_3A8DE0:BYTE
EXTERN _unk_3A8DF4:BYTE
EXTERN _unk_3A8E00:BYTE
EXTERN _unk_3A8E28:BYTE
EXTERN _unk_3A8E48:BYTE
EXTERN _unk_3A9020:BYTE
EXTERN _unk_3A96FC:BYTE
EXTERN _unk_3A9700:BYTE
EXTERN _unk_3A9708:BYTE
EXTERN _unk_3A970C:BYTE
EXTERN _unk_3A9710:BYTE
EXTERN _unk_3A9718:BYTE
EXTERN _unk_3A9720:BYTE
EXTERN _unk_3A9728:BYTE
EXTERN _unk_3A9730:BYTE
EXTERN _unk_3A9738:BYTE
EXTERN _unk_3A973C:BYTE
EXTERN _unk_3A9744:BYTE
EXTERN _unk_3A9754:BYTE
EXTERN _unk_3A9758:BYTE
EXTERN _unk_3A975C:BYTE
EXTERN _unk_3A9760:BYTE
EXTERN _unk_3A9768:BYTE
EXTERN _unk_3A9770:BYTE
EXTERN _unk_3A9780:BYTE
EXTERN _unk_3A978C:BYTE
EXTERN _unk_3A9798:BYTE
EXTERN _unk_3A97A4:BYTE
EXTERN _unk_3A97B0:BYTE
EXTERN _unk_3A97BC:BYTE
EXTERN _unk_3A97C8:BYTE
EXTERN _unk_3A97D4:BYTE
EXTERN _unk_3A97E0:BYTE
EXTERN _unk_3A97F0:BYTE
EXTERN _unk_3A97F4:BYTE
EXTERN _unk_3A97FC:BYTE
EXTERN _unk_3A9808:BYTE
EXTERN _unk_3A980C:BYTE
EXTERN _unk_3A9810:BYTE
EXTERN _unk_3A9814:BYTE
EXTERN _unk_3A9844:BYTE
EXTERN _unk_3A9860:BYTE
EXTERN _unk_3A9884:BYTE
EXTERN _unk_3A989C:BYTE
EXTERN _unk_3A98A0:BYTE
EXTERN _unk_3A98A4:BYTE
EXTERN _unk_3A98A8:BYTE
EXTERN _unk_3A98AC:BYTE
EXTERN _unk_3A98B4:BYTE
EXTERN _unk_3A98B8:BYTE
EXTERN _unk_3A98C8:BYTE
EXTERN _unk_3A98CC:BYTE
EXTERN _unk_3A98D0:BYTE
EXTERN _unk_3A98D8:BYTE
EXTERN _unk_3A98E0:BYTE
EXTERN _unk_3A98E8:BYTE
EXTERN _unk_3A98F0:BYTE
EXTERN _unk_3A98F4:BYTE
EXTERN _unk_3A98FC:BYTE
EXTERN _unk_3A9904:BYTE
EXTERN _unk_3A990C:BYTE
EXTERN _unk_3A9914:BYTE
EXTERN _unk_3A991C:BYTE
EXTERN _unk_3A9924:BYTE
EXTERN _unk_3A9A90:BYTE
EXTERN _unk_3A9AB0:BYTE
EXTERN _unk_3A9AF8:BYTE
EXTERN _unk_3A9B10:BYTE
EXTERN _unk_3A9B44:BYTE
EXTERN _unk_3A9B6C:BYTE
EXTERN _unk_3A9B7C:BYTE
EXTERN _unk_3A9B84:BYTE
EXTERN _unk_3A9BB4:BYTE
EXTERN _unk_3A9BE0:BYTE
EXTERN _unk_3A9E48:BYTE
EXTERN _unk_3A9E4C:BYTE
EXTERN _unk_3A9E50:BYTE
EXTERN _unk_3A9ED0:BYTE
EXTERN _unk_3A9EE8:BYTE
EXTERN _unk_3AA07C:BYTE
EXTERN _unk_3AA0A0:BYTE
EXTERN _unk_3AA0A8:BYTE
EXTERN _unk_3AA0C8:BYTE
EXTERN _unk_3AA1C0:BYTE
EXTERN _unk_3AA1E0:BYTE
EXTERN _unk_3AA1E8:BYTE
EXTERN _unk_3AA1F0:BYTE
EXTERN _unk_3AA1F8:BYTE
EXTERN _unk_3AA200:BYTE
EXTERN _unk_3AA208:BYTE
EXTERN _unk_3AA20C:BYTE
EXTERN _unk_3AA214:BYTE
EXTERN _unk_3AA21C:BYTE
EXTERN _unk_3AA224:BYTE
EXTERN _unk_3AA298:BYTE
EXTERN _unk_3AA2A0:BYTE
EXTERN _unk_3AA2A4:BYTE
EXTERN _unk_3AA2A8:BYTE
EXTERN _unk_3AA2B0:BYTE
EXTERN _unk_3AA2B4:BYTE
EXTERN _unk_3AA2B8:BYTE
EXTERN _unk_3AA2C0:BYTE
EXTERN _unk_3AA2C4:BYTE
EXTERN _unk_3AA35C:BYTE
EXTERN _unk_3D292C:BYTE
EXTERN _unk_3D292F:BYTE
EXTERN _unk_3D2E78:BYTE
EXTERN _unk_3D4018:BYTE
EXTERN _unk_3D51A4:BYTE
EXTERN _unk_3D7E50:BYTE
EXTERN _unk_3D8C40:BYTE
EXTERN _unk_3DE7E8:BYTE
EXTERN ??_C@_05KKCIMGE@error?$AA@:BYTE
EXTERN _unk_3E3D9C:BYTE
EXTERN _unk_3EB834:BYTE
EXTERN _unk_3EE8A8:BYTE
EXTERN _unk_3EE8B0:BYTE
EXTERN _unk_417830:BYTE
EXTERN _unk_417838:BYTE
EXTERN _unk_41A9C0:BYTE
EXTERN ??_7CompMask@VS_GRAPH_OPTIMIZER@XGRAPHICS@@6B@:BYTE
EXTERN _unk_41A9D4:BYTE
EXTERN _unk_41A9DC:BYTE
EXTERN _unk_41A9E8:BYTE
EXTERN _unk_41A9F0:BYTE
EXTERN _unk_41A9F8:BYTE
EXTERN _unk_41AA00:BYTE
EXTERN _unk_41AA10:BYTE
EXTERN _unk_41AA18:BYTE
EXTERN _unk_41AA20:BYTE
EXTERN _unk_41AA24:BYTE
EXTERN _unk_41AA28:BYTE
EXTERN _unk_41AA2C:BYTE
EXTERN _unk_41AA30:BYTE
EXTERN _unk_41AA34:BYTE
EXTERN _unk_41AA38:BYTE
EXTERN _unk_41AA48:BYTE
EXTERN _unk_41AA68:BYTE
EXTERN _unk_437868:BYTE
EXTERN _unk_4378D0:BYTE
EXTERN _unk_437910:BYTE
EXTERN _unk_437934:BYTE
EXTERN _unk_437A58:BYTE
EXTERN _unk_437BAC:BYTE
EXTERN _unk_437BB4:BYTE
EXTERN _unk_437BBC:BYTE
EXTERN _unk_437BC8:BYTE
EXTERN _unk_437C48:BYTE
EXTERN _unk_437C68:BYTE
EXTERN _unk_437C70:BYTE
EXTERN _unk_437C78:BYTE
EXTERN _unk_437C80:BYTE
EXTERN _unk_437C88:BYTE
EXTERN _unk_437CA8:BYTE
EXTERN _unk_437CE8:BYTE
EXTERN _unk_437D28:BYTE
EXTERN _unk_437D30:BYTE
EXTERN _unk_437D38:BYTE
EXTERN _unk_437D58:BYTE
EXTERN _unk_437D60:BYTE
EXTERN _unk_437D68:BYTE
EXTERN _unk_539778:BYTE
EXTERN ??_C@_04GHFHNDFH@?4xyz?$AA@:BYTE

seg0 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?RegisterWriteMask@InstructionDisassembler@XGRAPHICS@@CGPBDK@Z @ 0x0038CE5C
PUBLIC ?RegisterWriteMask@InstructionDisassembler@XGRAPHICS@@CGPBDK@Z
?RegisterWriteMask@InstructionDisassembler@XGRAPHICS@@CGPBDK@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 044h   ; sub esp, 0x44
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 083h, 0F8h, 00Fh   ; cmp eax, 0xf
        db 0C7h, 045h, 0BCh   ; mov dword ptr [ebp - 0x44], 0x3a7968
        dd _unk_3A7968
        db 0C7h, 045h, 0C0h   ; mov dword ptr [ebp - 0x40], 0x3a7964
        dd _unk_3A7964
        db 0C7h, 045h, 0C4h   ; mov dword ptr [ebp - 0x3c], 0x3a7960
        dd _unk_3A7960
        db 0C7h, 045h, 0C8h   ; mov dword ptr [ebp - 0x38], 0x3a795c
        dd _unk_3A795C
        db 0C7h, 045h, 0CCh   ; mov dword ptr [ebp - 0x34], 0x3a7958
        dd _unk_3A7958
        db 0C7h, 045h, 0D0h   ; mov dword ptr [ebp - 0x30], 0x3a7954
        dd _unk_3A7954
        db 0C7h, 045h, 0D4h   ; mov dword ptr [ebp - 0x2c], 0x3a7950
        dd _unk_3A7950
        db 0C7h, 045h, 0D8h   ; mov dword ptr [ebp - 0x28], 0x3a7948
        dd _unk_3A7948
        db 0C7h, 045h, 0DCh   ; mov dword ptr [ebp - 0x24], 0x3a7944
        dd _unk_3A7944
        db 0C7h, 045h, 0E0h   ; mov dword ptr [ebp - 0x20], 0x3a7940
        dd _unk_3A7940
        db 0C7h, 045h, 0E4h   ; mov dword ptr [ebp - 0x1c], 0x3a793c
        dd _unk_3A793C
        db 0C7h, 045h, 0E8h   ; mov dword ptr [ebp - 0x18], 0x3a7934
        dd _unk_3A7934
        db 0C7h, 045h, 0ECh   ; mov dword ptr [ebp - 0x14], 0x3a7930
        dd _unk_3A7930
        db 0C7h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], 0x3a7928
        dd _unk_3A7928
        db 0C7h, 045h, 0F4h   ; mov dword ptr [ebp - 0xc], 0x3a7920
        dd ??_C@_04GHFHNDFH@?4xyz?$AA@
        db 0C7h, 045h, 0F8h   ; mov dword ptr [ebp - 8], 0x3d292f
        dd _unk_3D292F
        db 0C7h, 045h, 0FCh   ; mov dword ptr [ebp - 4], 0x3e0138
        dd ??_C@_05KKCIMGE@error?$AA@
        db 076h, 003h   ; jbe 0x38cee4
        db 06Ah, 010h   ; push 0x10
        db 058h   ; pop eax
$L_38cee4:
        db 08Bh, 044h, 085h, 0BCh   ; mov eax, dword ptr [ebp + eax*4 - 0x44]
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
seg0 ENDS






seg7 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_3932E8 @ 0x003932E8
PUBLIC _sub_3932E8
_sub_3932E8:
$L_3932e8:
        db 0B8h   ; mov eax, 0x30902a
        dd _sub_30902A
        call __EH_prolog   ; 0x2C9200
        db 081h, 0ECh, 00Ch, 004h, 000h, 000h   ; sub esp, 0x40c
        db 08Bh, 045h, 00Ch   ; mov eax, dword ptr [ebp + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 008h   ; jne 0x393307
        db 0A1h   ; mov eax, dword ptr [0x437934]
        dd _unk_437934
        db 089h, 045h, 00Ch   ; mov dword ptr [ebp + 0xc], eax
$L_393307:
        db 08Bh, 04Dh, 018h   ; mov ecx, dword ptr [ebp + 0x18]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
        db 089h, 047h, 004h   ; mov dword ptr [edi + 4], eax
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 089h, 047h, 008h   ; mov dword ptr [edi + 8], eax
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 08Ah, 0C1h   ; mov al, cl
        db 024h, 001h   ; and al, 1
        db 088h, 045h, 0E3h   ; mov byte ptr [ebp - 0x1d], al
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E8h, 002h   ; shr eax, 2
        db 0F6h, 0D0h   ; not al
        db 024h, 001h   ; and al, 1
        db 088h, 045h, 0BCh   ; mov byte ptr [ebp - 0x44], al
        db 074h, 00Ch   ; je 0x393340
        db 0F7h, 0C1h, 000h, 000h, 001h, 000h   ; test ecx, 0x10000
        db 0C6h, 045h, 0C4h, 001h   ; mov byte ptr [ebp - 0x3c], 1
        db 075h, 004h   ; jne 0x393344
$L_393340:
        db 0C6h, 045h, 0C4h, 000h   ; mov byte ptr [ebp - 0x3c], 0
$L_393344:
        db 084h, 0C0h   ; test al, al
        db 074h, 00Ch   ; je 0x393354
        db 0F7h, 0C1h, 000h, 000h, 002h, 000h   ; test ecx, 0x20000
        db 0C6h, 045h, 0C8h, 001h   ; mov byte ptr [ebp - 0x38], 1
        db 075h, 004h   ; jne 0x393358
$L_393354:
        db 0C6h, 045h, 0C8h, 000h   ; mov byte ptr [ebp - 0x38], 0
$L_393358:
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0C1h, 0EAh, 00Fh   ; shr edx, 0xf
        db 080h, 0E2h, 001h   ; and dl, 1
        db 084h, 0C0h   ; test al, al
        db 088h, 055h, 0B8h   ; mov byte ptr [ebp - 0x48], dl
        db 074h, 009h   ; je 0x393370
        db 0F6h, 0C5h, 040h   ; test ch, 0x40
        db 0C6h, 045h, 0C0h, 001h   ; mov byte ptr [ebp - 0x40], 1
        db 074h, 004h   ; je 0x393374
$L_393370:
        db 0C6h, 045h, 0C0h, 000h   ; mov byte ptr [ebp - 0x40], 0
$L_393374:
        db 083h, 07Dh, 028h, 000h   ; cmp dword ptr [ebp + 0x28], 0
        db 08Bh, 0C1h   ; mov eax, ecx
        db 00Fh, 095h, 045h, 0DBh   ; setne byte ptr [ebp - 0x25]
        db 0F6h, 0C1h, 0F0h   ; test cl, 0xf0
        db 00Fh, 095h, 045h, 01Bh   ; setne byte ptr [ebp + 0x1b]
        db 0F6h, 0C5h, 00Ch   ; test ch, 0xc
        db 00Fh, 095h, 0C2h   ; setne dl
        db 083h, 065h, 0ECh, 000h   ; and dword ptr [ebp - 0x14], 0
        db 0C1h, 0E8h, 003h   ; shr eax, 3
        db 024h, 001h   ; and al, 1
        db 088h, 045h, 0F3h   ; mov byte ptr [ebp - 0xd], al
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 0C1h, 0E8h, 00Ch   ; shr eax, 0xc
        db 0C1h, 0EBh, 00Dh   ; shr ebx, 0xd
        db 024h, 001h   ; and al, 1
        db 080h, 0E3h, 001h   ; and bl, 1
        db 080h, 07Dh, 01Bh, 000h   ; cmp byte ptr [ebp + 0x1b], 0
        db 088h, 017h   ; mov byte ptr [edi], dl
        db 088h, 045h, 0EBh   ; mov byte ptr [ebp - 0x15], al
        db 0BEh, 000h, 001h, 000h, 000h   ; mov esi, 0x100
        db 074h, 039h   ; je 0x3933ef
        db 0F6h, 0C1h, 010h   ; test cl, 0x10
        db 074h, 006h   ; je 0x3933c1
        db 083h, 065h, 0ECh, 000h   ; and dword ptr [ebp - 0x14], 0
        db 0EBh, 027h   ; jmp 0x3933e8
$L_3933c1:
        db 0F6h, 0C1h, 020h   ; test cl, 0x20
        db 074h, 009h   ; je 0x3933cf
        db 0C7h, 045h, 0ECh, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x14], 1
        db 0EBh, 019h   ; jmp 0x3933e8
$L_3933cf:
        db 0F6h, 0C1h, 040h   ; test cl, 0x40
        db 074h, 009h   ; je 0x3933dd
        db 0C7h, 045h, 0ECh, 002h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x14], 2
        db 0EBh, 00Bh   ; jmp 0x3933e8
$L_3933dd:
        db 084h, 0C9h   ; test cl, cl
        db 079h, 007h   ; jns 0x3933e8
        db 0C7h, 045h, 0ECh, 003h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x14], 3
$L_3933e8:
        db 085h, 0CEh   ; test esi, ecx
        db 074h, 003h   ; je 0x3933ef
        db 009h, 075h, 0ECh   ; or dword ptr [ebp - 0x14], esi
$L_3933ef:
        db 083h, 065h, 0E4h, 000h   ; and dword ptr [ebp - 0x1c], 0
        db 084h, 0D2h   ; test dl, dl
        db 0C6h, 047h, 001h, 000h   ; mov byte ptr [edi + 1], 0
        db 074h, 062h   ; je 0x39345d
        db 083h, 07Dh, 014h, 002h   ; cmp dword ptr [ebp + 0x14], 2
        db 0C7h, 045h, 0ECh, 001h, 000h, 000h, 000h   ; mov dword ptr [ebp - 0x14], 1
        db 00Fh, 086h, 0CBh, 000h, 000h, 000h   ; jbe 0x3934d7
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 066h, 081h, 038h, 050h, 053h   ; cmp word ptr [eax], 0x5350
        db 00Fh, 085h, 0BDh, 000h, 000h, 000h   ; jne 0x3934d7
        db 083h, 065h, 0ECh, 000h   ; and dword ptr [ebp - 0x14], 0
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        call _XGBufferCreate@8   ; 0x38F797
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 021h   ; jl 0x39344f
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 075h, 010h   ; mov esi, dword ptr [ebp + 0x10]
        call _XGBuffer_GetBufferPointer@4   ; 0x38BC11
        db 08Bh, 04Dh, 014h   ; mov ecx, dword ptr [ebp + 0x14]
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0A4h   ; rep movsb byte ptr es:[edi], byte ptr [esi]
        db 08Bh, 07Dh, 008h   ; mov edi, dword ptr [ebp + 8]
$L_39344f:
        db 0C6h, 045h, 0F3h, 000h   ; mov byte ptr [ebp - 0xd], 0
        db 0C6h, 045h, 0EBh, 000h   ; mov byte ptr [ebp - 0x15], 0
        db 0C6h, 045h, 0E3h, 000h   ; mov byte ptr [ebp - 0x1d], 0
        db 0B3h, 001h   ; mov bl, 1
$L_39345d:
        db 033h, 0C0h   ; xor eax, eax
        db 0C7h, 045h, 0CCh   ; mov dword ptr [ebp - 0x34], 0x41a9c0
        dd _unk_41A9C0
        db 089h, 045h, 0D0h   ; mov dword ptr [ebp - 0x30], eax
        db 089h, 045h, 0D4h   ; mov dword ptr [ebp - 0x2c], eax
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 08Dh, 04Dh, 0CCh   ; lea ecx, [ebp - 0x34]
        db 089h, 045h, 0FCh   ; mov dword ptr [ebp - 4], eax
        call ?Initialize@MyErrorLog@XGRAPHICS@@QAEJPBD@Z   ; 0x391E80
        db 083h, 065h, 0DCh, 000h   ; and dword ptr [ebp - 0x24], 0
        db 080h, 07Dh, 01Bh, 000h   ; cmp byte ptr [ebp + 0x1b], 0
        db 08Bh, 0F0h   ; mov esi, eax
        db 00Fh, 085h, 0AFh, 000h, 000h, 000h   ; jne 0x393539
        db 080h, 03Fh, 000h   ; cmp byte ptr [edi], 0
        db 00Fh, 085h, 0A6h, 000h, 000h, 000h   ; jne 0x393539
        db 084h, 0DBh   ; test bl, bl
        db 074h, 059h   ; je 0x3934f0
        db 085h, 0F6h   ; test esi, esi
        db 00Fh, 08Ch, 084h, 000h, 000h, 000h   ; jl 0x393523
        db 08Dh, 045h, 0DCh   ; lea eax, [ebp - 0x24]
        db 050h   ; push eax
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        call _XGBufferCreate@8   ; 0x38F797
        db 08Bh, 0F0h   ; mov esi, eax
        db 085h, 0F6h   ; test esi, esi
        db 089h, 075h, 030h   ; mov dword ptr [ebp + 0x30], esi
        db 07Ch, 06Fh   ; jl 0x393523
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        db 08Bh, 075h, 010h   ; mov esi, dword ptr [ebp + 0x10]
        call _XGBuffer_GetBufferPointer@4   ; 0x38BC11
        db 08Bh, 04Dh, 014h   ; mov ecx, dword ptr [ebp + 0x14]
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0A4h   ; rep movsb byte ptr es:[edi], byte ptr [esi]
        db 08Bh, 075h, 030h   ; mov esi, dword ptr [ebp + 0x30]
        db 0EBh, 04Ch   ; jmp 0x393523
$L_3934d7:
        db 0F6h, 0C5h, 008h   ; test ch, 8
        db 00Fh, 084h, 06Fh, 0FFh, 0FFh, 0FFh   ; je 0x39344f
        db 0C6h, 047h, 001h, 001h   ; mov byte ptr [edi + 1], 1
        db 0C7h, 045h, 0ECh, 001h, 001h, 000h, 000h   ; mov dword ptr [ebp - 0x14], 0x101
        db 0E9h, 05Fh, 0FFh, 0FFh, 0FFh   ; jmp 0x39344f
$L_3934f0:
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 089h, 045h, 0B0h   ; mov dword ptr [ebp - 0x50], eax
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 0C7h, 045h, 0ACh, 088h, 013h, 000h, 000h   ; mov dword ptr [ebp - 0x54], 0x1388
        db 089h, 045h, 0B4h   ; mov dword ptr [ebp - 0x4c], eax
        db 07Ch, 01Ch   ; jl 0x393523
        db 08Dh, 045h, 0CCh   ; lea eax, [ebp - 0x34]
        db 050h   ; push eax
        db 08Dh, 045h, 0DCh   ; lea eax, [ebp - 0x24]
        db 050h   ; push eax
        db 08Dh, 045h, 0ACh   ; lea eax, [ebp - 0x54]
        db 050h   ; push eax
        db 0FFh, 075h, 030h   ; push dword ptr [ebp + 0x30]
        db 0FFh, 075h, 02Ch   ; push dword ptr [ebp + 0x2c]
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        call ?XGPreprocess@XGRAPHICS@@YGJPBDP6GJPAXH00PADKPAPAUXGBuffer@@@Z1PAU2@3PAUXD3DXErrorLog@1@@Z   ; 0x3A6AF5
        db 08Bh, 0F0h   ; mov esi, eax
$L_393523:
        db 080h, 07Dh, 0EBh, 000h   ; cmp byte ptr [ebp - 0x15], 0
        db 074h, 010h   ; je 0x393539
        db 085h, 0F6h   ; test esi, esi
        db 07Ch, 00Ch   ; jl 0x393539
        db 08Bh, 045h, 020h   ; mov eax, dword ptr [ebp + 0x20]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 005h   ; je 0x393539
        db 08Bh, 04Dh, 0DCh   ; mov ecx, dword ptr [ebp - 0x24]
        db 089h, 008h   ; mov dword ptr [eax], ecx
$L_393539:
        db 033h, 0DBh   ; xor ebx, ebx
        db 033h, 0FFh   ; xor edi, edi
        db 080h, 07Dh, 0EBh, 000h   ; cmp byte ptr [ebp - 0x15], 0
        db 00Fh, 085h, 010h, 002h, 000h, 000h   ; jne 0x393757
        db 08Bh, 045h, 020h   ; mov eax, dword ptr [ebp + 0x20]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 005h   ; je 0x393553
        db 089h, 018h   ; mov dword ptr [eax], ebx
        db 08Dh, 07Dh, 0E4h   ; lea edi, [ebp - 0x1c]
$L_393553:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 00Fh, 08Ch, 0DAh, 000h, 000h, 000h   ; jl 0x393635
        db 080h, 07Dh, 01Bh, 000h   ; cmp byte ptr [ebp + 0x1b], 0
        db 075h, 079h   ; jne 0x3935da
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 080h, 038h, 000h   ; cmp byte ptr [eax], 0
        db 075h, 071h   ; jne 0x3935da
        db 08Dh, 08Dh, 0E8h, 0FBh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x418]
        call ??0CD3DXAssembler@XGRAPHICS@@QAE@XZ   ; 0x3A0F71
        db 08Bh, 075h, 0DCh   ; mov esi, dword ptr [ebp - 0x24]
        db 056h   ; push esi
        db 0C6h, 045h, 0FCh, 001h   ; mov byte ptr [ebp - 4], 1
        call _XGBuffer_GetBufferPointer@4   ; 0x38BC11
        db 08Bh, 0D8h   ; mov ebx, eax
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 050h   ; push eax
        db 08Dh, 045h, 0CCh   ; lea eax, [ebp - 0x34]
        db 050h   ; push eax
        db 057h   ; push edi
        db 0FFh, 075h, 01Ch   ; push dword ptr [ebp + 0x1c]
        db 06Ah, 001h   ; push 1
        db 06Ah, 000h   ; push 0
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 056h   ; push esi
        call _XGBuffer_GetBufferSize@4   ; 0x38BC1B
        db 050h   ; push eax
        db 053h   ; push ebx
        db 08Dh, 08Dh, 0E8h, 0FBh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x418]
        call ?Assemble@CD3DXAssembler@XGRAPHICS@@QAEJPBXIPBDIKPAPAUXGBuffer@@2PAUXD3DXErrorLog@2@PAK@Z   ; 0x3A3BE8
        db 08Bh, 0F0h   ; mov esi, eax
        db 085h, 0F6h   ; test esi, esi
        db 07Ch, 01Ah   ; jl 0x3935c9
        db 083h, 0BDh, 078h, 0FCh, 0FFh, 0FFh, 000h   ; cmp dword ptr [ebp - 0x388], 0
        db 074h, 004h   ; je 0x3935bc
        db 080h, 04Dh, 0EDh, 001h   ; or byte ptr [ebp - 0x13], 1
$L_3935bc:
        db 083h, 0BDh, 07Ch, 0FCh, 0FFh, 0FFh, 000h   ; cmp dword ptr [ebp - 0x384], 0
        db 074h, 004h   ; je 0x3935c9
        db 080h, 04Dh, 0EDh, 002h   ; or byte ptr [ebp - 0x13], 2
$L_3935c9:
        db 08Dh, 08Dh, 0E8h, 0FBh, 0FFh, 0FFh   ; lea ecx, [ebp - 0x418]
        db 0C6h, 045h, 0FCh, 000h   ; mov byte ptr [ebp - 4], 0
        call ??1CD3DXAssembler@XGRAPHICS@@QAE@XZ   ; 0x3A0FF3
        db 033h, 0DBh   ; xor ebx, ebx
$L_3935da:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 057h   ; jl 0x393635
        db 080h, 07Dh, 01Bh, 000h   ; cmp byte ptr [ebp + 0x1b], 0
        db 074h, 038h   ; je 0x39361c
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        call _XGBufferCreate@8   ; 0x38F797
        db 08Bh, 0F0h   ; mov esi, eax
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 089h, 075h, 030h   ; mov dword ptr [ebp + 0x30], esi
        db 07Ch, 03Ch   ; jl 0x393635
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 075h, 010h   ; mov esi, dword ptr [ebp + 0x10]
        call _XGBuffer_GetBufferPointer@4   ; 0x38BC11
        db 08Bh, 04Dh, 014h   ; mov ecx, dword ptr [ebp + 0x14]
        db 08Bh, 0F8h   ; mov edi, eax
        db 08Bh, 0C1h   ; mov eax, ecx
        db 0C1h, 0E9h, 002h   ; shr ecx, 2
        db 0F3h, 0A5h   ; rep movsd dword ptr es:[edi], dword ptr [esi]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 083h, 0E1h, 003h   ; and ecx, 3
        db 0F3h, 0A4h   ; rep movsb byte ptr es:[edi], byte ptr [esi]
        db 08Bh, 075h, 030h   ; mov esi, dword ptr [ebp + 0x30]
        db 033h, 0DBh   ; xor ebx, ebx
$L_39361c:
        db 080h, 07Dh, 0F3h, 000h   ; cmp byte ptr [ebp - 0xd], 0
        db 074h, 013h   ; je 0x393635
        db 080h, 07Dh, 0E3h, 000h   ; cmp byte ptr [ebp - 0x1d], 0
        db 075h, 00Dh   ; jne 0x393635
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        call ?StripDebugInfo@Assembler@XGRAPHICS@@AAEJPAUXGBuffer@@@Z   ; 0x391509
        db 08Bh, 0F0h   ; mov esi, eax
$L_393635:
        db 033h, 0FFh   ; xor edi, edi
        db 080h, 07Dh, 0DBh, 000h   ; cmp byte ptr [ebp - 0x25], 0
        db 074h, 040h   ; je 0x39367d
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 00Ch   ; push 0xc
        call _XMemAlloc@8   ; 0x22FC99
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 00Ah   ; je 0x393657
        db 089h, 018h   ; mov dword ptr [eax], ebx
        db 089h, 058h, 004h   ; mov dword ptr [eax + 4], ebx
        db 089h, 058h, 008h   ; mov dword ptr [eax + 8], ebx
        db 0EBh, 002h   ; jmp 0x393659
$L_393657:
        db 033h, 0C0h   ; xor eax, eax
$L_393659:
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 08Bh, 0F8h   ; mov edi, eax
        db 075h, 005h   ; jne 0x393664
        db 0BEh, 00Eh, 000h, 007h, 080h   ; mov esi, 0x8007000e
$L_393664:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 00Fh, 08Ch, 0AAh, 000h, 000h, 000h   ; jl 0x393716
        db 068h, 020h, 04Eh, 000h, 000h   ; push 0x4e20
        db 08Bh, 0C8h   ; mov ecx, eax
        db 089h, 058h, 008h   ; mov dword ptr [eax + 8], ebx
        call ?GrowTo@Buffer@XGRAPHICS@@QAEJK@Z   ; 0x38F806
        db 08Bh, 0F0h   ; mov esi, eax
$L_39367d:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 00Fh, 08Ch, 091h, 000h, 000h, 000h   ; jl 0x393716
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 074h, 015h   ; je 0x39369e
        db 068h   ; push 0x539778
        dd _unk_539778
        db 068h   ; push 0x3a80f0
        dd _unk_3A80F0
        db 057h   ; push edi
        call ?Printf@Buffer@XGRAPHICS@@QAAJPBDZZ   ; 0x38F884
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
        db 08Bh, 0F0h   ; mov esi, eax
$L_39369e:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 074h   ; jl 0x393716
        db 08Bh, 045h, 0E4h   ; mov eax, dword ptr [ebp - 0x1c]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 03Ah   ; je 0x3936e3
        db 039h, 05Dh, 020h   ; cmp dword ptr [ebp + 0x20], ebx
        db 074h, 035h   ; je 0x3936e3
        db 080h, 07Dh, 0F3h, 000h   ; cmp byte ptr [ebp - 0xd], 0
        db 074h, 02Fh   ; je 0x3936e3
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 050h   ; push eax
        db 089h, 001h   ; mov dword ptr [ecx], eax
        call _XGBuffer_AddRef@4   ; 0x38BC06
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 074h, 020h   ; je 0x3936e3
        db 08Bh, 075h, 0E4h   ; mov esi, dword ptr [ebp - 0x1c]
        db 056h   ; push esi
        call _XGBuffer_GetBufferPointer@4   ; 0x38BC11
        db 056h   ; push esi
        db 08Bh, 0D8h   ; mov ebx, eax
        call _XGBuffer_GetBufferSize@4   ; 0x38BC1B
        db 0C1h, 0E8h, 002h   ; shr eax, 2
        db 050h   ; push eax
        db 053h   ; push ebx
        db 057h   ; push edi
        call ?ListD3DTokens@XGRAPHICS@@YGJPAVBuffer@1@PBKK@Z   ; 0x391419
        db 08Bh, 0F0h   ; mov esi, eax
        db 033h, 0DBh   ; xor ebx, ebx
$L_3936e3:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 02Fh   ; jl 0x393716
        db 080h, 07Dh, 0F3h, 000h   ; cmp byte ptr [ebp - 0xd], 0
        db 075h, 029h   ; jne 0x393716
        db 0FFh, 075h, 0C8h   ; push dword ptr [ebp - 0x38]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 0FFh, 075h, 0C4h   ; push dword ptr [ebp - 0x3c]
        db 08Dh, 045h, 0CCh   ; lea eax, [ebp - 0x34]
        db 050h   ; push eax
        db 057h   ; push edi
        db 0FFh, 075h, 020h   ; push dword ptr [ebp + 0x20]
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 0FFh, 075h, 0ECh   ; push dword ptr [ebp - 0x14]
        db 0FFh, 075h, 0B8h   ; push dword ptr [ebp - 0x48]
        db 0FFh, 075h, 0C0h   ; push dword ptr [ebp - 0x40]
        db 053h   ; push ebx
        db 053h   ; push ebx
        db 0FFh, 075h, 0BCh   ; push dword ptr [ebp - 0x44]
        call ?CompileShaderToUCode@Assembler@XGRAPHICS@@AAEJ_N0000KPAUXGBuffer@@PAPAU3@PAVBuffer@2@PAUXD3DXErrorLog@2@00@Z   ; 0x393271
        db 08Bh, 0F0h   ; mov esi, eax
$L_393716:
        db 039h, 05Dh, 0DCh   ; cmp dword ptr [ebp - 0x24], ebx
        db 074h, 00Bh   ; je 0x393726
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        call _XGBuffer_Release@4   ; 0x38F762
        db 089h, 05Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ebx
$L_393726:
        db 039h, 05Dh, 0E4h   ; cmp dword ptr [ebp - 0x1c], ebx
        db 074h, 00Bh   ; je 0x393736
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        call _XGBuffer_Release@4   ; 0x38F762
        db 089h, 05Dh, 0E4h   ; mov dword ptr [ebp - 0x1c], ebx
$L_393736:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 010h   ; jl 0x39374a
        db 039h, 05Dh, 028h   ; cmp dword ptr [ebp + 0x28], ebx
        db 074h, 00Bh   ; je 0x39374a
        db 0FFh, 075h, 028h   ; push dword ptr [ebp + 0x28]
        db 057h   ; push edi
        call ?XGBufferCreateFromBuffer@XGRAPHICS@@YGJPAVBuffer@1@PAPAUXGBuffer@@@Z   ; 0x3914B9
        db 08Bh, 0F0h   ; mov esi, eax
$L_39374a:
        db 03Bh, 0FBh   ; cmp edi, ebx
        db 074h, 009h   ; je 0x393757
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CFh   ; mov ecx, edi
        call ??_GBuffer@XGRAPHICS@@QAEPAXI@Z   ; 0x391495
$L_393757:
        db 039h, 05Dh, 024h   ; cmp dword ptr [ebp + 0x24], ebx
        db 074h, 011h   ; je 0x39376d
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 0FFh, 075h, 0D0h   ; push dword ptr [ebp - 0x30]
        call ?XGBufferCreateFromBuffer@XGRAPHICS@@YGJPAVBuffer@1@PAPAUXGBuffer@@@Z   ; 0x3914B9
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 012h   ; jl 0x39377d
        db 08Bh, 0F0h   ; mov esi, eax
$L_39376d:
        db 03Bh, 0F3h   ; cmp esi, ebx
        db 07Ch, 00Ch   ; jl 0x39377d
        db 08Bh, 045h, 034h   ; mov eax, dword ptr [ebp + 0x34]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 005h   ; je 0x39377d
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 089h, 008h   ; mov dword ptr [eax], ecx
$L_39377d:
        db 08Bh, 04Dh, 0D0h   ; mov ecx, dword ptr [ebp - 0x30]
        db 03Bh, 0CBh   ; cmp ecx, ebx
        db 0C7h, 045h, 0CCh   ; mov dword ptr [ebp - 0x34], 0x41a9c0
        dd _unk_41A9C0
        db 074h, 007h   ; je 0x393792
        db 06Ah, 001h   ; push 1
        call ??_GBuffer@XGRAPHICS@@QAEPAXI@Z   ; 0x391495
$L_393792:
        db 08Bh, 04Dh, 0F4h   ; mov ecx, dword ptr [ebp - 0xc]
        db 05Fh   ; pop edi
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h   ; mov dword ptr fs:[0], ecx
        db 0C9h   ; leave 
        db 0C2h, 030h, 000h   ; ret 0x30

; // match: _XGAssembleShader@44 @ 0x003937A5
PUBLIC _XGAssembleShader@44
_XGAssembleShader@44:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 0ECh, 010h   ; sub esp, 0x10
        db 0FFh, 075h, 030h   ; push dword ptr [ebp + 0x30]
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 0FFh, 075h, 02Ch   ; push dword ptr [ebp + 0x2c]
        db 0FFh, 075h, 028h   ; push dword ptr [ebp + 0x28]
        db 0FFh, 075h, 024h   ; push dword ptr [ebp + 0x24]
        db 0FFh, 075h, 020h   ; push dword ptr [ebp + 0x20]
        db 0FFh, 075h, 01Ch   ; push dword ptr [ebp + 0x1c]
        db 0FFh, 075h, 018h   ; push dword ptr [ebp + 0x18]
        db 0FFh, 075h, 014h   ; push dword ptr [ebp + 0x14]
        db 0FFh, 075h, 010h   ; push dword ptr [ebp + 0x10]
        db 0FFh, 075h, 00Ch   ; push dword ptr [ebp + 0xc]
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 050h   ; push eax
        db 0E8h, 013h, 0FBh, 0FFh, 0FFh   ; call 0x3932e8
        db 0C9h   ; leave 
        db 0C2h, 02Ch, 000h   ; ret 0x2c
seg7 ENDS

seg8 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??1CompMask@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ @ 0x00393997
PUBLIC ??1CompMask@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ
??1CompMask@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41a9d0
        dd ??_7CompMask@VS_GRAPH_OPTIMIZER@XGRAPHICS@@6B@
        db 0C3h   ; ret 
seg8 ENDS

seg9 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_393B18 @ 0x00393B18
PUBLIC _sub_393B18
_sub_393B18:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41a9d4
        dd _unk_41A9D4
        db 0C3h   ; ret 
seg9 ENDS

seg11 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_39465F @ 0x0039465F
PUBLIC _sub_39465F
_sub_39465F:
$L_39465f:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 01Ch   ; je 0x394684
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 0E8h, 0EBh, 0FFh, 0FFh, 0FFh   ; call 0x39465f
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 0E8h, 0E3h, 0FFh, 0FFh, 0FFh   ; call 0x39465f
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
$L_394684:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg11 ENDS

seg13 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_39479E @ 0x0039479E
PUBLIC _sub_39479E
_sub_39479E:
$L_39479e:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 01Ch   ; je 0x3947c3
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 0E8h, 0EBh, 0FFh, 0FFh, 0FFh   ; call 0x39479e
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 0E8h, 0E3h, 0FFh, 0FFh, 0FFh   ; call 0x39479e
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
$L_3947c3:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?clear_node@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z @ 0x003947C7
PUBLIC ?clear_node@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z
?clear_node@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z:
$L_3947c7:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 01Ch   ; je 0x3947ec
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 0E8h, 0EBh, 0FFh, 0FFh, 0FFh   ; call 0x3947c7
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 0E8h, 0E3h, 0FFh, 0FFh, 0FFh   ; call 0x3947c7
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
$L_3947ec:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg13 ENDS

seg14 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?clear_node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z @ 0x0039482D
PUBLIC ?clear_node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z
?clear_node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z:
$L_39482d:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 01Ch   ; je 0x394852
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 0E8h, 0EBh, 0FFh, 0FFh, 0FFh   ; call 0x39482d
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 0E8h, 0E3h, 0FFh, 0FFh, 0FFh   ; call 0x39482d
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
$L_394852:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_394856 @ 0x00394856
PUBLIC _sub_394856
_sub_394856:
$L_394856:
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 008h   ; mov esi, dword ptr [esp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 01Ch   ; je 0x39487b
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 0E8h, 0EBh, 0FFh, 0FFh, 0FFh   ; call 0x394856
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 0E8h, 0E3h, 0FFh, 0FFh, 0FFh   ; call 0x394856
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
$L_39487b:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg14 ENDS

seg16 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_GSwizzle@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00394A0B
PUBLIC ??_GSwizzle@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_GSwizzle@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41a9d4
        dd _unk_41A9D4
        db 074h, 00Bh   ; je 0x394a26
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_394a26:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg16 ENDS

seg17 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_39564C @ 0x0039564C
PUBLIC _sub_39564C
_sub_39564C:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call _sub_394608   ; 0x394608
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg17 ENDS

seg18 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_39567C @ 0x0039567C
PUBLIC _sub_39567C
_sub_39567C:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call _sub_39465F   ; 0x39465F
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg18 ENDS

seg19 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?clear@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ @ 0x003956E6
PUBLIC ?clear@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ
?clear@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call _sub_394702   ; 0x394702
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 

; // match: ?clear@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ @ 0x003956FB
PUBLIC ?clear@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ
?clear@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call _sub_39479E   ; 0x39479E
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg19 ENDS

seg20 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_395738 @ 0x00395738
PUBLIC _sub_395738
_sub_395738:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa20
        dd _unk_41AA20
        db 074h, 00Bh   ; je 0x395753
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395753:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?clear@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ @ 0x00395759
PUBLIC ?clear@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ
?clear@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call ?clear_node@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z   ; 0x3947C7
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 

; // match: _sub_39576E @ 0x0039576E
PUBLIC _sub_39576E
_sub_39576E:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x41aa24
        dd _unk_41AA24
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0C7h, 040h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 1
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_395796 @ 0x00395796
PUBLIC _sub_395796
_sub_395796:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa24
        dd _unk_41AA24
        db 074h, 00Bh   ; je 0x3957b1
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3957b1:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_3957B7 @ 0x003957B7
PUBLIC _sub_3957B7
_sub_3957B7:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x41aa28
        dd _unk_41AA28
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0C7h, 040h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 1
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_3957DF @ 0x003957DF
PUBLIC _sub_3957DF
_sub_3957DF:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa28
        dd _unk_41AA28
        db 074h, 00Bh   ; je 0x3957fa
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3957fa:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_395800 @ 0x00395800
PUBLIC _sub_395800
_sub_395800:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x41aa2c
        dd _unk_41AA2C
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0C7h, 040h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 1
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_395828 @ 0x00395828
PUBLIC _sub_395828
_sub_395828:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa2c
        dd _unk_41AA2C
        db 074h, 00Bh   ; je 0x395843
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395843:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?clear@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ @ 0x00395849
PUBLIC ?clear@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ
?clear@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call ?clear_node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z   ; 0x39482D
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 
seg20 ENDS

seg21 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_3958F3 @ 0x003958F3
PUBLIC _sub_3958F3
_sub_3958F3:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        call _sub_394856   ; 0x394856
        db 083h, 066h, 008h, 000h   ; and dword ptr [esi + 8], 0
        db 083h, 066h, 00Ch, 000h   ; and dword ptr [esi + 0xc], 0
        db 05Eh   ; pop esi
        db 0C3h   ; ret 

; // match: ??0node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVInstruction@23@PAV0123@@Z @ 0x00395908
PUBLIC ??0node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVInstruction@23@PAV0123@@Z
??0node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVInstruction@23@PAV0123@@Z:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x41aa30
        dd _unk_41AA30
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0C7h, 040h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 1
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_395930 @ 0x00395930
PUBLIC _sub_395930
_sub_395930:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa30
        dd _unk_41AA30
        db 074h, 00Bh   ; je 0x39594b
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_39594b:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_395951 @ 0x00395951
PUBLIC _sub_395951
_sub_395951:
        db 08Bh, 0C1h   ; mov eax, ecx
        db 08Bh, 04Ch, 024h, 004h   ; mov ecx, dword ptr [esp + 4]
        db 083h, 060h, 00Ch, 000h   ; and dword ptr [eax + 0xc], 0
        db 083h, 060h, 010h, 000h   ; and dword ptr [eax + 0x10], 0
        db 089h, 048h, 004h   ; mov dword ptr [eax + 4], ecx
        db 08Bh, 04Ch, 024h, 008h   ; mov ecx, dword ptr [esp + 8]
        db 0C7h, 000h   ; mov dword ptr [eax], 0x41aa34
        dd _unk_41AA34
        db 089h, 048h, 008h   ; mov dword ptr [eax + 8], ecx
        db 0C7h, 040h, 014h, 001h, 000h, 000h, 000h   ; mov dword ptr [eax + 0x14], 1
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_395979 @ 0x00395979
PUBLIC _sub_395979
_sub_395979:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa34
        dd _unk_41AA34
        db 074h, 00Bh   ; je 0x395994
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395994:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg21 ENDS

seg22 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_Gnode@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x003959C9
PUBLIC ??_Gnode@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_Gnode@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa38
        dd _unk_41AA38
        db 074h, 00Bh   ; je 0x3959e4
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3959e4:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg22 ENDS

seg23 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?RemoveAllCollections@Register@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ @ 0x00395BC8
PUBLIC ?RemoveAllCollections@Register@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ
?RemoveAllCollections@Register@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ:
        db 0FFh, 035h   ; push dword ptr [0x3aa2b0]
        dd _unk_3AA2B0
        call _sub_394608   ; 0x394608
        db 083h, 025h   ; and dword ptr [0x3aa2b0], 0
        dd _unk_3AA2B0
        db 000h
        db 083h, 025h   ; and dword ptr [0x3aa2b4], 0
        dd _unk_3AA2B4
        db 000h
        db 0C3h   ; ret 
seg23 ENDS

seg24 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?RemoveAllCollections@Instruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ @ 0x00395C18
PUBLIC ?RemoveAllCollections@Instruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ
?RemoveAllCollections@Instruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ:
        db 0FFh, 035h   ; push dword ptr [0x3aa2c0]
        dd _unk_3AA2C0
        call _sub_39465F   ; 0x39465F
        db 083h, 025h   ; and dword ptr [0x3aa2c0], 0
        dd _unk_3AA2C0
        db 000h
        db 083h, 025h   ; and dword ptr [0x3aa2c4], 0
        dd _unk_3AA2C4
        db 000h
        db 0C3h   ; ret 
seg24 ENDS

seg25 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_395ECD @ 0x00395ECD
PUBLIC _sub_395ECD
_sub_395ECD:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41a9f8
        dd _unk_41A9F8
        jmp ?clear@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395759
seg25 ENDS

seg26 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_395EF5 @ 0x00395EF5
PUBLIC _sub_395EF5
_sub_395EF5:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41aa10
        dd _unk_41AA10
        jmp ?clear@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395849

; // match: _sub_395F00 @ 0x00395F00
PUBLIC _sub_395F00
_sub_395F00:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41a9dc
        dd _unk_41A9DC
        jmp _sub_3958F3   ; 0x3958F3
seg26 ENDS

seg27 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_395F31 @ 0x00395F31
PUBLIC _sub_395F31
_sub_395F31:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41a9f0
        dd _unk_41A9F0
        call _sub_39564C   ; 0x39564C
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x395f51
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395f51:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ??_G?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00395F57
PUBLIC ??_G?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41a9f8
        dd _unk_41A9F8
        call ?clear@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395759
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x395f77
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395f77:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_395F7D @ 0x00395F7D
PUBLIC _sub_395F7D
_sub_395F7D:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa00
        dd _unk_41AA00
        call _sub_39567C   ; 0x39567C
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x395f9d
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395f9d:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ??_G?$list@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00395FA3
PUBLIC ??_G?$list@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$list@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_395ED8   ; 0x395ED8
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x395fc1
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x395fc1
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395fc1:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ??_G?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00395FC7
PUBLIC ??_G?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa10
        dd _unk_41AA10
        call ?clear@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395849
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x395fe7
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_395fe7:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ??_G?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00395FED
PUBLIC ??_G?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa18
        dd _unk_41AA18
        call ?clear@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x3956E6
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x39600d
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_39600d:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ??_G?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00396013
PUBLIC ??_G?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41a9dc
        dd _unk_41A9DC
        call _sub_3958F3   ; 0x3958F3
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x396033
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_396033:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg27 ENDS

seg28 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?Init@GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ @ 0x003961BA
PUBLIC ?Init@GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ
?Init@GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXXZ:
        db 033h, 0C0h   ; xor eax, eax
        db 050h   ; push eax
        db 0A3h   ; mov dword ptr [0x3aa2a0], eax
        dd _unk_3AA2A0
        db 0A3h   ; mov dword ptr [0x3aa2a4], eax
        dd _unk_3AA2A4
        call _sub_39479E   ; 0x39479E
        db 0C3h   ; ret 
seg28 ENDS

seg29 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??1?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ @ 0x003969E0
PUBLIC ??1?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ
??1?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ:
$L_3969e0:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41aa18
        dd _unk_41AA18
        jmp ?clear@?$set@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$pair_less@V?$pair@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x3956E6

; // match: ??_G?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x003969EB
PUBLIC ??_G?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_G?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0E8h, 0EDh, 0FFh, 0FFh, 0FFh   ; call 0x3969e0
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x396a09
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x396a09
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_396a09:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg29 ENDS

seg30 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_396BA3 @ 0x00396BA3
PUBLIC _sub_396BA3
_sub_396BA3:
$L_396ba3:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 005h   ; je 0x396bb3
        db 08Bh, 057h, 014h   ; mov edx, dword ptr [edi + 0x14]
        db 0EBh, 002h   ; jmp 0x396bb5
$L_396bb3:
        db 033h, 0D2h   ; xor edx, edx
$L_396bb5:
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 005h   ; je 0x396bc2
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 0EBh, 002h   ; jmp 0x396bc4
$L_396bc2:
        db 033h, 0C0h   ; xor eax, eax
$L_396bc4:
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 09Fh, 0C0h   ; setg al
        db 084h, 0C0h   ; test al, al
        db 08Bh, 0DFh   ; mov ebx, edi
        db 075h, 002h   ; jne 0x396bd1
        db 08Bh, 0DEh   ; mov ebx, esi
$L_396bd1:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 007h   ; jne 0x396bdc
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 086h, 000h, 000h, 000h   ; jmp 0x396c62
$L_396bdc:
        db 083h, 063h, 008h, 000h   ; and dword ptr [ebx + 8], 0
        db 084h, 0C0h   ; test al, al
        db 074h, 032h   ; je 0x396c16
        db 085h, 0F6h   ; test esi, esi
        db 074h, 068h   ; je 0x396c50
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 056h   ; push esi
        db 0E8h, 0AFh, 0FFh, 0FFh, 0FFh   ; call 0x396ba3
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 074h, 003h   ; je 0x396bfe
        db 089h, 070h, 008h   ; mov dword ptr [eax + 8], esi
$L_396bfe:
        db 089h, 077h, 00Ch   ; mov dword ptr [edi + 0xc], esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0EBh, 030h   ; jmp 0x396c46
$L_396c16:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 036h   ; je 0x396c50
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 057h   ; push edi
        db 0E8h, 07Dh, 0FFh, 0FFh, 0FFh   ; call 0x396ba3
        db 085h, 0C0h   ; test eax, eax
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 074h, 003h   ; je 0x396c30
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_396c30:
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 077h, 008h   ; mov dword ptr [edi + 8], esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
$L_396c46:
        call ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x39604E
        db 0EBh, 003h   ; jmp 0x396c50
$L_396c4d:
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
$L_396c50:
        db 083h, 07Bh, 008h, 000h   ; cmp dword ptr [ebx + 8], 0
        db 075h, 0F7h   ; jne 0x396c4d
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ   ; 0x3959EA
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 0C3h   ; mov eax, ebx
$L_396c62:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: _sub_396C68 @ 0x00396C68
PUBLIC _sub_396C68
_sub_396C68:
$L_396c68:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 005h   ; je 0x396c78
        db 08Bh, 057h, 014h   ; mov edx, dword ptr [edi + 0x14]
        db 0EBh, 002h   ; jmp 0x396c7a
$L_396c78:
        db 033h, 0D2h   ; xor edx, edx
$L_396c7a:
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 005h   ; je 0x396c87
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 0EBh, 002h   ; jmp 0x396c89
$L_396c87:
        db 033h, 0C0h   ; xor eax, eax
$L_396c89:
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 09Fh, 0C0h   ; setg al
        db 084h, 0C0h   ; test al, al
        db 08Bh, 0DFh   ; mov ebx, edi
        db 075h, 002h   ; jne 0x396c96
        db 08Bh, 0DEh   ; mov ebx, esi
$L_396c96:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 007h   ; jne 0x396ca1
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 086h, 000h, 000h, 000h   ; jmp 0x396d27
$L_396ca1:
        db 083h, 063h, 008h, 000h   ; and dword ptr [ebx + 8], 0
        db 084h, 0C0h   ; test al, al
        db 074h, 032h   ; je 0x396cdb
        db 085h, 0F6h   ; test esi, esi
        db 074h, 068h   ; je 0x396d15
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 056h   ; push esi
        db 0E8h, 0AFh, 0FFh, 0FFh, 0FFh   ; call 0x396c68
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 074h, 003h   ; je 0x396cc3
        db 089h, 070h, 008h   ; mov dword ptr [eax + 8], esi
$L_396cc3:
        db 089h, 077h, 00Ch   ; mov dword ptr [edi + 0xc], esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0EBh, 030h   ; jmp 0x396d0b
$L_396cdb:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 036h   ; je 0x396d15
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 057h   ; push edi
        db 0E8h, 07Dh, 0FFh, 0FFh, 0FFh   ; call 0x396c68
        db 085h, 0C0h   ; test eax, eax
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 074h, 003h   ; je 0x396cf5
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_396cf5:
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 077h, 008h   ; mov dword ptr [edi + 8], esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
$L_396d0b:
        call ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x39604E
        db 0EBh, 003h   ; jmp 0x396d15
$L_396d12:
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
$L_396d15:
        db 083h, 07Bh, 008h, 000h   ; cmp dword ptr [ebx + 8], 0
        db 075h, 0F7h   ; jne 0x396d12
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ   ; 0x3959EA
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 0C3h   ; mov eax, ebx
$L_396d27:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: _sub_396D2D @ 0x00396D2D
PUBLIC _sub_396D2D
_sub_396D2D:
$L_396d2d:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 005h   ; je 0x396d3d
        db 08Bh, 057h, 014h   ; mov edx, dword ptr [edi + 0x14]
        db 0EBh, 002h   ; jmp 0x396d3f
$L_396d3d:
        db 033h, 0D2h   ; xor edx, edx
$L_396d3f:
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 005h   ; je 0x396d4c
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 0EBh, 002h   ; jmp 0x396d4e
$L_396d4c:
        db 033h, 0C0h   ; xor eax, eax
$L_396d4e:
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 09Fh, 0C0h   ; setg al
        db 084h, 0C0h   ; test al, al
        db 08Bh, 0DFh   ; mov ebx, edi
        db 075h, 002h   ; jne 0x396d5b
        db 08Bh, 0DEh   ; mov ebx, esi
$L_396d5b:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 007h   ; jne 0x396d66
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 086h, 000h, 000h, 000h   ; jmp 0x396dec
$L_396d66:
        db 083h, 063h, 008h, 000h   ; and dword ptr [ebx + 8], 0
        db 084h, 0C0h   ; test al, al
        db 074h, 032h   ; je 0x396da0
        db 085h, 0F6h   ; test esi, esi
        db 074h, 068h   ; je 0x396dda
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 056h   ; push esi
        db 0E8h, 0AFh, 0FFh, 0FFh, 0FFh   ; call 0x396d2d
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 074h, 003h   ; je 0x396d88
        db 089h, 070h, 008h   ; mov dword ptr [eax + 8], esi
$L_396d88:
        db 089h, 077h, 00Ch   ; mov dword ptr [edi + 0xc], esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0EBh, 030h   ; jmp 0x396dd0
$L_396da0:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 036h   ; je 0x396dda
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 057h   ; push edi
        db 0E8h, 07Dh, 0FFh, 0FFh, 0FFh   ; call 0x396d2d
        db 085h, 0C0h   ; test eax, eax
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 074h, 003h   ; je 0x396dba
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_396dba:
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 077h, 008h   ; mov dword ptr [edi + 8], esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
$L_396dd0:
        call ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x39604E
        db 0EBh, 003h   ; jmp 0x396dda
$L_396dd7:
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
$L_396dda:
        db 083h, 07Bh, 008h, 000h   ; cmp dword ptr [ebx + 8], 0
        db 075h, 0F7h   ; jne 0x396dd7
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ   ; 0x3959EA
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 0C3h   ; mov eax, ebx
$L_396dec:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc

; // match: _sub_396DF2 @ 0x00396DF2
PUBLIC _sub_396DF2
_sub_396DF2:
$L_396df2:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 005h   ; je 0x396e02
        db 08Bh, 057h, 014h   ; mov edx, dword ptr [edi + 0x14]
        db 0EBh, 002h   ; jmp 0x396e04
$L_396e02:
        db 033h, 0D2h   ; xor edx, edx
$L_396e04:
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 005h   ; je 0x396e11
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 0EBh, 002h   ; jmp 0x396e13
$L_396e11:
        db 033h, 0C0h   ; xor eax, eax
$L_396e13:
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 09Fh, 0C0h   ; setg al
        db 084h, 0C0h   ; test al, al
        db 08Bh, 0DFh   ; mov ebx, edi
        db 075h, 002h   ; jne 0x396e20
        db 08Bh, 0DEh   ; mov ebx, esi
$L_396e20:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 007h   ; jne 0x396e2b
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 086h, 000h, 000h, 000h   ; jmp 0x396eb1
$L_396e2b:
        db 083h, 063h, 008h, 000h   ; and dword ptr [ebx + 8], 0
        db 084h, 0C0h   ; test al, al
        db 074h, 032h   ; je 0x396e65
        db 085h, 0F6h   ; test esi, esi
        db 074h, 068h   ; je 0x396e9f
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 056h   ; push esi
        db 0E8h, 0AFh, 0FFh, 0FFh, 0FFh   ; call 0x396df2
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 074h, 003h   ; je 0x396e4d
        db 089h, 070h, 008h   ; mov dword ptr [eax + 8], esi
$L_396e4d:
        db 089h, 077h, 00Ch   ; mov dword ptr [edi + 0xc], esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0EBh, 030h   ; jmp 0x396e95
$L_396e65:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 036h   ; je 0x396e9f
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 057h   ; push edi
        db 0E8h, 07Dh, 0FFh, 0FFh, 0FFh   ; call 0x396df2
        db 085h, 0C0h   ; test eax, eax
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 074h, 003h   ; je 0x396e7f
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_396e7f:
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 077h, 008h   ; mov dword ptr [edi + 8], esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
$L_396e95:
        call ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x39604E
        db 0EBh, 003h   ; jmp 0x396e9f
$L_396e9c:
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
$L_396e9f:
        db 083h, 07Bh, 008h, 000h   ; cmp dword ptr [ebx + 8], 0
        db 075h, 0F7h   ; jne 0x396e9c
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ   ; 0x3959EA
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 0C3h   ; mov eax, ebx
$L_396eb1:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg30 ENDS

seg31 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_397043 @ 0x00397043
PUBLIC _sub_397043
_sub_397043:
$L_397043:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 08Bh, 07Ch, 024h, 018h   ; mov edi, dword ptr [esp + 0x18]
        db 085h, 0FFh   ; test edi, edi
        db 074h, 005h   ; je 0x397053
        db 08Bh, 057h, 014h   ; mov edx, dword ptr [edi + 0x14]
        db 0EBh, 002h   ; jmp 0x397055
$L_397053:
        db 033h, 0D2h   ; xor edx, edx
$L_397055:
        db 08Bh, 074h, 024h, 014h   ; mov esi, dword ptr [esp + 0x14]
        db 085h, 0F6h   ; test esi, esi
        db 074h, 005h   ; je 0x397062
        db 08Bh, 046h, 014h   ; mov eax, dword ptr [esi + 0x14]
        db 0EBh, 002h   ; jmp 0x397064
$L_397062:
        db 033h, 0C0h   ; xor eax, eax
$L_397064:
        db 03Bh, 0D0h   ; cmp edx, eax
        db 00Fh, 09Fh, 0C0h   ; setg al
        db 084h, 0C0h   ; test al, al
        db 08Bh, 0DFh   ; mov ebx, edi
        db 075h, 002h   ; jne 0x397071
        db 08Bh, 0DEh   ; mov ebx, esi
$L_397071:
        db 085h, 0DBh   ; test ebx, ebx
        db 075h, 007h   ; jne 0x39707c
        db 033h, 0C0h   ; xor eax, eax
        db 0E9h, 086h, 000h, 000h, 000h   ; jmp 0x397102
$L_39707c:
        db 083h, 063h, 008h, 000h   ; and dword ptr [ebx + 8], 0
        db 084h, 0C0h   ; test al, al
        db 074h, 032h   ; je 0x3970b6
        db 085h, 0F6h   ; test esi, esi
        db 074h, 068h   ; je 0x3970f0
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 056h   ; push esi
        db 0E8h, 0AFh, 0FFh, 0FFh, 0FFh   ; call 0x397043
        db 085h, 0C0h   ; test eax, eax
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 074h, 003h   ; je 0x39709e
        db 089h, 070h, 008h   ; mov dword ptr [eax + 8], esi
$L_39709e:
        db 089h, 077h, 00Ch   ; mov dword ptr [edi + 0xc], esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 089h, 07Eh, 008h   ; mov dword ptr [esi + 8], edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0EBh, 030h   ; jmp 0x3970e6
$L_3970b6:
        db 085h, 0FFh   ; test edi, edi
        db 074h, 036h   ; je 0x3970f0
        db 0FFh, 077h, 00Ch   ; push dword ptr [edi + 0xc]
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 057h   ; push edi
        db 0E8h, 07Dh, 0FFh, 0FFh, 0FFh   ; call 0x397043
        db 085h, 0C0h   ; test eax, eax
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
        db 074h, 003h   ; je 0x3970d0
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_3970d0:
        db 089h, 07Eh, 010h   ; mov dword ptr [esi + 0x10], edi
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 077h, 008h   ; mov dword ptr [edi + 8], esi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?depth_fix@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x395A22
        db 08Bh, 0CFh   ; mov ecx, edi
$L_3970e6:
        call ?balance@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXXZ   ; 0x39604E
        db 0EBh, 003h   ; jmp 0x3970f0
$L_3970ed:
        db 08Bh, 05Bh, 008h   ; mov ebx, dword ptr [ebx + 8]
$L_3970f0:
        db 083h, 07Bh, 008h, 000h   ; cmp dword ptr [ebx + 8], 0
        db 075h, 0F7h   ; jne 0x3970ed
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?depth_check@node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEHXZ   ; 0x3959EA
        db 089h, 043h, 014h   ; mov dword ptr [ebx + 0x14], eax
        db 08Bh, 0C3h   ; mov eax, ebx
$L_397102:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C2h, 00Ch, 000h   ; ret 0xc
seg31 ENDS

seg32 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_397571 @ 0x00397571
PUBLIC _sub_397571
_sub_397571:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 075h, 004h   ; jne 0x397583
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 059h   ; jmp 0x3975dc
$L_397583:
        db 057h   ; push edi
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        call ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ   ; 0x3947F0
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_0   ; 0x396BA3
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x3975ca
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x3975b0
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_3975b0:
        db 039h, 077h, 00Ch   ; cmp dword ptr [edi + 0xc], esi
        db 075h, 003h   ; jne 0x3975b8
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
$L_3975b8:
        db 039h, 077h, 010h   ; cmp dword ptr [edi + 0x10], esi
        db 075h, 003h   ; jne 0x3975c0
        db 089h, 047h, 010h   ; mov dword ptr [edi + 0x10], eax
$L_3975c0:
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 003h   ; jmp 0x3975cd
$L_3975ca:
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
$L_3975cd:
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
        db 0FFh, 04Bh, 00Ch   ; dec dword ptr [ebx + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 05Fh   ; pop edi
$L_3975dc:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_3975E2 @ 0x003975E2
PUBLIC _sub_3975E2
_sub_3975E2:
$L_3975e2:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 010h   ; mov esi, dword ptr [esp + 0x10]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 075h, 001h   ; jne 0x3975f0
        db 0CCh   ; int3 
$L_3975f0:
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 08Bh, 05Ch, 024h, 010h   ; mov ebx, dword ptr [esp + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 076h, 036h   ; jbe 0x397631
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 038h   ; jne 0x39763a
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x39761d
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_0   ; 0x39576E
        db 0EBh, 002h   ; jmp 0x39761f
$L_39761d:
        db 033h, 0C0h   ; xor eax, eax
$L_39761f:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_397622:
        db 0FFh, 047h, 00Ch   ; inc dword ptr [edi + 0xc]
$L_397625:
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0D8h   ; mov ebx, eax
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 038h   ; jmp 0x397669
$L_397631:
        db 073h, 034h   ; jae 0x397667
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397645
$L_39763a:
        db 050h   ; push eax
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0E8h, 09Fh, 0FFh, 0FFh, 0FFh   ; call 0x3975e2
        db 0EBh, 0E0h   ; jmp 0x397625
$L_397645:
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397660
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_0   ; 0x39576E
        db 0EBh, 002h   ; jmp 0x397662
$L_397660:
        db 033h, 0C0h   ; xor eax, eax
$L_397662:
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 0EBh, 0BBh   ; jmp 0x397622
$L_397667:
        db 08Bh, 0DEh   ; mov ebx, esi
$L_397669:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 0C3h   ; mov eax, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8

; // match: ?erase@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z @ 0x00397671
PUBLIC ?erase@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z
?erase@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 075h, 004h   ; jne 0x397683
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 059h   ; jmp 0x3976dc
$L_397683:
        db 057h   ; push edi
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        call ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ   ; 0x3947F0
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_1   ; 0x396C68
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x3976ca
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x3976b0
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_3976b0:
        db 039h, 077h, 00Ch   ; cmp dword ptr [edi + 0xc], esi
        db 075h, 003h   ; jne 0x3976b8
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
$L_3976b8:
        db 039h, 077h, 010h   ; cmp dword ptr [edi + 0x10], esi
        db 075h, 003h   ; jne 0x3976c0
        db 089h, 047h, 010h   ; mov dword ptr [edi + 0x10], eax
$L_3976c0:
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 003h   ; jmp 0x3976cd
$L_3976ca:
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
$L_3976cd:
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
        db 0FFh, 04Bh, 00Ch   ; dec dword ptr [ebx + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 05Fh   ; pop edi
$L_3976dc:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@PAV4123@@Z @ 0x003976E2
PUBLIC ?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@PAV4123@@Z
?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@PAV4123@@Z:
$L_3976e2:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 010h   ; mov esi, dword ptr [esp + 0x10]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 075h, 001h   ; jne 0x3976f0
        db 0CCh   ; int3 
$L_3976f0:
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 08Bh, 05Ch, 024h, 010h   ; mov ebx, dword ptr [esp + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 076h, 036h   ; jbe 0x397731
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 038h   ; jne 0x39773a
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x39771d
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_1   ; 0x3957B7
        db 0EBh, 002h   ; jmp 0x39771f
$L_39771d:
        db 033h, 0C0h   ; xor eax, eax
$L_39771f:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_397722:
        db 0FFh, 047h, 00Ch   ; inc dword ptr [edi + 0xc]
$L_397725:
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0D8h   ; mov ebx, eax
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 038h   ; jmp 0x397769
$L_397731:
        db 073h, 034h   ; jae 0x397767
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397745
$L_39773a:
        db 050h   ; push eax
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0E8h, 09Fh, 0FFh, 0FFh, 0FFh   ; call 0x3976e2
        db 0EBh, 0E0h   ; jmp 0x397725
$L_397745:
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397760
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_1   ; 0x3957B7
        db 0EBh, 002h   ; jmp 0x397762
$L_397760:
        db 033h, 0C0h   ; xor eax, eax
$L_397762:
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 0EBh, 0BBh   ; jmp 0x397722
$L_397767:
        db 08Bh, 0DEh   ; mov ebx, esi
$L_397769:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 0C3h   ; mov eax, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8

; // match: _sub_397771 @ 0x00397771
PUBLIC _sub_397771
_sub_397771:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 075h, 004h   ; jne 0x397783
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 059h   ; jmp 0x3977dc
$L_397783:
        db 057h   ; push edi
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        call ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ   ; 0x3947F0
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_2   ; 0x396D2D
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x3977ca
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x3977b0
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_3977b0:
        db 039h, 077h, 00Ch   ; cmp dword ptr [edi + 0xc], esi
        db 075h, 003h   ; jne 0x3977b8
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
$L_3977b8:
        db 039h, 077h, 010h   ; cmp dword ptr [edi + 0x10], esi
        db 075h, 003h   ; jne 0x3977c0
        db 089h, 047h, 010h   ; mov dword ptr [edi + 0x10], eax
$L_3977c0:
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 003h   ; jmp 0x3977cd
$L_3977ca:
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
$L_3977cd:
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
        db 0FFh, 04Bh, 00Ch   ; dec dword ptr [ebx + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 05Fh   ; pop edi
$L_3977dc:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_3977E2 @ 0x003977E2
PUBLIC _sub_3977E2
_sub_3977E2:
$L_3977e2:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 010h   ; mov esi, dword ptr [esp + 0x10]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 075h, 001h   ; jne 0x3977f0
        db 0CCh   ; int3 
$L_3977f0:
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 08Bh, 05Ch, 024h, 010h   ; mov ebx, dword ptr [esp + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 076h, 036h   ; jbe 0x397831
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 038h   ; jne 0x39783a
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x39781d
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_2   ; 0x395800
        db 0EBh, 002h   ; jmp 0x39781f
$L_39781d:
        db 033h, 0C0h   ; xor eax, eax
$L_39781f:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_397822:
        db 0FFh, 047h, 00Ch   ; inc dword ptr [edi + 0xc]
$L_397825:
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0D8h   ; mov ebx, eax
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 038h   ; jmp 0x397869
$L_397831:
        db 073h, 034h   ; jae 0x397867
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397845
$L_39783a:
        db 050h   ; push eax
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0E8h, 09Fh, 0FFh, 0FFh, 0FFh   ; call 0x3977e2
        db 0EBh, 0E0h   ; jmp 0x397825
$L_397845:
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397860
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_2   ; 0x395800
        db 0EBh, 002h   ; jmp 0x397862
$L_397860:
        db 033h, 0C0h   ; xor eax, eax
$L_397862:
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 0EBh, 0BBh   ; jmp 0x397822
$L_397867:
        db 08Bh, 0DEh   ; mov ebx, esi
$L_397869:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 0C3h   ; mov eax, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8

; // match: ?erase@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z @ 0x00397871
PUBLIC ?erase@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z
?erase@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 075h, 004h   ; jne 0x397883
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 059h   ; jmp 0x3978dc
$L_397883:
        db 057h   ; push edi
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        call ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ   ; 0x3947F0
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_3   ; 0x396DF2
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x3978ca
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x3978b0
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_3978b0:
        db 039h, 077h, 00Ch   ; cmp dword ptr [edi + 0xc], esi
        db 075h, 003h   ; jne 0x3978b8
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
$L_3978b8:
        db 039h, 077h, 010h   ; cmp dword ptr [edi + 0x10], esi
        db 075h, 003h   ; jne 0x3978c0
        db 089h, 047h, 010h   ; mov dword ptr [edi + 0x10], eax
$L_3978c0:
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 003h   ; jmp 0x3978cd
$L_3978ca:
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
$L_3978cd:
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
        db 0FFh, 04Bh, 00Ch   ; dec dword ptr [ebx + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 05Fh   ; pop edi
$L_3978dc:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4
seg32 ENDS

seg33 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?erase@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z @ 0x00397A50
PUBLIC ?erase@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z
?erase@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 008h   ; mov esi, dword ptr [ebp + 8]
        db 085h, 0F6h   ; test esi, esi
        db 08Bh, 0D9h   ; mov ebx, ecx
        db 075h, 004h   ; jne 0x397a62
        db 033h, 0C0h   ; xor eax, eax
        db 0EBh, 059h   ; jmp 0x397abb
$L_397a62:
        db 057h   ; push edi
        db 08Dh, 04Dh, 008h   ; lea ecx, [ebp + 8]
        db 089h, 075h, 008h   ; mov dword ptr [ebp + 8], esi
        call ??Econst_iterator@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEAAV0123@XZ   ; 0x3947F0
        db 0FFh, 076h, 010h   ; push dword ptr [esi + 0x10]
        db 08Bh, 07Eh, 008h   ; mov edi, dword ptr [esi + 8]
        db 0FFh, 076h, 00Ch   ; push dword ptr [esi + 0xc]
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call ?fill_hole@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEPAVnode@123@PAV4123@00@Z_4   ; 0x397043
        db 085h, 0FFh   ; test edi, edi
        db 074h, 021h   ; je 0x397aa9
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x397a8f
        db 089h, 078h, 008h   ; mov dword ptr [eax + 8], edi
$L_397a8f:
        db 039h, 077h, 00Ch   ; cmp dword ptr [edi + 0xc], esi
        db 075h, 003h   ; jne 0x397a97
        db 089h, 047h, 00Ch   ; mov dword ptr [edi + 0xc], eax
$L_397a97:
        db 039h, 077h, 010h   ; cmp dword ptr [edi + 0x10], esi
        db 075h, 003h   ; jne 0x397a9f
        db 089h, 047h, 010h   ; mov dword ptr [edi + 0x10], eax
$L_397a9f:
        db 057h   ; push edi
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 003h   ; jmp 0x397aac
$L_397aa9:
        db 089h, 043h, 008h   ; mov dword ptr [ebx + 8], eax
$L_397aac:
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 06Ah, 001h   ; push 1
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 010h   ; call dword ptr [eax]
        db 0FFh, 04Bh, 00Ch   ; dec dword ptr [ebx + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 05Fh   ; pop edi
$L_397abb:
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@PAV4123@@Z @ 0x00397AC1
PUBLIC ?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@PAV4123@@Z
?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@PAV4123@@Z:
$L_397ac1:
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 074h, 024h, 010h   ; mov esi, dword ptr [esp + 0x10]
        db 085h, 0F6h   ; test esi, esi
        db 057h   ; push edi
        db 08Bh, 0F9h   ; mov edi, ecx
        db 075h, 001h   ; jne 0x397acf
        db 0CCh   ; int3 
$L_397acf:
        db 08Bh, 046h, 004h   ; mov eax, dword ptr [esi + 4]
        db 08Bh, 05Ch, 024h, 010h   ; mov ebx, dword ptr [esp + 0x10]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 076h, 036h   ; jbe 0x397b10
        db 08Bh, 046h, 00Ch   ; mov eax, dword ptr [esi + 0xc]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 038h   ; jne 0x397b19
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397afc
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_4   ; 0x395951
        db 0EBh, 002h   ; jmp 0x397afe
$L_397afc:
        db 033h, 0C0h   ; xor eax, eax
$L_397afe:
        db 089h, 046h, 00Ch   ; mov dword ptr [esi + 0xc], eax
$L_397b01:
        db 0FFh, 047h, 00Ch   ; inc dword ptr [edi + 0xc]
$L_397b04:
        db 056h   ; push esi
        db 08Bh, 0CFh   ; mov ecx, edi
        db 08Bh, 0D8h   ; mov ebx, eax
        call ?balance@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@IAEXPAVnode@123@@Z   ; 0x396AB1
        db 0EBh, 038h   ; jmp 0x397b48
$L_397b10:
        db 073h, 034h   ; jae 0x397b46
        db 08Bh, 046h, 010h   ; mov eax, dword ptr [esi + 0x10]
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397b24
$L_397b19:
        db 050h   ; push eax
        db 053h   ; push ebx
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0E8h, 09Fh, 0FFh, 0FFh, 0FFh   ; call 0x397ac1
        db 0EBh, 0E0h   ; jmp 0x397b04
$L_397b24:
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Bh   ; je 0x397b3f
        db 056h   ; push esi
        db 053h   ; push ebx
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_4   ; 0x395951
        db 0EBh, 002h   ; jmp 0x397b41
$L_397b3f:
        db 033h, 0C0h   ; xor eax, eax
$L_397b41:
        db 089h, 046h, 010h   ; mov dword ptr [esi + 0x10], eax
        db 0EBh, 0BBh   ; jmp 0x397b01
$L_397b46:
        db 08Bh, 0DEh   ; mov ebx, esi
$L_397b48:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 08Bh, 0C3h   ; mov eax, ebx
        db 05Bh   ; pop ebx
        db 0C2h, 008h, 000h   ; ret 8
seg33 ENDS

seg34 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEXPAVGraphOptimizerObject@23@@Z @ 0x00397BC3
PUBLIC ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEXPAVGraphOptimizerObject@23@@Z
?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEXPAVGraphOptimizerObject@23@@Z:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z   ; 0x397471
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397BDB @ 0x00397BDB
PUBLIC _sub_397BDB
_sub_397BDB:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 02Dh   ; jne 0x397c12
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Fh   ; je 0x397c0b
        db 06Ah, 000h   ; push 0
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_0   ; 0x39576E
        db 0EBh, 002h   ; jmp 0x397c0d
$L_397c0b:
        db 033h, 0C0h   ; xor eax, eax
$L_397c0d:
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 0EBh, 00Ch   ; jmp 0x397c1e
$L_397c12:
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_0   ; 0x3975E2
$L_397c1e:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397C22 @ 0x00397C22
PUBLIC _sub_397C22
_sub_397C22:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_0   ; 0x397571
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@@Z @ 0x00397C3A
PUBLIC ?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@@Z
?insert@?$set@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVReader@23@@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 02Dh   ; jne 0x397c71
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Fh   ; je 0x397c6a
        db 06Ah, 000h   ; push 0
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_1   ; 0x3957B7
        db 0EBh, 002h   ; jmp 0x397c6c
$L_397c6a:
        db 033h, 0C0h   ; xor eax, eax
$L_397c6c:
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 0EBh, 00Ch   ; jmp 0x397c7d
$L_397c71:
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_1   ; 0x3976E2
$L_397c7d:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397C81 @ 0x00397C81
PUBLIC _sub_397C81
_sub_397C81:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_1   ; 0x397671
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397C99 @ 0x00397C99
PUBLIC _sub_397C99
_sub_397C99:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 02Dh   ; jne 0x397cd0
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Fh   ; je 0x397cc9
        db 06Ah, 000h   ; push 0
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_2   ; 0x395800
        db 0EBh, 002h   ; jmp 0x397ccb
$L_397cc9:
        db 033h, 0C0h   ; xor eax, eax
$L_397ccb:
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 0EBh, 00Ch   ; jmp 0x397cdc
$L_397cd0:
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_2   ; 0x3977E2
$L_397cdc:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397CE0 @ 0x00397CE0
PUBLIC _sub_397CE0
_sub_397CE0:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_2   ; 0x397771
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: ?insert@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVInstruction@23@@Z @ 0x00397CF8
PUBLIC ?insert@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVInstruction@23@@Z
?insert@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVInstruction@23@@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 02Dh   ; jne 0x397d2f
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Fh   ; je 0x397d28
        db 06Ah, 000h   ; push 0
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_3   ; 0x395908
        db 0EBh, 002h   ; jmp 0x397d2a
$L_397d28:
        db 033h, 0C0h   ; xor eax, eax
$L_397d2a:
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 0EBh, 00Ch   ; jmp 0x397d3b
$L_397d2f:
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVInstruction@23@PAV4123@@Z   ; 0x3978E2
$L_397d3b:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

seg34 ENDS

seg35 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@@Z @ 0x00397DA6
PUBLIC ?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@@Z
?insert@?$set@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVRegister@23@@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 08Bh, 046h, 008h   ; mov eax, dword ptr [esi + 8]
        db 085h, 0C0h   ; test eax, eax
        db 075h, 02Dh   ; jne 0x397ddd
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 06Ah, 018h   ; push 0x18
        db 0C7h, 046h, 00Ch, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0xc], 1
        call _XMemAlloc@8   ; 0x22FC99
        db 085h, 0C0h   ; test eax, eax
        db 074h, 00Fh   ; je 0x397dd6
        db 06Ah, 000h   ; push 0
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0C8h   ; mov ecx, eax
        call ??0node@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@PAVGraphOptimizerObject@23@PAV0123@@Z_4   ; 0x395951
        db 0EBh, 002h   ; jmp 0x397dd8
$L_397dd6:
        db 033h, 0C0h   ; xor eax, eax
$L_397dd8:
        db 089h, 046h, 008h   ; mov dword ptr [esi + 8], eax
        db 0EBh, 00Ch   ; jmp 0x397de9
$L_397ddd:
        db 050h   ; push eax
        db 0FFh, 074h, 024h, 00Ch   ; push dword ptr [esp + 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@PAV4123@@Z_3   ; 0x397AC1
$L_397de9:
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_397DED @ 0x00397DED
PUBLIC _sub_397DED
_sub_397DED:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_4   ; 0x397A50
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg35 ENDS

seg36 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??0GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@XZ @ 0x00397E24
PUBLIC ??0GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@XZ
??0GraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAE@XZ:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 056h   ; push esi
        db 0B9h   ; mov ecx, 0x3aa298
        dd _unk_3AA298
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa48
        dd _unk_41AA48
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z   ; 0x397B7C
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C3h   ; ret 

; // match: _sub_397E3C @ 0x00397E3C
PUBLIC _sub_397E3C
_sub_397E3C:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41aa48
        dd _unk_41AA48
        db 051h   ; push ecx
        db 0B9h   ; mov ecx, 0x3aa298
        dd _unk_3AA298
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEXPAVGraphOptimizerObject@23@@Z   ; 0x397BC3
        db 0C3h   ; ret 
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 056h   ; push esi
        db 0B9h   ; mov ecx, 0x3aa298
        dd _unk_3AA298
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa48
        dd _unk_41AA48
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEXPAVGraphOptimizerObject@23@@Z   ; 0x397BC3
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Bh   ; je 0x397e74
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_397e74:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg36 ENDS

seg37 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?erase@?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXH@Z @ 0x00398BFB
PUBLIC ?erase@?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXH@Z
?erase@?$map@HPAVRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEXH@Z:
        db 056h   ; push esi
        db 0FFh, 074h, 024h, 008h   ; push dword ptr [esp + 8]
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_396039   ; 0x396039
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_397990   ; 0x397990
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg37 ENDS

seg38 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_GInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00398D1E
PUBLIC ??_GInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_GInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_398259   ; 0x398259
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x398d3c
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x398d3c
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_398d3c:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg38 ENDS

seg40 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_GInstructionGraph@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00399404
PUBLIC ??_GInstructionGraph@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_GInstructionGraph@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call ??1InstructionGraph@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ   ; 0x398B8F
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x399422
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x399422
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_399422:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg40 ENDS

seg41 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_GReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x00399506
PUBLIC ??_GReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_GReader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call ??1Reader@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAE@XZ   ; 0x399102
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x399524
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x399524
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_399524:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg41 ENDS

seg42 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??_GRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z @ 0x003995CE
PUBLIC ??_GRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z
??_GRegister@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UAEPAXI@Z:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_398D42   ; 0x398D42
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x3995ec
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x3995ec
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3995ec:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
seg42 ENDS

seg43 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_39C068 @ 0x0039C068
PUBLIC _sub_39C068
_sub_39C068:
        db 0B8h   ; mov eax, 0x3094ae
        dd _sub_3094AE
        call __EH_prolog   ; 0x2C9200
        db 083h, 0ECh, 030h   ; sub esp, 0x30
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 089h, 04Dh, 0ECh   ; mov dword ptr [ebp - 0x14], ecx
        db 0C7h, 045h, 0C4h   ; mov dword ptr [ebp - 0x3c], 0x41aa10
        dd _unk_41AA10
        db 089h, 05Dh, 0CCh   ; mov dword ptr [ebp - 0x34], ebx
        db 089h, 05Dh, 0D0h   ; mov dword ptr [ebp - 0x30], ebx
        db 089h, 05Dh, 0FCh   ; mov dword ptr [ebp - 4], ebx
        db 0C7h, 045h, 0D4h   ; mov dword ptr [ebp - 0x2c], 0x41a9dc
        dd _unk_41A9DC
        db 089h, 05Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ebx
        db 089h, 05Dh, 0E0h   ; mov dword ptr [ebp - 0x20], ebx
        db 08Dh, 045h, 0C4h   ; lea eax, [ebp - 0x3c]
        db 0BFh   ; mov edi, 0x3aa2b8
        dd _unk_3AA2B8
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0C6h, 045h, 0FCh, 001h   ; mov byte ptr [ebp - 4], 1
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_2   ; 0x397C99
        db 08Dh, 045h, 0D4h   ; lea eax, [ebp - 0x2c]
        db 0BEh   ; mov esi, 0x3aa2a8
        dd _unk_3AA2A8
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_0   ; 0x397BDB
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 081h, 0C1h, 088h, 000h, 000h, 000h   ; add ecx, 0x88
        call _sub_395661   ; 0x395661
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 089h, 045h, 0E8h   ; mov dword ptr [ebp - 0x18], eax
        db 0EBh, 053h   ; jmp 0x39c12a
$L_39c0d7:
        db 08Bh, 040h, 004h   ; mov eax, dword ptr [eax + 4]
        db 050h   ; push eax
        db 08Dh, 04Dh, 0C4h   ; lea ecx, [ebp - 0x3c]
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_3   ; 0x397CF8
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 040h, 034h   ; mov eax, dword ptr [eax + 0x34]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 009h   ; je 0x39c0f9
        db 050h   ; push eax
        db 08Dh, 04Dh, 0D4h   ; lea ecx, [ebp - 0x2c]
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_4   ; 0x397DA6
$L_39c0f9:
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 040h, 038h   ; mov eax, dword ptr [eax + 0x38]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 009h   ; je 0x39c10c
        db 050h   ; push eax
        db 08Dh, 04Dh, 0D4h   ; lea ecx, [ebp - 0x2c]
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_4   ; 0x397DA6
$L_39c10c:
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 08Bh, 040h, 03Ch   ; mov eax, dword ptr [eax + 0x3c]
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 074h, 009h   ; je 0x39c11f
        db 050h   ; push eax
        db 08Dh, 04Dh, 0D4h   ; lea ecx, [ebp - 0x2c]
        call ?insert@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAVGraphOptimizerObject@23@@Z_4   ; 0x397DA6
$L_39c11f:
        db 08Dh, 04Dh, 0E8h   ; lea ecx, [ebp - 0x18]
        call _sub_394631   ; 0x394631
        db 08Bh, 045h, 0E8h   ; mov eax, dword ptr [ebp - 0x18]
$L_39c12a:
        db 03Bh, 0C3h   ; cmp eax, ebx
        db 075h, 0A9h   ; jne 0x39c0d7
$L_39c12e:
        db 039h, 05Dh, 0E0h   ; cmp dword ptr [ebp - 0x20], ebx
        db 075h, 005h   ; jne 0x39c138
        db 039h, 05Dh, 0D0h   ; cmp dword ptr [ebp - 0x30], ebx
        db 074h, 022h   ; je 0x39c15a
$L_39c138:
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Dh, 045h, 0C4h   ; lea eax, [ebp - 0x3c]
        db 050h   ; push eax
        db 08Dh, 045h, 0D4h   ; lea eax, [ebp - 0x2c]
        db 050h   ; push eax
        call _sub_39B389   ; 0x39B389
        db 08Bh, 04Dh, 0ECh   ; mov ecx, dword ptr [ebp - 0x14]
        db 08Dh, 045h, 0C4h   ; lea eax, [ebp - 0x3c]
        db 050h   ; push eax
        db 08Dh, 045h, 0D4h   ; lea eax, [ebp - 0x2c]
        db 050h   ; push eax
        call _sub_39B0CF   ; 0x39B0CF
        db 0EBh, 0D4h   ; jmp 0x39c12e
$L_39c15a:
        db 08Dh, 045h, 0C4h   ; lea eax, [ebp - 0x3c]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_2   ; 0x397771
        db 08Dh, 045h, 0D4h   ; lea eax, [ebp - 0x2c]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_397E05   ; 0x397E05
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?erase@?$set@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@U?$less@PAVGraphOptimizerObject@VS_GRAPH_OPTIMIZER@XGRAPHICS@@@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@QAEPAVnode@123@PAV4123@@Z_0   ; 0x397571
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        db 088h, 05Dh, 0FCh   ; mov byte ptr [ebp - 4], bl
        db 0C7h, 045h, 0D4h   ; mov dword ptr [ebp - 0x2c], 0x41a9dc
        dd _unk_41A9DC
        call _sub_394856   ; 0x394856
        db 0FFh, 075h, 0CCh   ; push dword ptr [ebp - 0x34]
        db 083h, 04Dh, 0FCh, 0FFh   ; or dword ptr [ebp - 4], 0xffffffff
        db 089h, 05Dh, 0DCh   ; mov dword ptr [ebp - 0x24], ebx
        db 089h, 05Dh, 0E0h   ; mov dword ptr [ebp - 0x20], ebx
        db 0C7h, 045h, 0C4h   ; mov dword ptr [ebp - 0x3c], 0x41aa10
        dd _unk_41AA10
        call ?clear_node@?$set@PAVInstruction@VS_GRAPH_OPTIMIZER@XGRAPHICS@@UInstructionLess@23@@VS_GRAPH_OPTIMIZER@XGRAPHICS@@SGXPAVnode@123@@Z   ; 0x39482D
        db 08Bh, 04Dh, 0F4h   ; mov ecx, dword ptr [ebp - 0xc]
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 064h, 089h, 00Dh, 000h, 000h, 000h, 000h   ; mov dword ptr fs:[0], ecx
        db 0C9h   ; leave 
        db 0C3h   ; ret 
seg43 ENDS



seg46 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?InstructionLRP@XGRAPHICS@@YGXKKPAK00000@Z @ 0x0039D4FF
PUBLIC ?InstructionLRP@XGRAPHICS@@YGXKKPAK00000@Z
?InstructionLRP@XGRAPHICS@@YGXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 083h, 0F8h, 020h   ; cmp eax, 0x20
        db 074h, 007h   ; je 0x39d513
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x39d513
        db 083h, 021h, 000h   ; and dword ptr [ecx], 0
$L_39d513:
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 053h   ; push ebx
        db 056h   ; push esi
        db 08Bh, 075h, 01Ch   ; mov esi, dword ptr [ebp + 0x1c]
        db 057h   ; push edi
        db 0FFh, 036h   ; push dword ptr [esi]
        db 00Fh, 085h, 081h, 000h, 000h, 000h   ; jne 0x39d5a6
        call _sub_39D085   ; 0x39D085
        db 0FFh, 076h, 004h   ; push dword ptr [esi + 4]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 08Bh, 0D8h   ; mov ebx, eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 038h   ; mov edi, dword ptr [eax]
        db 089h, 07Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], edi
        call _sub_39D085   ; 0x39D085
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 00Bh, 0FBh   ; or edi, ebx
        db 00Bh, 0FAh   ; or edi, edx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0C7h   ; or eax, edi
        db 08Bh, 07Dh, 018h   ; mov edi, dword ptr [ebp + 0x18]
        db 00Bh, 047h, 004h   ; or eax, dword ptr [edi + 4]
        db 00Bh, 041h, 004h   ; or eax, dword ptr [ecx + 4]
        db 0C1h, 0E0h, 008h   ; shl eax, 8
        db 08Bh, 0F0h   ; mov esi, eax
        call _sub_39D085   ; 0x39D085
        db 00Bh, 0F0h   ; or esi, eax
        db 00Bh, 077h, 008h   ; or esi, dword ptr [edi + 8]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 071h, 008h   ; or esi, dword ptr [ecx + 8]
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E6h, 008h   ; shl esi, 8
        db 0C1h, 0EAh, 005h   ; shr edx, 5
        db 00Bh, 034h, 095h   ; or esi, dword ptr [edx*4 + 0x437a58]
        dd _unk_437A58
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 00Bh, 075h, 01Ch   ; or esi, dword ptr [ebp + 0x1c]
        db 00Bh, 0F3h   ; or esi, ebx
        db 089h, 0B4h, 081h, 088h, 000h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x88], esi
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 00Bh, 00Ah   ; or ecx, dword ptr [edx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 089h, 08Ch, 082h, 0B4h, 000h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0xb4], ecx
        db 0EBh, 079h   ; jmp 0x39d61f
$L_39d5a6:
        call _sub_39D099   ; 0x39D099
        db 0FFh, 076h, 004h   ; push dword ptr [esi + 4]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 089h, 045h, 01Ch   ; mov dword ptr [ebp + 0x1c], eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        call _sub_39D099   ; 0x39D099
        db 08Bh, 07Dh, 01Ch   ; mov edi, dword ptr [ebp + 0x1c]
        db 0FFh, 076h, 008h   ; push dword ptr [esi + 8]
        db 00Bh, 0FBh   ; or edi, ebx
        db 00Bh, 0FAh   ; or edi, edx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 0C7h   ; or eax, edi
        db 08Bh, 07Dh, 018h   ; mov edi, dword ptr [ebp + 0x18]
        db 00Bh, 047h, 004h   ; or eax, dword ptr [edi + 4]
        db 00Bh, 041h, 004h   ; or eax, dword ptr [ecx + 4]
        db 0C1h, 0E0h, 008h   ; shl eax, 8
        db 08Bh, 0F0h   ; mov esi, eax
        call _sub_39D099   ; 0x39D099
        db 00Bh, 0F0h   ; or esi, eax
        db 00Bh, 077h, 008h   ; or esi, dword ptr [edi + 8]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 071h, 008h   ; or esi, dword ptr [ecx + 8]
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E6h, 008h   ; shl esi, 8
        db 0C1h, 0EAh, 005h   ; shr edx, 5
        db 00Bh, 034h, 095h   ; or esi, dword ptr [edx*4 + 0x437a58]
        dd _unk_437A58
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 00Bh, 075h, 01Ch   ; or esi, dword ptr [ebp + 0x1c]
        db 00Bh, 0F3h   ; or esi, ebx
        db 089h, 034h, 081h   ; mov dword ptr [ecx + eax*4], esi
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 00Bh, 00Ah   ; or ecx, dword ptr [edx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 089h, 04Ch, 082h, 068h   ; mov dword ptr [edx + eax*4 + 0x68], ecx
$L_39d61f:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 020h, 000h   ; ret 0x20
seg46 ENDS

seg62 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?InstructionCND@XGRAPHICS@@YGXKKPAK00000@Z @ 0x0039D626
PUBLIC ?InstructionCND@XGRAPHICS@@YGXKKPAK00000@Z
?InstructionCND@XGRAPHICS@@YGXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 083h, 07Dh, 00Ch, 000h   ; cmp dword ptr [ebp + 0xc], 0
        db 08Bh, 04Dh, 01Ch   ; mov ecx, dword ptr [ebp + 0x1c]
        db 056h   ; push esi
        db 057h   ; push edi
        db 0FFh, 071h, 008h   ; push dword ptr [ecx + 8]
        db 075h, 061h   ; jne 0x39d698
        call _sub_39D085   ; 0x39D085
        db 08Bh, 055h, 018h   ; mov edx, dword ptr [ebp + 0x18]
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 0FFh, 071h, 004h   ; push dword ptr [ecx + 4]
        db 08Bh, 0F8h   ; mov edi, eax
        db 00Bh, 07Ah, 008h   ; or edi, dword ptr [edx + 8]
        db 00Bh, 07Eh, 008h   ; or edi, dword ptr [esi + 8]
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        call _sub_39D085   ; 0x39D085
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 00Bh, 0F8h   ; or edi, eax
        db 00Bh, 07Ah, 004h   ; or edi, dword ptr [edx + 4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 07Eh, 004h   ; or edi, dword ptr [esi + 4]
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0CFh, 020h, 000h, 020h, 000h   ; or edi, 0x200020
        db 089h, 0BCh, 081h, 088h, 000h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x88], edi
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0C9h, 004h   ; or ecx, 4
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 00Bh, 00Ah   ; or ecx, dword ptr [edx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 089h, 08Ch, 082h, 0B4h, 000h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0xb4], ecx
        db 0EBh, 058h   ; jmp 0x39d6f0
$L_39d698:
        call _sub_39D099   ; 0x39D099
        db 08Bh, 055h, 018h   ; mov edx, dword ptr [ebp + 0x18]
        db 08Bh, 075h, 020h   ; mov esi, dword ptr [ebp + 0x20]
        db 0FFh, 071h, 004h   ; push dword ptr [ecx + 4]
        db 08Bh, 0F8h   ; mov edi, eax
        db 00Bh, 07Ah, 008h   ; or edi, dword ptr [edx + 8]
        db 00Bh, 07Eh, 008h   ; or edi, dword ptr [esi + 8]
        db 0C1h, 0E7h, 010h   ; shl edi, 0x10
        call _sub_39D099   ; 0x39D099
        db 08Bh, 00Dh   ; mov ecx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 00Bh, 0F8h   ; or edi, eax
        db 00Bh, 07Ah, 004h   ; or edi, dword ptr [edx + 4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 07Eh, 004h   ; or edi, dword ptr [esi + 4]
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 081h, 0CFh   ; or edi, 0x300030
        dd _loc_300030
        db 089h, 03Ch, 081h   ; mov dword ptr [ecx + eax*4], edi
        db 08Bh, 04Dh, 010h   ; mov ecx, dword ptr [ebp + 0x10]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0C9h, 004h   ; or ecx, 4
        db 0C1h, 0E1h, 004h   ; shl ecx, 4
        db 00Bh, 00Ah   ; or ecx, dword ptr [edx]
        db 08Bh, 015h   ; mov edx, dword ptr [0x3aa35c]
        dd _unk_3AA35C
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 089h, 04Ch, 082h, 068h   ; mov dword ptr [edx + eax*4 + 0x68], ecx
$L_39d6f0:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Dh   ; pop ebp
        db 0C2h, 020h, 000h   ; ret 0x20
seg62 ENDS


seg48 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?InstructionLRP@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F334
PUBLIC ?InstructionLRP@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionLRP@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 083h, 0F8h, 020h   ; cmp eax, 0x20
        db 074h, 007h   ; je 0x39f34c
        db 085h, 0C0h   ; test eax, eax
        db 074h, 003h   ; je 0x39f34c
        db 083h, 021h, 000h   ; and dword ptr [ecx], 0
$L_39f34c:
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 00Fh, 085h, 0A0h, 000h, 000h, 000h   ; jne 0x39f3fa
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 08Bh, 032h   ; mov esi, dword ptr [edx]
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 03Bh, 0F0h   ; cmp esi, eax
        db 06Ah, 010h   ; push 0x10
        db 05Fh   ; pop edi
        db 075h, 002h   ; jne 0x39f36d
        db 08Bh, 0DFh   ; mov ebx, edi
$L_39f36d:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 075h, 005h   ; jne 0x39f377
        db 089h, 07Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], edi
        db 0EBh, 004h   ; jmp 0x39f37b
$L_39f377:
        db 083h, 065h, 01Ch, 000h   ; and dword ptr [ebp + 0x1c], 0
$L_39f37b:
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 075h, 005h   ; jne 0x39f385
        db 089h, 07Dh, 020h   ; mov dword ptr [ebp + 0x20], edi
        db 0EBh, 004h   ; jmp 0x39f389
$L_39f385:
        db 083h, 065h, 020h, 000h   ; and dword ptr [ebp + 0x20], 0
$L_39f389:
        db 03Bh, 0F0h   ; cmp esi, eax
        db 075h, 005h   ; jne 0x39f392
        db 089h, 07Dh, 00Ch   ; mov dword ptr [ebp + 0xc], edi
        db 0EBh, 004h   ; jmp 0x39f396
$L_39f392:
        db 083h, 065h, 00Ch, 000h   ; and dword ptr [ebp + 0xc], 0
$L_39f396:
        db 08Bh, 055h, 018h   ; mov edx, dword ptr [ebp + 0x18]
        db 08Bh, 032h   ; mov esi, dword ptr [edx]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 08Bh, 0FEh   ; mov edi, esi
        db 00Bh, 0F8h   ; or edi, eax
        db 00Bh, 0FBh   ; or edi, ebx
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 07Ah, 004h   ; or edi, dword ptr [edx + 4]
        db 0C1h, 0E8h, 005h   ; shr eax, 5
        db 00Bh, 079h, 004h   ; or edi, dword ptr [ecx + 4]
        db 00Bh, 07Dh, 01Ch   ; or edi, dword ptr [ebp + 0x1c]
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 07Ah, 008h   ; or edi, dword ptr [edx + 8]
        db 00Bh, 079h, 008h   ; or edi, dword ptr [ecx + 8]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 00Bh, 07Dh, 020h   ; or edi, dword ptr [ebp + 0x20]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 0C1h, 0E7h, 008h   ; shl edi, 8
        db 00Bh, 03Ch, 085h   ; or edi, dword ptr [eax*4 + 0x3a9020]
        dd _unk_3A9020
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 0FEh   ; or edi, esi
        db 00Bh, 07Dh, 00Ch   ; or edi, dword ptr [ebp + 0xc]
        db 08Bh, 075h, 014h   ; mov esi, dword ptr [ebp + 0x14]
        db 089h, 0BCh, 082h, 008h, 002h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0x208], edi
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 0C1h, 0E2h, 004h   ; shl edx, 4
        db 00Bh, 016h   ; or edx, dword ptr [esi]
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 089h, 094h, 081h, 094h, 002h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x294], edx
        db 0E9h, 0A8h, 000h, 000h, 000h   ; jmp 0x39f4a2
$L_39f3fa:
        db 08Bh, 075h, 01Ch   ; mov esi, dword ptr [ebp + 0x1c]
        db 08Bh, 006h   ; mov eax, dword ptr [esi]
        db 08Bh, 056h, 004h   ; mov edx, dword ptr [esi + 4]
        db 08Bh, 076h, 008h   ; mov esi, dword ptr [esi + 8]
        db 025h, 000h, 000h, 0C0h, 000h   ; and eax, 0xc00000
        db 08Bh, 0F8h   ; mov edi, eax
        db 0BBh, 000h, 000h, 080h, 000h   ; mov ebx, 0x800000
        db 02Bh, 0FBh   ; sub edi, ebx
        db 0F7h, 0DFh   ; neg edi
        db 01Bh, 0FFh   ; sbb edi, edi
        db 081h, 0E2h, 000h, 000h, 0C0h, 000h   ; and edx, 0xc00000
        db 02Bh, 0D3h   ; sub edx, ebx
        db 083h, 0E7h, 010h   ; and edi, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 081h, 0E6h, 000h, 000h, 0C0h, 000h   ; and esi, 0xc00000
        db 02Bh, 0F3h   ; sub esi, ebx
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 0F7h, 0DEh   ; neg esi
        db 01Bh, 0F6h   ; sbb esi, esi
        db 02Bh, 0C3h   ; sub eax, ebx
        db 083h, 0E6h, 010h   ; and esi, 0x10
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 089h, 045h, 020h   ; mov dword ptr [ebp + 0x20], eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 089h, 05Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], ebx
        db 00Bh, 0D8h   ; or ebx, eax
        db 00Bh, 0DFh   ; or ebx, edi
        db 08Bh, 07Dh, 018h   ; mov edi, dword ptr [ebp + 0x18]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Fh, 004h   ; or ebx, dword ptr [edi + 4]
        db 0C1h, 0E8h, 005h   ; shr eax, 5
        db 00Bh, 059h, 004h   ; or ebx, dword ptr [ecx + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 05Fh, 008h   ; or ebx, dword ptr [edi + 8]
        db 00Bh, 059h, 008h   ; or ebx, dword ptr [ecx + 8]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 00Bh, 0DEh   ; or ebx, esi
        db 08Bh, 075h, 014h   ; mov esi, dword ptr [ebp + 0x14]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 01Ch, 085h   ; or ebx, dword ptr [eax*4 + 0x3a9020]
        dd _unk_3A9020
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 05Dh, 01Ch   ; or ebx, dword ptr [ebp + 0x1c]
        db 00Bh, 05Dh, 020h   ; or ebx, dword ptr [ebp + 0x20]
        db 089h, 01Ch, 082h   ; mov dword ptr [edx + eax*4], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 0C1h, 0E2h, 004h   ; shl edx, 4
        db 00Bh, 016h   ; or edx, dword ptr [esi]
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 089h, 094h, 081h, 088h, 001h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x188], edx
$L_39f4a2:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 020h, 000h   ; ret 0x20
seg48 ENDS

seg63 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?InstructionCND@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F4A9
PUBLIC ?InstructionCND@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionCND@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 053h   ; push ebx
        db 056h   ; push esi
        db 033h, 0F6h   ; xor esi, esi
        db 039h, 075h, 00Ch   ; cmp dword ptr [ebp + 0xc], esi
        db 057h   ; push edi
        db 075h, 065h   ; jne 0x39f51e
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 075h, 005h   ; jne 0x39f4c8
        db 06Ah, 010h   ; push 0x10
        db 05Fh   ; pop edi
        db 0EBh, 002h   ; jmp 0x39f4ca
$L_39f4c8:
        db 033h, 0FFh   ; xor edi, edi
$L_39f4ca:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 075h, 003h   ; jne 0x39f4d2
        db 06Ah, 010h   ; push 0x10
        db 05Eh   ; pop esi
$L_39f4d2:
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 058h, 008h   ; mov ebx, dword ptr [eax + 8]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 00Bh, 05Ah, 008h   ; or ebx, dword ptr [edx + 8]
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 010h   ; shl ebx, 0x10
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 05Ah, 004h   ; or ebx, dword ptr [edx + 4]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 00Bh, 0DEh   ; or ebx, esi
        db 08Bh, 075h, 014h   ; mov esi, dword ptr [ebp + 0x14]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 081h, 0CBh, 020h, 000h, 020h, 000h   ; or ebx, 0x200020
        db 089h, 09Ch, 082h, 008h, 002h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0x208], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0CAh, 004h   ; or edx, 4
        db 0C1h, 0E2h, 004h   ; shl edx, 4
        db 00Bh, 016h   ; or edx, dword ptr [esi]
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 089h, 094h, 081h, 094h, 002h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x294], edx
        db 0EBh, 06Ch   ; jmp 0x39f58a
$L_39f51e:
        db 08Bh, 042h, 008h   ; mov eax, dword ptr [edx + 8]
        db 08Bh, 052h, 004h   ; mov edx, dword ptr [edx + 4]
        db 0BFh, 000h, 000h, 0C0h, 000h   ; mov edi, 0xc00000
        db 023h, 0C7h   ; and eax, edi
        db 0BEh, 000h, 000h, 080h, 000h   ; mov esi, 0x800000
        db 02Bh, 0C6h   ; sub eax, esi
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 023h, 0D7h   ; and edx, edi
        db 08Bh, 07Dh, 020h   ; mov edi, dword ptr [ebp + 0x20]
        db 02Bh, 0D6h   ; sub edx, esi
        db 08Bh, 075h, 018h   ; mov esi, dword ptr [ebp + 0x18]
        db 08Bh, 05Eh, 008h   ; mov ebx, dword ptr [esi + 8]
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 00Bh, 05Fh, 008h   ; or ebx, dword ptr [edi + 8]
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 00Bh, 0D8h   ; or ebx, eax
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 0C1h, 0E3h, 010h   ; shl ebx, 0x10
        db 00Bh, 05Eh, 004h   ; or ebx, dword ptr [esi + 4]
        db 08Bh, 075h, 014h   ; mov esi, dword ptr [ebp + 0x14]
        db 00Bh, 05Fh, 004h   ; or ebx, dword ptr [edi + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 081h, 0CBh   ; or ebx, 0x300030
        dd _loc_300030
        db 089h, 01Ch, 082h   ; mov dword ptr [edx + eax*4], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0CAh, 004h   ; or edx, 4
        db 0C1h, 0E2h, 004h   ; shl edx, 4
        db 00Bh, 016h   ; or edx, dword ptr [esi]
        db 0C1h, 0E2h, 008h   ; shl edx, 8
        db 089h, 094h, 081h, 088h, 001h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x188], edx
$L_39f58a:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 05Dh   ; pop ebp
        db 0C2h, 020h, 000h   ; ret 0x20
; // match: ?InstructionXMMA@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F591
PUBLIC ?InstructionXMMA@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionXMMA@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 00Fh, 085h, 094h, 000h, 000h, 000h   ; jne 0x39f63a
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 039h, 002h   ; cmp dword ptr [edx], eax
        db 06Ah, 010h   ; push 0x10
        db 05Eh   ; pop esi
        db 075h, 004h   ; jne 0x39f5b9
        db 08Bh, 0FEh   ; mov edi, esi
        db 0EBh, 002h   ; jmp 0x39f5bb
$L_39f5b9:
        db 033h, 0FFh   ; xor edi, edi
$L_39f5bb:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 089h, 075h, 01Ch   ; mov dword ptr [ebp + 0x1c], esi
        db 074h, 003h   ; je 0x39f5c6
        db 089h, 05Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], ebx
$L_39f5c6:
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 089h, 075h, 00Ch   ; mov dword ptr [ebp + 0xc], esi
        db 074h, 003h   ; je 0x39f5d1
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
$L_39f5d1:
        db 039h, 042h, 00Ch   ; cmp dword ptr [edx + 0xc], eax
        db 074h, 002h   ; je 0x39f5d8
        db 033h, 0F6h   ; xor esi, esi
$L_39f5d8:
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 00Bh, 01Ah   ; or ebx, dword ptr [edx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 05Ah, 004h   ; or ebx, dword ptr [edx + 4]
        db 00Bh, 05Dh, 01Ch   ; or ebx, dword ptr [ebp + 0x1c]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 05Ah, 008h   ; or ebx, dword ptr [edx + 8]
        db 00Bh, 05Dh, 00Ch   ; or ebx, dword ptr [ebp + 0xc]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 00Bh, 05Ah, 00Ch   ; or ebx, dword ptr [edx + 0xc]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 089h, 09Ch, 090h, 008h, 002h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x208], ebx
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 008h   ; or esi, dword ptr [eax + 8]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 030h   ; or esi, dword ptr [eax]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 004h   ; or esi, dword ptr [eax + 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 089h, 0B4h, 090h, 094h, 002h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x294], esi
        db 0E9h, 0A1h, 000h, 000h, 000h   ; jmp 0x39f6db
$L_39f63a:
        db 08Bh, 07Dh, 01Ch   ; mov edi, dword ptr [ebp + 0x1c]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 057h, 004h   ; mov edx, dword ptr [edi + 4]
        db 08Bh, 077h, 008h   ; mov esi, dword ptr [edi + 8]
        db 08Bh, 07Fh, 00Ch   ; mov edi, dword ptr [edi + 0xc]
        db 0BBh, 000h, 000h, 0C0h, 000h   ; mov ebx, 0xc00000
        db 023h, 0C3h   ; and eax, ebx
        db 0B9h, 000h, 000h, 080h, 000h   ; mov ecx, 0x800000
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 023h, 0D3h   ; and edx, ebx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 023h, 0F3h   ; and esi, ebx
        db 02Bh, 0F1h   ; sub esi, ecx
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 0F7h, 0DEh   ; neg esi
        db 01Bh, 0F6h   ; sbb esi, esi
        db 023h, 0FBh   ; and edi, ebx
        db 083h, 0E6h, 010h   ; and esi, 0x10
        db 02Bh, 0F9h   ; sub edi, ecx
        db 08Bh, 04Dh, 018h   ; mov ecx, dword ptr [ebp + 0x18]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 0F7h, 0DFh   ; neg edi
        db 01Bh, 0FFh   ; sbb edi, edi
        db 00Bh, 019h   ; or ebx, dword ptr [ecx]
        db 083h, 0E7h, 010h   ; and edi, 0x10
        db 00Bh, 0D8h   ; or ebx, eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 059h, 004h   ; or ebx, dword ptr [ecx + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 059h, 008h   ; or ebx, dword ptr [ecx + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 00Bh, 059h, 00Ch   ; or ebx, dword ptr [ecx + 0xc]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 089h, 01Ch, 090h   ; mov dword ptr [eax + edx*4], ebx
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 008h   ; or esi, dword ptr [eax + 8]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 030h   ; or esi, dword ptr [eax]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 004h   ; or esi, dword ptr [eax + 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 089h, 0B4h, 090h, 088h, 001h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x188], esi
$L_39f6db:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 020h, 000h   ; ret 0x20
; // match: ?InstructionXMMC@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F6E2
PUBLIC ?InstructionXMMC@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionXMMC@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 00Fh, 085h, 097h, 000h, 000h, 000h   ; jne 0x39f78e
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 039h, 002h   ; cmp dword ptr [edx], eax
        db 06Ah, 010h   ; push 0x10
        db 05Eh   ; pop esi
        db 075h, 004h   ; jne 0x39f70a
        db 08Bh, 0FEh   ; mov edi, esi
        db 0EBh, 002h   ; jmp 0x39f70c
$L_39f70a:
        db 033h, 0FFh   ; xor edi, edi
$L_39f70c:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 089h, 075h, 01Ch   ; mov dword ptr [ebp + 0x1c], esi
        db 074h, 003h   ; je 0x39f717
        db 089h, 05Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], ebx
$L_39f717:
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 089h, 075h, 00Ch   ; mov dword ptr [ebp + 0xc], esi
        db 074h, 003h   ; je 0x39f722
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
$L_39f722:
        db 039h, 042h, 00Ch   ; cmp dword ptr [edx + 0xc], eax
        db 074h, 002h   ; je 0x39f729
        db 033h, 0F6h   ; xor esi, esi
$L_39f729:
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 00Bh, 01Ah   ; or ebx, dword ptr [edx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 05Ah, 004h   ; or ebx, dword ptr [edx + 4]
        db 00Bh, 05Dh, 01Ch   ; or ebx, dword ptr [ebp + 0x1c]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 05Ah, 008h   ; or ebx, dword ptr [edx + 8]
        db 00Bh, 05Dh, 00Ch   ; or ebx, dword ptr [ebp + 0xc]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 00Bh, 05Ah, 00Ch   ; or ebx, dword ptr [edx + 0xc]
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 089h, 09Ch, 090h, 008h, 002h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x208], ebx
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 083h, 0CEh, 004h   ; or esi, 4
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 008h   ; or esi, dword ptr [eax + 8]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 030h   ; or esi, dword ptr [eax]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 004h   ; or esi, dword ptr [eax + 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 089h, 0B4h, 090h, 094h, 002h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x294], esi
        db 0E9h, 0A4h, 000h, 000h, 000h   ; jmp 0x39f832
$L_39f78e:
        db 08Bh, 07Dh, 01Ch   ; mov edi, dword ptr [ebp + 0x1c]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 057h, 004h   ; mov edx, dword ptr [edi + 4]
        db 08Bh, 077h, 008h   ; mov esi, dword ptr [edi + 8]
        db 08Bh, 07Fh, 00Ch   ; mov edi, dword ptr [edi + 0xc]
        db 0BBh, 000h, 000h, 0C0h, 000h   ; mov ebx, 0xc00000
        db 023h, 0C3h   ; and eax, ebx
        db 0B9h, 000h, 000h, 080h, 000h   ; mov ecx, 0x800000
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 023h, 0D3h   ; and edx, ebx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 023h, 0F3h   ; and esi, ebx
        db 02Bh, 0F1h   ; sub esi, ecx
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 0F7h, 0DEh   ; neg esi
        db 01Bh, 0F6h   ; sbb esi, esi
        db 023h, 0FBh   ; and edi, ebx
        db 083h, 0E6h, 010h   ; and esi, 0x10
        db 02Bh, 0F9h   ; sub edi, ecx
        db 08Bh, 04Dh, 018h   ; mov ecx, dword ptr [ebp + 0x18]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 0F7h, 0DFh   ; neg edi
        db 01Bh, 0FFh   ; sbb edi, edi
        db 00Bh, 019h   ; or ebx, dword ptr [ecx]
        db 083h, 0E7h, 010h   ; and edi, 0x10
        db 00Bh, 0D8h   ; or ebx, eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 059h, 004h   ; or ebx, dword ptr [ecx + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 08Bh, 055h, 008h   ; mov edx, dword ptr [ebp + 8]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 059h, 008h   ; or ebx, dword ptr [ecx + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 00Bh, 059h, 00Ch   ; or ebx, dword ptr [ecx + 0xc]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 089h, 01Ch, 090h   ; mov dword ptr [eax + edx*4], ebx
        db 08Bh, 045h, 010h   ; mov eax, dword ptr [ebp + 0x10]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 08Bh, 045h, 014h   ; mov eax, dword ptr [ebp + 0x14]
        db 083h, 0CEh, 004h   ; or esi, 4
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 008h   ; or esi, dword ptr [eax + 8]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 030h   ; or esi, dword ptr [eax]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 070h, 004h   ; or esi, dword ptr [eax + 4]
        db 08Bh, 001h   ; mov eax, dword ptr [ecx]
        db 089h, 0B4h, 090h, 088h, 001h, 000h, 000h   ; mov dword ptr [eax + edx*4 + 0x188], esi
$L_39f832:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 020h, 000h   ; ret 0x20
; // match: ?InstructionXDM@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F839
PUBLIC ?InstructionXDM@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionXDM@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 00Fh, 085h, 091h, 000h, 000h, 000h   ; jne 0x39f8df
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 039h, 002h   ; cmp dword ptr [edx], eax
        db 06Ah, 010h   ; push 0x10
        db 05Eh   ; pop esi
        db 075h, 004h   ; jne 0x39f861
        db 08Bh, 0FEh   ; mov edi, esi
        db 0EBh, 002h   ; jmp 0x39f863
$L_39f861:
        db 033h, 0FFh   ; xor edi, edi
$L_39f863:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 089h, 075h, 01Ch   ; mov dword ptr [ebp + 0x1c], esi
        db 074h, 003h   ; je 0x39f86e
        db 089h, 05Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], ebx
$L_39f86e:
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 089h, 075h, 00Ch   ; mov dword ptr [ebp + 0xc], esi
        db 074h, 003h   ; je 0x39f879
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
$L_39f879:
        db 039h, 042h, 00Ch   ; cmp dword ptr [edx + 0xc], eax
        db 074h, 002h   ; je 0x39f880
        db 033h, 0F6h   ; xor esi, esi
$L_39f880:
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 00Bh, 01Ah   ; or ebx, dword ptr [edx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 05Ah, 004h   ; or ebx, dword ptr [edx + 4]
        db 00Bh, 05Dh, 01Ch   ; or ebx, dword ptr [ebp + 0x1c]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 05Ah, 008h   ; or ebx, dword ptr [edx + 8]
        db 00Bh, 05Dh, 00Ch   ; or ebx, dword ptr [ebp + 0xc]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 05Ah, 00Ch   ; or ebx, dword ptr [edx + 0xc]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 00Bh, 0DEh   ; or ebx, esi
        db 089h, 09Ch, 082h, 008h, 002h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0x208], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 032h   ; mov esi, dword ptr [edx]
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0CEh, 002h   ; or esi, 2
        db 0C1h, 0E6h, 008h   ; shl esi, 8
        db 00Bh, 032h   ; or esi, dword ptr [edx]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 072h, 004h   ; or esi, dword ptr [edx + 4]
        db 089h, 0B4h, 081h, 094h, 002h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x294], esi
        db 0E9h, 0A3h, 000h, 000h, 000h   ; jmp 0x39f982
$L_39f8df:
        db 08Bh, 07Dh, 01Ch   ; mov edi, dword ptr [ebp + 0x1c]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 057h, 004h   ; mov edx, dword ptr [edi + 4]
        db 08Bh, 077h, 008h   ; mov esi, dword ptr [edi + 8]
        db 08Bh, 07Fh, 00Ch   ; mov edi, dword ptr [edi + 0xc]
        db 0BBh, 000h, 000h, 0C0h, 000h   ; mov ebx, 0xc00000
        db 023h, 0C3h   ; and eax, ebx
        db 0B9h, 000h, 000h, 080h, 000h   ; mov ecx, 0x800000
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 023h, 0D3h   ; and edx, ebx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 023h, 0F3h   ; and esi, ebx
        db 02Bh, 0F1h   ; sub esi, ecx
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 0F7h, 0DEh   ; neg esi
        db 01Bh, 0F6h   ; sbb esi, esi
        db 023h, 0FBh   ; and edi, ebx
        db 02Bh, 0F9h   ; sub edi, ecx
        db 08Bh, 04Dh, 018h   ; mov ecx, dword ptr [ebp + 0x18]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 083h, 0E6h, 010h   ; and esi, 0x10
        db 0F7h, 0DFh   ; neg edi
        db 01Bh, 0FFh   ; sbb edi, edi
        db 00Bh, 019h   ; or ebx, dword ptr [ecx]
        db 083h, 0E7h, 010h   ; and edi, 0x10
        db 00Bh, 0D8h   ; or ebx, eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 059h, 004h   ; or ebx, dword ptr [ecx + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 059h, 008h   ; or ebx, dword ptr [ecx + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 08Bh, 075h, 014h   ; mov esi, dword ptr [ebp + 0x14]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 00Bh, 059h, 00Ch   ; or ebx, dword ptr [ecx + 0xc]
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 00Bh, 0DFh   ; or ebx, edi
        db 089h, 01Ch, 08Ah   ; mov dword ptr [edx + ecx*4], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 0C1h, 0E2h, 00Ch   ; shl edx, 0xc
        db 00Bh, 056h, 004h   ; or edx, dword ptr [esi + 4]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 089h, 094h, 08Eh, 088h, 001h, 000h, 000h   ; mov dword ptr [esi + ecx*4 + 0x188], edx
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 08Dh, 084h, 088h, 094h, 002h, 000h, 000h   ; lea eax, [eax + ecx*4 + 0x294]
        db 080h, 048h, 002h, 008h   ; or byte ptr [eax + 2], 8
$L_39f982:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 020h, 000h   ; ret 0x20
; // match: ?InstructionXDD@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z @ 0x0039F989
PUBLIC ?InstructionXDD@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z
?InstructionXDD@PixelShaderAssembler@XGRAPHICS@@AAEXKKPAK00000@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 051h   ; push ecx
        db 053h   ; push ebx
        db 033h, 0DBh   ; xor ebx, ebx
        db 039h, 05Dh, 00Ch   ; cmp dword ptr [ebp + 0xc], ebx
        db 056h   ; push esi
        db 057h   ; push edi
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 00Fh, 085h, 091h, 000h, 000h, 000h   ; jne 0x39fa2f
        db 08Bh, 055h, 01Ch   ; mov edx, dword ptr [ebp + 0x1c]
        db 0B8h, 000h, 000h, 0FFh, 000h   ; mov eax, 0xff0000
        db 039h, 002h   ; cmp dword ptr [edx], eax
        db 06Ah, 010h   ; push 0x10
        db 05Eh   ; pop esi
        db 075h, 004h   ; jne 0x39f9b1
        db 08Bh, 0FEh   ; mov edi, esi
        db 0EBh, 002h   ; jmp 0x39f9b3
$L_39f9b1:
        db 033h, 0FFh   ; xor edi, edi
$L_39f9b3:
        db 039h, 042h, 004h   ; cmp dword ptr [edx + 4], eax
        db 089h, 075h, 01Ch   ; mov dword ptr [ebp + 0x1c], esi
        db 074h, 003h   ; je 0x39f9be
        db 089h, 05Dh, 01Ch   ; mov dword ptr [ebp + 0x1c], ebx
$L_39f9be:
        db 039h, 042h, 008h   ; cmp dword ptr [edx + 8], eax
        db 089h, 075h, 00Ch   ; mov dword ptr [ebp + 0xc], esi
        db 074h, 003h   ; je 0x39f9c9
        db 089h, 05Dh, 00Ch   ; mov dword ptr [ebp + 0xc], ebx
$L_39f9c9:
        db 039h, 042h, 00Ch   ; cmp dword ptr [edx + 0xc], eax
        db 074h, 002h   ; je 0x39f9d0
        db 033h, 0F6h   ; xor esi, esi
$L_39f9d0:
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 08Bh, 055h, 020h   ; mov edx, dword ptr [ebp + 0x20]
        db 08Bh, 018h   ; mov ebx, dword ptr [eax]
        db 00Bh, 01Ah   ; or ebx, dword ptr [edx]
        db 00Bh, 0DFh   ; or ebx, edi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 05Ah, 004h   ; or ebx, dword ptr [edx + 4]
        db 00Bh, 05Dh, 01Ch   ; or ebx, dword ptr [ebp + 0x1c]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 05Ah, 008h   ; or ebx, dword ptr [edx + 8]
        db 00Bh, 05Dh, 00Ch   ; or ebx, dword ptr [ebp + 0xc]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 00Bh, 05Ah, 00Ch   ; or ebx, dword ptr [edx + 0xc]
        db 08Bh, 011h   ; mov edx, dword ptr [ecx]
        db 00Bh, 0DEh   ; or ebx, esi
        db 089h, 09Ch, 082h, 008h, 002h, 000h, 000h   ; mov dword ptr [edx + eax*4 + 0x208], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 032h   ; mov esi, dword ptr [edx]
        db 08Bh, 055h, 014h   ; mov edx, dword ptr [ebp + 0x14]
        db 08Bh, 009h   ; mov ecx, dword ptr [ecx]
        db 083h, 0CEh, 003h   ; or esi, 3
        db 0C1h, 0E6h, 008h   ; shl esi, 8
        db 00Bh, 032h   ; or esi, dword ptr [edx]
        db 0C1h, 0E6h, 004h   ; shl esi, 4
        db 00Bh, 072h, 004h   ; or esi, dword ptr [edx + 4]
        db 089h, 0B4h, 081h, 094h, 002h, 000h, 000h   ; mov dword ptr [ecx + eax*4 + 0x294], esi
        db 0E9h, 0A7h, 000h, 000h, 000h   ; jmp 0x39fad6
$L_39fa2f:
        db 08Bh, 07Dh, 01Ch   ; mov edi, dword ptr [ebp + 0x1c]
        db 08Bh, 007h   ; mov eax, dword ptr [edi]
        db 08Bh, 057h, 004h   ; mov edx, dword ptr [edi + 4]
        db 08Bh, 077h, 008h   ; mov esi, dword ptr [edi + 8]
        db 08Bh, 07Fh, 00Ch   ; mov edi, dword ptr [edi + 0xc]
        db 0BBh, 000h, 000h, 0C0h, 000h   ; mov ebx, 0xc00000
        db 023h, 0C3h   ; and eax, ebx
        db 0B9h, 000h, 000h, 080h, 000h   ; mov ecx, 0x800000
        db 02Bh, 0C1h   ; sub eax, ecx
        db 0F7h, 0D8h   ; neg eax
        db 01Bh, 0C0h   ; sbb eax, eax
        db 023h, 0D3h   ; and edx, ebx
        db 02Bh, 0D1h   ; sub edx, ecx
        db 083h, 0E0h, 010h   ; and eax, 0x10
        db 0F7h, 0DAh   ; neg edx
        db 01Bh, 0D2h   ; sbb edx, edx
        db 023h, 0F3h   ; and esi, ebx
        db 02Bh, 0F1h   ; sub esi, ecx
        db 083h, 0E2h, 010h   ; and edx, 0x10
        db 0F7h, 0DEh   ; neg esi
        db 01Bh, 0F6h   ; sbb esi, esi
        db 023h, 0FBh   ; and edi, ebx
        db 02Bh, 0F9h   ; sub edi, ecx
        db 08Bh, 04Dh, 018h   ; mov ecx, dword ptr [ebp + 0x18]
        db 08Bh, 019h   ; mov ebx, dword ptr [ecx]
        db 08Bh, 04Dh, 020h   ; mov ecx, dword ptr [ebp + 0x20]
        db 083h, 0E6h, 010h   ; and esi, 0x10
        db 0F7h, 0DFh   ; neg edi
        db 01Bh, 0FFh   ; sbb edi, edi
        db 00Bh, 019h   ; or ebx, dword ptr [ecx]
        db 083h, 0E7h, 010h   ; and edi, 0x10
        db 00Bh, 0D8h   ; or ebx, eax
        db 08Bh, 045h, 018h   ; mov eax, dword ptr [ebp + 0x18]
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 004h   ; or ebx, dword ptr [eax + 4]
        db 00Bh, 059h, 004h   ; or ebx, dword ptr [ecx + 4]
        db 00Bh, 0DAh   ; or ebx, edx
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 008h   ; or ebx, dword ptr [eax + 8]
        db 00Bh, 059h, 008h   ; or ebx, dword ptr [ecx + 8]
        db 00Bh, 0DEh   ; or ebx, esi
        db 0C1h, 0E3h, 008h   ; shl ebx, 8
        db 00Bh, 058h, 00Ch   ; or ebx, dword ptr [eax + 0xc]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 00Bh, 059h, 00Ch   ; or ebx, dword ptr [ecx + 0xc]
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 00Bh, 0DFh   ; or ebx, edi
        db 089h, 01Ch, 08Ah   ; mov dword ptr [edx + ecx*4], ebx
        db 08Bh, 055h, 010h   ; mov edx, dword ptr [ebp + 0x10]
        db 08Bh, 012h   ; mov edx, dword ptr [edx]
        db 08Bh, 030h   ; mov esi, dword ptr [eax]
        db 0C1h, 0E2h, 00Ch   ; shl edx, 0xc
        db 089h, 094h, 08Eh, 088h, 001h, 000h, 000h   ; mov dword ptr [esi + ecx*4 + 0x188], edx
        db 08Bh, 010h   ; mov edx, dword ptr [eax]
        db 08Dh, 00Ch, 08Dh, 094h, 002h, 000h, 000h   ; lea ecx, [ecx*4 + 0x294]
        db 003h, 0D1h   ; add edx, ecx
        db 080h, 04Ah, 002h, 008h   ; or byte ptr [edx + 2], 8
        db 08Bh, 000h   ; mov eax, dword ptr [eax]
        db 003h, 0C1h   ; add eax, ecx
        db 080h, 048h, 002h, 004h   ; or byte ptr [eax + 2], 4
$L_39fad6:
        db 05Fh   ; pop edi
        db 05Eh   ; pop esi
        db 05Bh   ; pop ebx
        db 0C9h   ; leave 
        db 0C2h, 020h, 000h   ; ret 0x20
seg63 ENDS



seg51 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ?Production@CD3DXAssembler@XGRAPHICS@@QAEXI@Z @ 0x003A2863
PUBLIC ?Production@CD3DXAssembler@XGRAPHICS@@QAEXI@Z
?Production@CD3DXAssembler@XGRAPHICS@@QAEXI@Z:
        db 055h   ; push ebp
        db 08Bh, 0ECh   ; mov ebp, esp
        db 081h, 0ECh, 040h, 004h, 000h, 000h   ; sub esp, 0x440
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 083h, 0C0h, 0FCh   ; add eax, -4
        db 083h, 0F8h, 043h   ; cmp eax, 0x43
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 00Fh, 087h, 04Ch, 00Ch, 000h, 000h   ; ja 0x3a34ca
        db 00Fh, 0B6h, 080h   ; movzx eax, byte ptr [eax + 0x3a35d1]
        dd $L_3a35d1
        db 053h   ; push ebx
        db 057h   ; push edi
        db 0FFh, 024h, 085h   ; jmp dword ptr [eax*4 + 0x3a3521]
        dd $L_3a3521
$L_3a288e:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Bh, 04Dh, 0F8h   ; or ecx, dword ptr [ebp - 8]
        db 0F7h, 0C1h, 000h, 0FFh, 0FFh, 0FFh   ; test ecx, 0xffffff00
        db 00Fh, 085h, 06Ah, 001h, 000h, 000h   ; jne 0x3a2a25
        db 033h, 0FFh   ; xor edi, edi
        db 089h, 0BEh, 084h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x84], edi
$L_3a28c3:
        db 089h, 0BEh, 080h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x80], edi
        db 089h, 0BEh, 088h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x88], edi
        db 089h, 0BEh, 08Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x8c], edi
        db 0E9h, 07Eh, 001h, 000h, 000h   ; jmp 0x3a2a58
$L_3a28da:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 00Bh, 055h, 0F8h   ; or edx, dword ptr [ebp - 8]
        db 0B8h, 000h, 0FFh, 0FFh, 0FFh   ; mov eax, 0xffffff00
        db 085h, 0D0h   ; test eax, edx
        db 00Fh, 085h, 01Dh, 001h, 000h, 000h   ; jne 0x3a2a25
        db 00Bh, 0C8h   ; or ecx, eax
        db 033h, 0FFh   ; xor edi, edi
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 00Bh, 04Dh, 0F8h   ; or ecx, dword ptr [ebp - 8]
        db 0C7h, 086h, 080h, 000h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x80], 1
        db 089h, 0BEh, 084h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x84], edi
        db 0EBh, 04Bh   ; jmp 0x3a296f
$L_3a2924:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 08Bh, 055h, 0F8h   ; mov edx, dword ptr [ebp - 8]
        db 08Bh, 0F9h   ; mov edi, ecx
        db 00Bh, 0FAh   ; or edi, edx
        db 0B8h, 000h, 0FFh, 0FFh, 0FFh   ; mov eax, 0xffffff00
        db 085h, 0F8h   ; test eax, edi
        db 00Fh, 085h, 0D1h, 000h, 000h, 000h   ; jne 0x3a2a25
        db 033h, 0FFh   ; xor edi, edi
        db 047h   ; inc edi
        db 00Bh, 0C8h   ; or ecx, eax
        db 089h, 0BEh, 080h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x80], edi
        db 089h, 0BEh, 084h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x84], edi
        db 0C1h, 0E1h, 008h   ; shl ecx, 8
        db 083h, 0C2h, 00Ah   ; add edx, 0xa
        db 033h, 0FFh   ; xor edi, edi
        db 00Bh, 0CAh   ; or ecx, edx
$L_3a296f:
        db 089h, 0BEh, 088h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x88], edi
        db 089h, 0BEh, 08Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x8c], edi
        db 089h, 08Eh, 09Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x9c], ecx
        db 0E9h, 042h, 00Bh, 000h, 000h   ; jmp 0x3a34c8
$L_3a2986:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Bh, 04Dh, 0F8h   ; or ecx, dword ptr [ebp - 8]
        db 0F7h, 0C1h, 000h, 0FFh, 0FFh, 0FFh   ; test ecx, 0xffffff00
        db 075h, 076h   ; jne 0x3a2a25
        db 033h, 0FFh   ; xor edi, edi
        db 0C7h, 086h, 084h, 000h, 000h, 000h, 001h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x84], 1
        db 0E9h, 003h, 0FFh, 0FFh, 0FFh   ; jmp 0x3a28c3
$L_3a29c0:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Bh, 04Dh, 0F8h   ; or ecx, dword ptr [ebp - 8]
        db 0F7h, 0C1h, 000h, 0FFh, 0FFh, 0FFh   ; test ecx, 0xffffff00
        db 075h, 03Ch   ; jne 0x3a2a25
        db 033h, 0FFh   ; xor edi, edi
        db 033h, 0C9h   ; xor ecx, ecx
        db 089h, 0BEh, 080h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x80], edi
        db 041h   ; inc ecx
        db 089h, 0BEh, 08Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x8c], edi
        db 0EBh, 050h   ; jmp 0x3a2a4c
$L_3a29fc:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 010h   ; lea edi, [esi + 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 00Bh, 04Dh, 0F8h   ; or ecx, dword ptr [ebp - 8]
        db 0F7h, 0C1h, 000h, 0FFh, 0FFh, 0FFh   ; test ecx, 0xffffff00
        db 074h, 017h   ; je 0x3a2a3c
$L_3a2a25:
        db 068h   ; push 0x3a9be0
        dd _unk_3A9BE0
        db 06Ah, 066h   ; push 0x66
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
        db 0E9h, 08Ch, 00Ah, 000h, 000h   ; jmp 0x3a34c8
$L_3a2a3c:
        db 083h, 0A6h, 080h, 000h, 000h, 000h, 000h   ; and dword ptr [esi + 0x80], 0
        db 033h, 0C9h   ; xor ecx, ecx
        db 041h   ; inc ecx
        db 089h, 08Eh, 08Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x8c], ecx
$L_3a2a4c:
        db 089h, 08Eh, 084h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x84], ecx
        db 089h, 08Eh, 088h, 000h, 000h, 000h   ; mov dword ptr [esi + 0x88], ecx
$L_3a2a58:
        db 00Dh, 000h, 0FEh, 0FFh, 0FFh   ; or eax, 0xfffffe00
        db 0C1h, 0E0h, 008h   ; shl eax, 8
        db 00Bh, 045h, 0F8h   ; or eax, dword ptr [ebp - 8]
        db 089h, 086h, 09Ch, 000h, 000h, 000h   ; mov dword ptr [esi + 0x9c], eax
        db 0E9h, 05Ah, 00Ah, 000h, 000h   ; jmp 0x3a34c8
$L_3a2a6e:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Dh, 04Eh, 030h   ; lea ecx, [esi + 0x30]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0CCh   ; lea eax, [ebp - 0x34]
        db 08Dh, 07Eh, 020h   ; lea edi, [esi + 0x20]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0C8h   ; lea eax, [ebp - 0x38]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0C4h   ; lea eax, [ebp - 0x3c]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0C0h   ; lea eax, [ebp - 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0C0h   ; lea eax, [ebp - 0x40]
        db 050h   ; push eax
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_3A222F   ; 0x3A222F
        db 0E9h, 00Ch, 00Ah, 000h, 000h   ; jmp 0x3a34c8
$L_3a2abc:
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 04Eh, 060h   ; lea ecx, [esi + 0x60]
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 004h   ; add dword ptr [esi + 0x7c], 4
        db 0E9h, 0DFh, 009h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2ae9:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Dh, 04Eh, 030h   ; lea ecx, [esi + 0x30]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 008h   ; add dword ptr [esi + 0x7c], 8
        db 0E9h, 096h, 009h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2b32:
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 00Ch   ; add dword ptr [esi + 0x7c], 0xc
        db 0E9h, 036h, 009h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2b92:
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], 0
        db 075h, 022h   ; jne 0x3a2bfa
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 025h, 0FFh, 0FFh, 000h, 000h   ; and eax, 0xffff
        db 083h, 0F8h, 003h   ; cmp eax, 3
        db 075h, 015h   ; jne 0x3a2bfa
        db 08Bh, 045h, 0F0h   ; mov eax, dword ptr [ebp - 0x10]
        db 025h, 002h, 000h, 0FFh, 0FFh   ; and eax, 0xffff0002
        db 083h, 0C8h, 002h   ; or eax, 2
        db 081h, 075h, 0E4h, 000h, 000h, 000h, 001h   ; xor dword ptr [ebp - 0x1c], 0x1000000
        db 089h, 045h, 0F0h   ; mov dword ptr [ebp - 0x10], eax
$L_3a2bfa:
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 010h   ; add dword ptr [esi + 0x7c], 0x10
        db 0E9h, 096h, 008h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2c32:
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E0h   ; push dword ptr [ebp - 0x20]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 014h   ; add dword ptr [esi + 0x7c], 0x14
        db 0E9h, 00Ch, 008h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2cbc:
        db 08Dh, 045h, 0DCh   ; lea eax, [ebp - 0x24]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0D8h   ; lea eax, [ebp - 0x28]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E0h   ; push dword ptr [ebp - 0x20]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0D8h   ; push dword ptr [ebp - 0x28]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 01Ch   ; add dword ptr [esi + 0x7c], 0x1c
        db 0E9h, 058h, 007h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2d70:
        db 08Dh, 045h, 0D4h   ; lea eax, [ebp - 0x2c]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0DCh   ; lea eax, [ebp - 0x24]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0D8h   ; lea eax, [ebp - 0x28]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0E0h   ; lea eax, [ebp - 0x20]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0E4h   ; lea eax, [ebp - 0x1c]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F8h   ; lea eax, [ebp - 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0ECh   ; lea eax, [ebp - 0x14]
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F0h   ; lea eax, [ebp - 0x10]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F0h   ; push dword ptr [ebp - 0x10]
        db 08Dh, 07Eh, 060h   ; lea edi, [esi + 0x60]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 045h, 0ECh   ; mov eax, dword ptr [ebp - 0x14]
        db 00Bh, 045h, 008h   ; or eax, dword ptr [ebp + 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0F8h   ; push dword ptr [ebp - 8]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E4h   ; push dword ptr [ebp - 0x1c]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0E0h   ; push dword ptr [ebp - 0x20]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0D8h   ; push dword ptr [ebp - 0x28]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0DCh   ; push dword ptr [ebp - 0x24]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 075h, 0D4h   ; push dword ptr [ebp - 0x2c]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 046h, 07Ch, 020h   ; add dword ptr [esi + 0x7c], 0x20
        db 0E9h, 08Fh, 006h, 000h, 000h   ; jmp 0x3a34c8
$L_3a2e39:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 080h, 04Dh, 00Ah, 00Fh   ; or byte ptr [ebp + 0xa], 0xf
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_3A20AA   ; 0x3A20AA
$L_3a2e55:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0E9h, 068h, 005h, 000h, 000h   ; jmp 0x3a33c5
$L_3a2e5d:
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_3A19C5   ; 0x3A19C5
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 081h, 0E1h, 0FFh, 0FFh, 0F0h, 0FFh   ; and ecx, 0xfff0ffff
        db 00Bh, 0C1h   ; or eax, ecx
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        call _sub_3A20AA   ; 0x3A20AA
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
$L_3a2e99:
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 083h, 07Dh, 0F4h, 000h   ; cmp dword ptr [ebp - 0xc], 0
        db 0E9h, 0D5h, 001h, 000h, 000h   ; jmp 0x3a307e
$L_3a2ea9:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
$L_3a2eb7:
        db 0FFh, 075h, 008h   ; push dword ptr [ebp + 8]
        db 0E9h, 0ABh, 000h, 000h, 000h   ; jmp 0x3a2f6a
$L_3a2ebf:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 000h, 000h, 000h, 00Fh   ; and eax, 0xf000000
        db 074h, 02Ch   ; je 0x3a2f03
        db 03Dh, 000h, 000h, 000h, 002h   ; cmp eax, 0x2000000
        db 074h, 016h   ; je 0x3a2ef4
        db 03Dh, 000h, 000h, 000h, 004h   ; cmp eax, 0x4000000
        db 075h, 0D2h   ; jne 0x3a2eb7
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 0FFh, 0FFh, 0F5h   ; and eax, 0xf5ffffff
        db 00Dh, 000h, 000h, 000h, 005h   ; or eax, 0x5000000
        db 0EBh, 01Ch   ; jmp 0x3a2f10
$L_3a2ef4:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 0FFh, 0FFh, 0F3h   ; and eax, 0xf3ffffff
        db 00Dh, 000h, 000h, 000h, 003h   ; or eax, 0x3000000
        db 0EBh, 00Dh   ; jmp 0x3a2f10
$L_3a2f03:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 0FFh, 0FFh, 0F1h   ; and eax, 0xf1ffffff
        db 00Dh, 000h, 000h, 000h, 001h   ; or eax, 0x1000000
$L_3a2f10:
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 0EBh, 0A2h   ; jmp 0x3a2eb7
$L_3a2f15:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], 0
        db 075h, 009h   ; jne 0x3a2f41
        db 068h   ; push 0x3a9bb4
        dd _unk_3A9BB4
        db 06Ah, 067h   ; push 0x67
        db 0EBh, 00Dh   ; jmp 0x3a2f4e
$L_3a2f41:
        db 0F6h, 045h, 00Bh, 00Fh   ; test byte ptr [ebp + 0xb], 0xf
        db 074h, 012h   ; je 0x3a2f59
        db 068h   ; push 0x3a9b84
        dd _unk_3A9B84
        db 06Ah, 068h   ; push 0x68
$L_3a2f4e:
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a2f59:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 0FFh, 0FFh, 0F6h   ; and eax, 0xf6ffffff
        db 00Dh, 000h, 000h, 000h, 006h   ; or eax, 0x6000000
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
        db 050h   ; push eax
$L_3a2f6a:
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?ValidateSrcRegister@CD3DXAssembler@XGRAPHICS@@QAEXK@Z   ; 0x3A219B
        db 0E9h, 0DFh, 0FEh, 0FFh, 0FFh   ; jmp 0x3a2e55
$L_3a2f76:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 0FFh, 0E4h, 0FFh   ; and eax, 0xffe4ffff
        db 00Dh, 000h, 000h, 0E4h, 000h   ; or eax, 0xe40000
$L_3a2f91:
        db 050h   ; push eax
        db 0E9h, 02Eh, 004h, 000h, 000h   ; jmp 0x3a33c5
$L_3a2f97:
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?DecodeSwizzle@CD3DXAssembler@XGRAPHICS@@QAEKPAD@Z   ; 0x3A1A6F
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 081h, 0E1h, 0FFh, 0FFh, 000h, 0FFh   ; and ecx, 0xff00ffff
        db 00Bh, 0C1h   ; or eax, ecx
        db 0EBh, 04Eh   ; jmp 0x3a3015
$L_3a2fc7:
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 033h, 0FFh   ; xor edi, edi
        db 057h   ; push edi
        db 057h   ; push edi
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?DecodeRegister@CD3DXAssembler@XGRAPHICS@@QAEKPADKH@Z   ; 0x3A1B0F
        db 08Dh, 04Eh, 030h   ; lea ecx, [esi + 0x30]
        db 0E9h, 088h, 000h, 000h, 000h   ; jmp 0x3a3070
$L_3a2fe8:
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 06Ah, 001h   ; push 1
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 08Bh, 0CEh   ; mov ecx, esi
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        call ?DecodeRegister@CD3DXAssembler@XGRAPHICS@@QAEKPADKH@Z   ; 0x3A1B0F
        db 00Dh, 000h, 000h, 000h, 080h   ; or eax, 0x80000000
$L_3a3015:
        db 050h   ; push eax
        db 0E9h, 07Eh, 0FEh, 0FFh, 0FFh   ; jmp 0x3a2e99
$L_3a301b:
        db 08Dh, 045h, 0D0h   ; lea eax, [ebp - 0x30]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 08Dh, 05Eh, 030h   ; lea ebx, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0F4h   ; lea eax, [ebp - 0xc]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0FFh, 075h, 0D0h   ; push dword ptr [ebp - 0x30]
        db 08Dh, 085h, 0C0h, 0FBh, 0FFh, 0FFh   ; lea eax, [ebp - 0x440]
        db 0FFh, 075h, 0FCh   ; push dword ptr [ebp - 4]
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        db 068h   ; push 0x3a9b7c
        dd _unk_3A9B7C
        db 050h   ; push eax
        call _sprintf   ; 0x2C61C4
        db 083h, 0C4h, 014h   ; add esp, 0x14
        db 033h, 0FFh   ; xor edi, edi
        db 057h   ; push edi
        db 057h   ; push edi
        db 08Dh, 085h, 0C0h, 0FBh, 0FFh, 0FFh   ; lea eax, [ebp - 0x440]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?DecodeRegister@CD3DXAssembler@XGRAPHICS@@QAEKPADKH@Z   ; 0x3A1B0F
        db 08Bh, 0CBh   ; mov ecx, ebx
$L_3a3070:
        db 00Dh, 000h, 000h, 000h, 080h   ; or eax, 0x80000000
        db 050h   ; push eax
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 039h, 07Dh, 0F4h   ; cmp dword ptr [ebp - 0xc], edi
$L_3a307e:
        db 00Fh, 084h, 044h, 004h, 000h, 000h   ; je 0x3a34c8
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 0FFh, 075h, 0F4h   ; push dword ptr [ebp - 0xc]
        call _XMemFree@8   ; 0x22FD39
        db 0E9h, 032h, 004h, 000h, 000h   ; jmp 0x3a34c8
$L_3a3096:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], 0
        db 074h, 009h   ; je 0x3a30b6
        db 068h   ; push 0x3a9b6c
        dd _unk_3A9B6C
        db 06Ah, 06Ah   ; push 0x6a
        db 0EBh, 010h   ; jmp 0x3a30c6
$L_3a30b6:
        db 081h, 07Dh, 0FCh, 000h, 000h, 000h, 0B0h   ; cmp dword ptr [ebp - 4], 0xb0000000
        db 074h, 012h   ; je 0x3a30d1
        db 068h   ; push 0x3a9b44
        dd _unk_3A9B44
        db 06Ah, 06Bh   ; push 0x6b
$L_3a30c6:
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a30d1:
        db 068h, 000h, 020h, 000h, 000h   ; push 0x2000
        db 0E9h, 0EAh, 002h, 000h, 000h   ; jmp 0x3a33c5
$L_3a30db:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 025h, 0FFh, 00Fh, 000h, 000h   ; and eax, 0xfff
        db 050h   ; push eax
        db 0E9h, 017h, 002h, 000h, 000h   ; jmp 0x3a330c
$L_3a30f5:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 05Eh, 030h   ; lea ebx, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], 0
        db 0BFh, 000h, 020h, 000h, 000h   ; mov edi, 0x2000
        db 074h, 009h   ; je 0x3a3125
        db 068h   ; push 0x3a9b6c
        dd _unk_3A9B6C
        db 06Ah, 06Ah   ; push 0x6a
        db 0EBh, 01Eh   ; jmp 0x3a3143
$L_3a3125:
        db 081h, 07Dh, 0FCh, 000h, 000h, 000h, 0B0h   ; cmp dword ptr [ebp - 4], 0xb0000000
        db 074h, 009h   ; je 0x3a3137
        db 068h   ; push 0x3a9b44
        dd _unk_3A9B44
        db 06Ah, 06Bh   ; push 0x6b
        db 0EBh, 00Ch   ; jmp 0x3a3143
$L_3a3137:
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 074h, 012h   ; je 0x3a314e
        db 068h   ; push 0x3a9b10
        dd _unk_3A9B10
        db 06Ah, 06Ch   ; push 0x6c
$L_3a3143:
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a314e:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 0E9h, 094h, 000h, 000h, 000h   ; jmp 0x3a31ea
$L_3a3156:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 003h, 0C8h   ; add ecx, eax
        db 0E9h, 03Dh, 002h, 000h, 000h   ; jmp 0x3a33ba
$L_3a317d:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 05Eh, 030h   ; lea ebx, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 083h, 0BEh, 080h, 000h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], 0
        db 0BFh, 000h, 020h, 000h, 000h   ; mov edi, 0x2000
        db 074h, 009h   ; je 0x3a31ad
        db 068h   ; push 0x3a9b6c
        dd _unk_3A9B6C
        db 06Ah, 06Ah   ; push 0x6a
        db 0EBh, 01Eh   ; jmp 0x3a31cb
$L_3a31ad:
        db 081h, 07Dh, 0FCh, 000h, 000h, 000h, 0B0h   ; cmp dword ptr [ebp - 4], 0xb0000000
        db 074h, 009h   ; je 0x3a31bf
        db 068h   ; push 0x3a9b44
        dd _unk_3A9B44
        db 06Ah, 06Bh   ; push 0x6b
        db 0EBh, 00Ch   ; jmp 0x3a31cb
$L_3a31bf:
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 074h, 012h   ; je 0x3a31d6
        db 068h   ; push 0x3a9b10
        dd _unk_3A9B10
        db 06Ah, 06Ch   ; push 0x6c
$L_3a31cb:
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a31d6:
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 08Bh, 0C8h   ; mov ecx, eax
        db 0F7h, 0D9h   ; neg ecx
        db 033h, 0C8h   ; xor ecx, eax
        db 081h, 0E1h, 0FFh, 00Fh, 000h, 000h   ; and ecx, 0xfff
        db 033h, 0C1h   ; xor eax, ecx
        db 089h, 045h, 008h   ; mov dword ptr [ebp + 8], eax
$L_3a31ea:
        db 00Bh, 0C7h   ; or eax, edi
        db 050h   ; push eax
        db 08Bh, 0CBh   ; mov ecx, ebx
        db 0E9h, 0CFh, 002h, 000h, 000h   ; jmp 0x3a34c3
$L_3a31f4:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 0D1h   ; mov edx, ecx
        db 0F7h, 0DAh   ; neg edx
        db 033h, 0D1h   ; xor edx, ecx
        db 0B8h, 0FFh, 00Fh, 000h, 000h   ; mov eax, 0xfff
        db 023h, 0D0h   ; and edx, eax
        db 033h, 0CAh   ; xor ecx, edx
        db 089h, 04Dh, 0FCh   ; mov dword ptr [ebp - 4], ecx
        db 023h, 0C8h   ; and ecx, eax
        db 0E9h, 0EFh, 000h, 000h, 000h   ; jmp 0x3a330b
$L_3a321c:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0BFh, 000h, 020h, 000h, 000h   ; mov edi, 0x2000
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 074h, 017h   ; je 0x3a3256
        db 085h, 07Dh, 0FCh   ; test dword ptr [ebp - 4], edi
        db 074h, 012h   ; je 0x3a3256
        db 068h   ; push 0x3a9b10
        dd _unk_3A9B10
        db 06Ah, 06Ch   ; push 0x6c
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a3256:
        db 08Bh, 04Dh, 008h   ; mov ecx, dword ptr [ebp + 8]
        db 0B8h, 0FFh, 00Fh, 000h, 000h   ; mov eax, 0xfff
        db 023h, 0C8h   ; and ecx, eax
        db 0BAh, 000h, 008h, 000h, 000h   ; mov edx, 0x800
        db 085h, 0CAh   ; test edx, ecx
        db 074h, 006h   ; je 0x3a326f
        db 081h, 0C9h, 000h, 0F0h, 0FFh, 0FFh   ; or ecx, 0xfffff000
$L_3a326f:
        db 08Bh, 05Dh, 0FCh   ; mov ebx, dword ptr [ebp - 4]
        db 023h, 0D8h   ; and ebx, eax
        db 085h, 0DAh   ; test edx, ebx
        db 074h, 006h   ; je 0x3a327e
        db 081h, 0CBh, 000h, 0F0h, 0FFh, 0FFh   ; or ebx, 0xfffff000
$L_3a327e:
        db 003h, 0CBh   ; add ecx, ebx
        db 0EBh, 07Bh   ; jmp 0x3a32fd
$L_3a3282:
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0BFh, 000h, 020h, 000h, 000h   ; mov edi, 0x2000
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 074h, 02Eh   ; je 0x3a32d3
        db 085h, 07Dh, 0FCh   ; test dword ptr [ebp - 4], edi
        db 074h, 012h   ; je 0x3a32bc
        db 068h   ; push 0x3a9b10
        dd _unk_3A9B10
        db 06Ah, 06Ch   ; push 0x6c
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a32bc:
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 074h, 012h   ; je 0x3a32d3
        db 068h   ; push 0x3a9af8
        dd _unk_3A9AF8
        db 06Ah, 07Fh   ; push 0x7f
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a32d3:
        db 08Bh, 05Dh, 008h   ; mov ebx, dword ptr [ebp + 8]
        db 0B8h, 0FFh, 00Fh, 000h, 000h   ; mov eax, 0xfff
        db 023h, 0D8h   ; and ebx, eax
        db 0BAh, 000h, 008h, 000h, 000h   ; mov edx, 0x800
        db 085h, 0DAh   ; test edx, ebx
        db 074h, 006h   ; je 0x3a32ec
        db 081h, 0CBh, 000h, 0F0h, 0FFh, 0FFh   ; or ebx, 0xfffff000
$L_3a32ec:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 023h, 0C8h   ; and ecx, eax
        db 085h, 0CAh   ; test edx, ecx
        db 074h, 006h   ; je 0x3a32fb
        db 081h, 0C9h, 000h, 0F0h, 0FFh, 0FFh   ; or ecx, 0xfffff000
$L_3a32fb:
        db 02Bh, 0CBh   ; sub ecx, ebx
$L_3a32fd:
        db 023h, 0C8h   ; and ecx, eax
        db 085h, 07Dh, 008h   ; test dword ptr [ebp + 8], edi
        db 075h, 005h   ; jne 0x3a3309
        db 085h, 07Dh, 0FCh   ; test dword ptr [ebp - 4], edi
        db 074h, 002h   ; je 0x3a330b
$L_3a3309:
        db 00Bh, 0CFh   ; or ecx, edi
$L_3a330b:
        db 051h   ; push ecx
$L_3a330c:
        db 08Dh, 04Eh, 030h   ; lea ecx, [esi + 0x30]
        db 0E9h, 0AFh, 001h, 000h, 000h   ; jmp 0x3a34c3
$L_3a3314:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0F6h, 045h, 009h, 020h   ; test byte ptr [ebp + 9], 0x20
        db 074h, 012h   ; je 0x3a3346
        db 068h   ; push 0x3a9af8
        dd _unk_3A9AF8
        db 06Ah, 07Fh   ; push 0x7f
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a3346:
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 02Bh, 045h, 008h   ; sub eax, dword ptr [ebp + 8]
        db 0EBh, 020h   ; jmp 0x3a336e
$L_3a334e:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 02Bh, 045h, 0FCh   ; sub eax, dword ptr [ebp - 4]
$L_3a336e:
        db 033h, 045h, 008h   ; xor eax, dword ptr [ebp + 8]
        db 025h, 0FFh, 00Fh, 000h, 000h   ; and eax, 0xfff
        db 033h, 045h, 008h   ; xor eax, dword ptr [ebp + 8]
        db 0E9h, 013h, 0FCh, 0FFh, 0FFh   ; jmp 0x3a2f91
$L_3a337e:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 08Dh, 045h, 008h   ; lea eax, [ebp + 8]
        db 08Dh, 07Eh, 030h   ; lea edi, [esi + 0x30]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0F6h, 045h, 009h, 020h   ; test byte ptr [ebp + 9], 0x20
        db 074h, 012h   ; je 0x3a33b0
        db 068h   ; push 0x3a9af8
        dd _unk_3A9AF8
        db 06Ah, 07Fh   ; push 0x7f
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a33b0:
        db 08Bh, 04Dh, 0FCh   ; mov ecx, dword ptr [ebp - 4]
        db 08Bh, 045h, 008h   ; mov eax, dword ptr [ebp + 8]
        db 003h, 0C8h   ; add ecx, eax
        db 0F7h, 0D9h   ; neg ecx
$L_3a33ba:
        db 033h, 0C8h   ; xor ecx, eax
        db 081h, 0E1h, 0FFh, 00Fh, 000h, 000h   ; and ecx, 0xfff
        db 033h, 0C8h   ; xor ecx, eax
        db 051h   ; push ecx
$L_3a33c5:
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0E9h, 0F7h, 000h, 000h, 000h   ; jmp 0x3a34c3
$L_3a33cc:
        db 033h, 0FFh   ; xor edi, edi
        db 039h, 0BEh, 080h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x80], edi
        db 075h, 022h   ; jne 0x3a33f8
        db 039h, 0BEh, 084h, 000h, 000h, 000h   ; cmp dword ptr [esi + 0x84], edi
        db 075h, 01Ah   ; jne 0x3a33f8
        db 068h   ; push 0x3a9ab0
        dd _unk_3A9AB0
        db 06Ah, 077h   ; push 0x77
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 010h   ; add esp, 0x10
$L_3a33f0:
        db 0FFh, 0B6h, 0B0h, 001h, 000h, 000h   ; push dword ptr [esi + 0x1b0]
        db 0EBh, 00Ch   ; jmp 0x3a3404
$L_3a33f8:
        db 08Bh, 086h, 0B0h, 001h, 000h, 000h   ; mov eax, dword ptr [esi + 0x1b0]
        db 00Dh, 000h, 000h, 000h, 040h   ; or eax, 0x40000000
        db 050h   ; push eax
$L_3a3404:
        db 08Dh, 07Eh, 040h   ; lea edi, [esi + 0x40]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 0FFh, 0B6h, 0B4h, 001h, 000h, 000h   ; push dword ptr [esi + 0x1b4]
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?UpdateDebugFileLine@CD3DXAssembler@XGRAPHICS@@QAEXXZ   ; 0x3A1846
        db 0E9h, 0A1h, 000h, 000h, 000h   ; jmp 0x3a34c8
$L_3a3427:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0DBh, 045h, 0FCh   ; fild dword ptr [ebp - 4]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 026h   ; jge 0x3a3463
        db 0D8h, 005h   ; fadd dword ptr [0x3eb834]
        dd _unk_3EB834
        db 0EBh, 01Eh   ; jmp 0x3a3463
$L_3a3445:
        db 08Dh, 045h, 0FCh   ; lea eax, [ebp - 4]
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0DBh, 045h, 0FCh   ; fild dword ptr [ebp - 4]
        db 08Bh, 045h, 0FCh   ; mov eax, dword ptr [ebp - 4]
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 006h   ; jge 0x3a3461
        db 0D8h, 005h   ; fadd dword ptr [0x3eb834]
        dd _unk_3EB834
$L_3a3461:
        db 0D9h, 0E0h   ; fchs 
$L_3a3463:
        db 0D9h, 05Dh, 0E8h   ; fstp dword ptr [ebp - 0x18]
        db 0EBh, 055h   ; jmp 0x3a34bd
$L_3a3468:
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 08Dh, 07Eh, 020h   ; lea edi, [esi + 0x20]
        db 050h   ; push eax
        db 08Bh, 0CFh   ; mov ecx, edi
        call ?Pop@XAsmCD3DXDwStack@XGRAPHICS@@QAEJPAK@Z   ; 0x3A72E4
        db 0D9h, 045h, 0E8h   ; fld dword ptr [ebp - 0x18]
        db 0D9h, 0E0h   ; fchs 
        db 08Bh, 0CFh   ; mov ecx, edi
        db 0D9h, 05Dh, 0E8h   ; fstp dword ptr [ebp - 0x18]
        db 0EBh, 03Eh   ; jmp 0x3a34c0
$L_3a3482:
        db 08Dh, 086h, 0B0h, 000h, 000h, 000h   ; lea eax, [esi + 0xb0]
        db 050h   ; push eax
        db 08Bh, 0CEh   ; mov ecx, esi
        call ?Push@XAsmCD3DXSzStack@XGRAPHICS@@QAEJPAD@Z   ; 0x3A73FA
        db 0EBh, 036h   ; jmp 0x3a34c8
$L_3a3492:
        db 08Dh, 086h, 0B0h, 000h, 000h, 000h   ; lea eax, [esi + 0xb0]
        db 050h   ; push eax
        call _atoi   ; 0x2C6F9B
        db 059h   ; pop ecx
        db 050h   ; push eax
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        db 0EBh, 01Eh   ; jmp 0x3a34c3
$L_3a34a5:
        db 08Dh, 045h, 0E8h   ; lea eax, [ebp - 0x18]
        db 050h   ; push eax
        db 08Dh, 086h, 0B0h, 000h, 000h, 000h   ; lea eax, [esi + 0xb0]
        db 068h   ; push 0x3de7e8
        dd _unk_3DE7E8
        db 050h   ; push eax
        call _sscanf   ; 0x2C94E0
        db 083h, 0C4h, 00Ch   ; add esp, 0xc
$L_3a34bd:
        db 08Dh, 04Eh, 020h   ; lea ecx, [esi + 0x20]
$L_3a34c0:
        db 0FFh, 075h, 0E8h   ; push dword ptr [ebp - 0x18]
$L_3a34c3:
        call ?Push@XAsmCD3DXDwStack@XGRAPHICS@@QAEJK@Z   ; 0x3A7342
$L_3a34c8:
        db 05Fh   ; pop edi
        db 05Bh   ; pop ebx
$L_3a34ca:
        db 08Bh, 0CEh   ; mov ecx, esi
        call _sub_3A7328   ; 0x3A7328
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 030h   ; jl 0x3a3505
        db 08Dh, 04Eh, 010h   ; lea ecx, [esi + 0x10]
        call _sub_3A7328   ; 0x3A7328
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 024h   ; jl 0x3a3505
        db 08Dh, 04Eh, 030h   ; lea ecx, [esi + 0x30]
        call _sub_3A7328   ; 0x3A7328
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 018h   ; jl 0x3a3505
        db 08Dh, 04Eh, 060h   ; lea ecx, [esi + 0x60]
        call _sub_3A7328   ; 0x3A7328
        db 085h, 0C0h   ; test eax, eax
        db 07Ch, 00Ch   ; jl 0x3a3505
        db 08Dh, 04Eh, 020h   ; lea ecx, [esi + 0x20]
        call _sub_3A7328   ; 0x3A7328
        db 085h, 0C0h   ; test eax, eax
        db 07Dh, 017h   ; jge 0x3a351c
$L_3a3505:
        db 068h, 08Dh, 004h, 000h, 000h   ; push 0x48d
        db 068h   ; push 0x3a9a90
        dd _unk_3A9A90
        db 06Ah, 06Dh   ; push 0x6d
        db 06Ah, 001h   ; push 1
        db 056h   ; push esi
        call _sub_3A19AB   ; 0x3A19AB
        db 083h, 0C4h, 014h   ; add esp, 0x14
$L_3a351c:
        db 05Eh   ; pop esi
        db 0C9h   ; leave 
        db 0C2h, 004h, 000h   ; ret 4
$L_3a3521:
        dd $L_3a288e
        dd $L_3a28da
        dd $L_3a2986
        dd $L_3a29c0
        dd $L_3a29fc
        dd $L_3a2924
        dd $L_3a2a6e
        dd $L_3a2abc
        dd $L_3a2ae9
        dd $L_3a2b32
        dd $L_3a2b92
        dd $L_3a2c32
        dd $L_3a2d70
        dd $L_3a2cbc
        dd $L_3a2e39
        dd $L_3a2e5d
        dd $L_3a2ea9
        dd $L_3a2ebf
        dd $L_3a2f15
        dd $L_3a2f76
        dd $L_3a2f97
        dd $L_3a2fc7
        dd $L_3a2fe8
        dd $L_3a301b
        dd $L_3a3096
        dd $L_3a30db
        dd $L_3a30f5
        dd $L_3a3156
        dd $L_3a317d
        dd $L_3a31f4
        dd $L_3a321c
        dd $L_3a3282
        dd $L_3a3314
        dd $L_3a334e
        dd $L_3a337e
        dd $L_3a33f0
        dd $L_3a33cc
        dd $L_3a3427
        dd $L_3a3445
        dd $L_3a3468
        dd $L_3a3482
        dd $L_3a3492
        dd $L_3a34a5
        dd $L_3a34c8
$L_3a35d1:
        db 000h
        db 001h
        db 002h
        db 003h
        db 004h
        db 005h
        db 02Bh
        db 02Bh
        db 02Bh
        db 02Bh
        db 006h
        db 02Bh
        db 02Bh
        db 007h
        db 008h
        db 009h
        db 00Ah
        db 00Bh
        db 00Ch
        db 00Dh
        db 00Ch
        db 00Eh
        db 00Fh
        db 010h
        db 011h
        db 012h
        db 013h
        db 014h
        db 015h
        db 016h
        db 017h
        db 018h
        db 019h
        db 01Ah
        db 01Bh
        db 01Ch
        db 01Dh
        db 02Bh
        db 01Eh
        db 01Fh
        db 020h
        db 021h
        db 022h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 023h
        db 024h
        db 025h
        db 025h
        db 026h
        db 02Bh
        db 02Bh
        db 027h
        db 028h
        db 029h
        db 02Ah
seg51 ENDS




seg55 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: ??1Map@PreProcessor@XGRAPHICS@@QAE@XZ @ 0x003A54F9
PUBLIC ??1Map@PreProcessor@XGRAPHICS@@QAE@XZ
??1Map@PreProcessor@XGRAPHICS@@QAE@XZ:
        jmp ?Cleanup@Map@PreProcessor@XGRAPHICS@@QAEXXZ   ; 0x3A5087
seg55 ENDS



seg58 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_3A6FD8 @ 0x003A6FD8
PUBLIC _sub_3A6FD8
_sub_3A6FD8:
        db 0C7h, 001h   ; mov dword ptr [ecx], 0x41aa68
        dd _unk_41AA68
        db 0C3h   ; ret 

seg58 ENDS

seg59 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_3A71C4 @ 0x003A71C4
PUBLIC _sub_3A71C4
_sub_3A71C4:
        db 0F6h, 044h, 024h, 004h, 001h   ; test byte ptr [esp + 4], 1
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        db 0C7h, 006h   ; mov dword ptr [esi], 0x41aa68
        dd _unk_41AA68
        db 074h, 00Bh   ; je 0x3a71df
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3a71df:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4

; // match: _sub_3A71E5 @ 0x003A71E5
PUBLIC _sub_3A71E5
_sub_3A71E5:
        db 056h   ; push esi
        db 08Bh, 0F1h   ; mov esi, ecx
        call _sub_3A6FD8   ; 0x3A6FD8
        db 0F6h, 044h, 024h, 008h, 001h   ; test byte ptr [esp + 8], 1
        db 074h, 00Fh   ; je 0x3a7203
        db 085h, 0F6h   ; test esi, esi
        db 074h, 00Bh   ; je 0x3a7203
        db 068h, 000h, 000h, 087h, 024h   ; push 0x24870000
        db 056h   ; push esi
        call _XMemFree@8   ; 0x22FD39
$L_3a7203:
        db 08Bh, 0C6h   ; mov eax, esi
        db 05Eh   ; pop esi
        db 0C2h, 004h, 000h   ; ret 4
        db 08Bh, 049h, 00Ch   ; mov ecx, dword ptr [ecx + 0xc]
        db 085h, 0C9h   ; test ecx, ecx
        db 074h, 007h   ; je 0x3a7217
        db 06Ah, 001h   ; push 1
        call ??_GPixelShaderVerifier@XGRAPHICS@@QAEPAXI@Z   ; 0x3A71A0
$L_3a7217:
        db 0C3h   ; ret 
seg59 ENDS

seg61 SEGMENT BYTE PUBLIC ALIAS('XGRPH') 'CODE'

; // match: _sub_3A74CA @ 0x003A74CA
PUBLIC _sub_3A74CA
_sub_3A74CA LABEL BYTE
        db 0CCh, 0CCh, 0CCh, 0CCh, 0CCh, 0CCh
seg61 ENDS

























seg61_s15 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A797B @ 0x003A797B
PUBLIC _unk_3A797B
_unk_3A797B LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 01Bh, 040h, 047h, 006h, 0FFh, 01Bh, 036h, 0C4h, 000h, 0E8h, 078h
        db 010h, 000h, 000h, 000h, 000h, 01Bh, 060h, 087h, 000h, 06Ch, 028h, 000h, 0C4h, 000h, 0E8h, 070h
        db 030h
seg61_s15 ENDS




















seg61_s192 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A7DB0 @ 0x003A7DB0
PUBLIC _unk_3A7DB0
_unk_3A7DB0 LABEL BYTE
        db 078h, 079h, 07Ah, 077h, 000h, 000h, 000h, 000h
seg61_s192 ENDS



seg61_s195 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A7DCB @ 0x003A7DCB
PUBLIC _unk_3A7DCB
_unk_3A7DCB LABEL BYTE
        db 000h, 03Fh, 072h, 076h, 063h, 000h, 000h, 000h, 000h
seg61_s195 ENDS


















seg61_s48 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A80C6 @ 0x003A80C6
PUBLIC _unk_3A80C6
_unk_3A80C6 LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 01Bh, 040h, 047h, 006h, 0FFh, 01Bh, 036h, 0C4h, 000h, 0E8h
        db 078h, 010h, 000h, 000h, 000h, 000h, 01Bh, 060h, 087h, 000h, 06Ch, 028h, 000h, 0C4h, 000h, 0E8h
        db 070h, 030h, 078h, 020h, 078h, 077h, 078h, 073h, 000h, 000h
seg61_s48 ENDS

seg61_s49 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A810E @ 0x003A810E
PUBLIC _unk_3A810E
_unk_3A810E LABEL BYTE
        db 000h, 000h
seg61_s49 ENDS

seg61_s1 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8169 @ 0x003A8169
PUBLIC _unk_3A8169
_unk_3A8169 LABEL BYTE
        db 000h, 000h, 000h
seg61_s1 ENDS

seg61_s2 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A818A @ 0x003A818A
PUBLIC _unk_3A818A
_unk_3A818A LABEL BYTE
        db 000h, 000h
seg61_s2 ENDS

seg61_s3 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A81AD @ 0x003A81AD
PUBLIC _unk_3A81AD
_unk_3A81AD LABEL BYTE
        db 000h
        db 000h, 000h
seg61_s3 ENDS

seg61_s4 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A81CE @ 0x003A81CE
PUBLIC _unk_3A81CE
_unk_3A81CE LABEL BYTE
        db 000h, 000h
seg61_s4 ENDS

seg61_s5 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A81EF @ 0x003A81EF
PUBLIC _unk_3A81EF
_unk_3A81EF LABEL BYTE
        db 000h
seg61_s5 ENDS

seg61_s6 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A820E @ 0x003A820E
PUBLIC _unk_3A820E
_unk_3A820E LABEL BYTE
        db 000h, 000h
seg61_s6 ENDS

seg61_s7 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8233 @ 0x003A8233
PUBLIC _unk_3A8233
_unk_3A8233 LABEL BYTE
        db 000h
seg61_s7 ENDS

seg61_s8 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8252 @ 0x003A8252
PUBLIC _unk_3A8252
_unk_3A8252 LABEL BYTE
        db 000h, 000h
seg61_s8 ENDS

seg61_s9 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A826B @ 0x003A826B
PUBLIC _unk_3A826B
_unk_3A826B LABEL BYTE
        db 000h
seg61_s9 ENDS

seg61_s10 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8287 @ 0x003A8287
PUBLIC _unk_3A8287
_unk_3A8287 LABEL BYTE
        db 000h
seg61_s10 ENDS

seg61_s11 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A82A9 @ 0x003A82A9
PUBLIC _unk_3A82A9
_unk_3A82A9 LABEL BYTE
        db 000h, 000h, 000h
seg61_s11 ENDS

seg61_s12 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A82BB @ 0x003A82BB
PUBLIC _unk_3A82BB
_unk_3A82BB LABEL BYTE
        db 000h
seg61_s12 ENDS

seg61_s13 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A82F9 @ 0x003A82F9
PUBLIC _unk_3A82F9
_unk_3A82F9 LABEL BYTE
        db 000h, 000h, 000h
seg61_s13 ENDS

seg61_s14 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A830B @ 0x003A830B
PUBLIC _unk_3A830B
_unk_3A830B LABEL BYTE
        db 000h
seg61_s14 ENDS

seg61_s16 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A831B @ 0x003A831B
PUBLIC _unk_3A831B
_unk_3A831B LABEL BYTE
        db 000h
seg61_s16 ENDS

seg61_s17 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A832B @ 0x003A832B
PUBLIC _unk_3A832B
_unk_3A832B LABEL BYTE
        db 000h
seg61_s17 ENDS

seg61_s18 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A833B @ 0x003A833B
PUBLIC _unk_3A833B
_unk_3A833B LABEL BYTE
        db 000h
seg61_s18 ENDS

seg61_s19 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A834B @ 0x003A834B
PUBLIC _unk_3A834B
_unk_3A834B LABEL BYTE
        db 000h
seg61_s19 ENDS

seg61_s20 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A835B @ 0x003A835B
PUBLIC _unk_3A835B
_unk_3A835B LABEL BYTE
        db 000h
seg61_s20 ENDS

seg61_s21 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A836B @ 0x003A836B
PUBLIC _unk_3A836B
_unk_3A836B LABEL BYTE
        db 000h
seg61_s21 ENDS

seg61_s22 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A837B @ 0x003A837B
PUBLIC _unk_3A837B
_unk_3A837B LABEL BYTE
        db 000h
seg61_s22 ENDS

seg61_s23 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A839B @ 0x003A839B
PUBLIC _unk_3A839B
_unk_3A839B LABEL BYTE
        db 000h
seg61_s23 ENDS

seg61_s24 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A83AB @ 0x003A83AB
PUBLIC _unk_3A83AB
_unk_3A83AB LABEL BYTE
        db 000h
seg61_s24 ENDS

seg61_s25 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A83BD @ 0x003A83BD
PUBLIC _unk_3A83BD
_unk_3A83BD LABEL BYTE
        db 000h
        db 000h, 000h
seg61_s25 ENDS

seg61_s26 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A83DE @ 0x003A83DE
PUBLIC _unk_3A83DE
_unk_3A83DE LABEL BYTE
        db 000h, 000h
seg61_s26 ENDS

seg61_s27 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A845E @ 0x003A845E
PUBLIC _unk_3A845E
_unk_3A845E LABEL BYTE
        db 000h, 000h
seg61_s27 ENDS

seg61_s28 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A847E @ 0x003A847E
PUBLIC _unk_3A847E
_unk_3A847E LABEL BYTE
        db 000h, 000h
seg61_s28 ENDS

seg61_s29 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A84C2 @ 0x003A84C2
PUBLIC _unk_3A84C2
_unk_3A84C2 LABEL BYTE
        db 000h, 000h
seg61_s29 ENDS

seg61_s30 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8582 @ 0x003A8582
PUBLIC _unk_3A8582
_unk_3A8582 LABEL BYTE
        db 000h, 000h
seg61_s30 ENDS

seg61_s31 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8592 @ 0x003A8592
PUBLIC _unk_3A8592
_unk_3A8592 LABEL BYTE
        db 000h, 000h
seg61_s31 ENDS

seg61_s32 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A85A9 @ 0x003A85A9
PUBLIC _unk_3A85A9
_unk_3A85A9 LABEL BYTE
        db 000h, 000h, 000h
seg61_s32 ENDS

seg61_s33 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A85C6 @ 0x003A85C6
PUBLIC _unk_3A85C6
_unk_3A85C6 LABEL BYTE
        db 000h, 000h
seg61_s33 ENDS

seg61_s34 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A85E5 @ 0x003A85E5
PUBLIC _unk_3A85E5
_unk_3A85E5 LABEL BYTE
        db 000h, 000h, 000h
seg61_s34 ENDS

seg61_s35 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8606 @ 0x003A8606
PUBLIC _unk_3A8606
_unk_3A8606 LABEL BYTE
        db 000h, 000h
seg61_s35 ENDS

seg61_s36 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8622 @ 0x003A8622
PUBLIC _unk_3A8622
_unk_3A8622 LABEL BYTE
        db 000h, 000h
seg61_s36 ENDS

seg61_s37 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8651 @ 0x003A8651
PUBLIC _unk_3A8651
_unk_3A8651 LABEL BYTE
        db 000h, 000h, 000h
seg61_s37 ENDS

seg61_s38 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A866F @ 0x003A866F
PUBLIC _unk_3A866F
_unk_3A866F LABEL BYTE
        db 000h
seg61_s38 ENDS

seg61_s39 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A868A @ 0x003A868A
PUBLIC _unk_3A868A
_unk_3A868A LABEL BYTE
        db 000h, 000h
seg61_s39 ENDS

seg61_s40 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A86A6 @ 0x003A86A6
PUBLIC _unk_3A86A6
_unk_3A86A6 LABEL BYTE
        db 000h, 000h
seg61_s40 ENDS

seg61_s41 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A86C5 @ 0x003A86C5
PUBLIC _unk_3A86C5
_unk_3A86C5 LABEL BYTE
        db 000h, 000h, 000h
seg61_s41 ENDS

seg61_s42 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A86E3 @ 0x003A86E3
PUBLIC _unk_3A86E3
_unk_3A86E3 LABEL BYTE
        db 000h
seg61_s42 ENDS

seg61_s43 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8703 @ 0x003A8703
PUBLIC _unk_3A8703
_unk_3A8703 LABEL BYTE
        db 000h
seg61_s43 ENDS

seg61_s44 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8723 @ 0x003A8723
PUBLIC _unk_3A8723
_unk_3A8723 LABEL BYTE
        db 000h
seg61_s44 ENDS

seg61_s45 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A873B @ 0x003A873B
PUBLIC _unk_3A873B
_unk_3A873B LABEL BYTE
        db 000h
seg61_s45 ENDS

seg61_s46 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8753 @ 0x003A8753
PUBLIC _unk_3A8753
_unk_3A8753 LABEL BYTE
        db 000h
seg61_s46 ENDS

seg61_s47 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8769 @ 0x003A8769
PUBLIC _unk_3A8769
_unk_3A8769 LABEL BYTE
        db 000h, 000h, 000h
seg61_s47 ENDS

seg61_s50 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A878B @ 0x003A878B
PUBLIC _unk_3A878B
_unk_3A878B LABEL BYTE
        db 000h
seg61_s50 ENDS

seg61_s51 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A87A7 @ 0x003A87A7
PUBLIC _unk_3A87A7
_unk_3A87A7 LABEL BYTE
        db 000h
seg61_s51 ENDS

seg61_s52 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A87C2 @ 0x003A87C2
PUBLIC _unk_3A87C2
_unk_3A87C2 LABEL BYTE
        db 000h, 000h
seg61_s52 ENDS

seg61_s53 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A87DD @ 0x003A87DD
PUBLIC _unk_3A87DD
_unk_3A87DD LABEL BYTE
        db 000h
        db 000h, 000h
seg61_s53 ENDS

seg61_s54 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8812 @ 0x003A8812
PUBLIC _unk_3A8812
_unk_3A8812 LABEL BYTE
        db 000h, 000h
seg61_s54 ENDS

seg61_s55 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A882E @ 0x003A882E
PUBLIC _unk_3A882E
_unk_3A882E LABEL BYTE
        db 000h, 000h
seg61_s55 ENDS

seg61_s56 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8845 @ 0x003A8845
PUBLIC _unk_3A8845
_unk_3A8845 LABEL BYTE
        db 000h, 000h, 000h
seg61_s56 ENDS

seg61_s57 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A8863 @ 0x003A8863
PUBLIC _unk_3A8863
_unk_3A8863 LABEL BYTE
        db 000h
seg61_s57 ENDS

seg61_s58 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A887D @ 0x003A887D
PUBLIC _unk_3A887D
_unk_3A887D LABEL BYTE
        db 000h
        db 000h, 000h
seg61_s58 ENDS

seg61_s59 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A889B @ 0x003A889B
PUBLIC _unk_3A889B
_unk_3A889B LABEL BYTE
        db 000h
seg61_s59 ENDS

seg61_s60 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A88B5 @ 0x003A88B5
PUBLIC _unk_3A88B5
_unk_3A88B5 LABEL BYTE
        db 000h, 000h, 000h
seg61_s60 ENDS

seg61_s61 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A88D1 @ 0x003A88D1
PUBLIC _unk_3A88D1
_unk_3A88D1 LABEL BYTE
        db 000h, 000h, 000h
seg61_s61 ENDS

seg61_s62 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A88ED @ 0x003A88ED
PUBLIC _unk_3A88ED
_unk_3A88ED LABEL BYTE
        db 000h
        db 000h, 000h
seg61_s62 ENDS



























































































































seg61_s139 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3A9C63 @ 0x003A9C63
PUBLIC _unk_3A9C63
_unk_3A9C63 LABEL BYTE
        db 000h, 065h, 06Eh, 075h, 06Dh, 000h, 000h, 000h, 000h
seg61_s139 ENDS




























seg61_s167 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3AA09E @ 0x003AA09E
PUBLIC _unk_3AA09E
_unk_3AA09E LABEL BYTE
        db 000h, 000h, 065h, 06Eh, 064h, 06Dh, 000h, 000h, 000h, 000h
seg61_s167 ENDS

seg61_s168 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3AA0C6 @ 0x003AA0C6
PUBLIC _unk_3AA0C6
_unk_3AA0C6 LABEL BYTE
        db 000h, 000h, 06Dh, 061h, 063h, 072h, 06Fh, 000h, 000h, 000h
seg61_s168 ENDS















seg61_s175 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3AA23F @ 0x003AA23F
PUBLIC _unk_3AA23F
_unk_3AA23F LABEL BYTE
        db 000h, 004h, 000h, 008h, 000h, 004h, 000h, 008h, 000h
seg61_s175 ENDS


seg61_s177 SEGMENT BYTE PUBLIC READONLY ALIAS('XGRPH_RD') 'DATA'

; // match: _unk_3AA28F @ 0x003AA28F
PUBLIC _unk_3AA28F
_unk_3AA28F LABEL BYTE
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0E8h, 0A9h, 041h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0F0h, 0A9h, 041h, 000h, 000h, 000h, 000h
        db 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 000h, 0AAh, 041h, 000h
seg61_s177 ENDS

        END
