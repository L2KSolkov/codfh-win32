// match: __rpSkinXboxMatrixUpdate @ 0x002D2230
void
_rpSkinXboxMatrixUpdate(RwV4d *shaderConstants, RpAtomic *atomic, RpSkin *skin)
{
    SkinAtomicData      *atomicData;
    RpHAnimHierarchy    *hierarchy;

    atomicData = RPSKINATOMICGETDATA(atomic);

    hierarchy = atomicData->hierarchy;

    if (hierarchy)
    {
        RwMatrix        *matrixArray;
        const RwMatrix  *skinToBone;
        RwMatrix        result;

        matrixArray = hierarchy->pMatrixArray;

        skinToBone = RpSkinGetSkinToBoneMatrices(skin);

        if (hierarchy->flags & rpHANIMHIERARCHYNOMATRICES)
        {
            RpHAnimNodeInfo *frameInfo;
            RwMatrix        inverseLtm;
            RwMatrix        prodMatrix;
            RwInt32         i;

            frameInfo = hierarchy->pNodeInfo;

            rwMatrixInitialize(&inverseLtm, 0);
            rwMatrixInitialize(&prodMatrix, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                const RwInt32   iNode = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&prodMatrix, &skinToBone[iNode],
                                 RwFrameGetLTM(frameInfo[iNode].pFrame));
                RwMatrixMultiply(&result, &prodMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);
            }
        }
        else if (hierarchy->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
        {
            RwInt32 i;

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                const RwInt32   iNode = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&result, &skinToBone[iNode], &matrixArray[iNode]);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);
            }
        }
        else
        {
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;
            RwInt32         i;

            rwMatrixInitialize(&inverseLtm, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                const RwInt32   iNode = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[iNode], &matrixArray[iNode]);
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);
            }
        }
    }
    else
    {
        RwReal  *dst = (RwReal *)shaderConstants;
        RwInt32 i;

        for (i = 0; i < skin->platformData.numBonesUsed; i++)
        {
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
            *dst++ = 0.0f;

            *dst++ = 0.0f;
            *dst++ = 0.0f;
            *dst++ = 1.0f;
            *dst++ = 0.0f;
        }
    }
}

