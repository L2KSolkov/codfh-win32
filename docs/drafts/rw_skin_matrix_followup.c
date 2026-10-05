/* PARKED 2026-10-01: insert this fragment immediately before
 * _rpSkinXboxSetMaterialColor in src/rw/plugin/skin2/xbox/skinxboxrender.c.
 * Uses that unit's existing headers. D3DMATRIXFromRwMatrix matches (100 bytes).
 * MatrixUpdate: 100 normalized diff lines in current unit context, versus
 * 121 for rw_skinxboxrender_draft3.c and 133 for rw_mu_gf.c in the same context.
 * First actual byte difference +0x1E: branch displacement (body length differs).
 * The hierarchy matrix-array spill also uses esp+0x1C instead of esp+0x20
 * (accounting for the pushed argument).
 * Changed first two branches to indexed shaderConstants[i * 3]; third branch
 * retains stepped constants. Tested all eight combinations, separate loop
 * scopes and pre/post increment; no exact match. Matrix slots, pointer spills,
 * and scheduling still differ. Scratch-score relocation addends and padding
 * are not byte failures: use match.py to locate the actual first mismatch.
 */
// match: _D3DMATRIXFromRwMatrix @ 0x002D21C0
static void
D3DMATRIXFromRwMatrix(D3DMATRIX *d, const RwMatrix *m)
{
    RwReal  *dst = (RwReal *)d;

    *dst++ = m->right.x;
    *dst++ = m->up.x;
    *dst++ = m->at.x;
    *dst++ = m->pos.x;

    *dst++ = m->right.y;
    *dst++ = m->up.y;
    *dst++ = m->at.y;
    *dst++ = m->pos.y;

    *dst++ = m->right.z;
    *dst++ = m->up.z;
    *dst++ = m->at.z;
    *dst = m->pos.z;
}

// match: __rpSkinXboxMatrixUpdate @ 0x002D2230
void
_rpSkinXboxMatrixUpdate(RwV4d *shaderConstants, RpAtomic *atomic, RpSkin *skin)
{
    RpHAnimHierarchy    *hierarchy = RPSKINATOMICGETDATA(atomic)->hierarchy;
    RwMatrix            result;
    RwInt32             i;

    if (hierarchy)
    {
        const RwMatrix  *matrixArray = hierarchy->pMatrixArray;
        const RwMatrix  *skinToBone = RpSkinGetSkinToBoneMatrices(skin);

        if (hierarchy->flags & rpHANIMHIERARCHYNOMATRICES)
        {
            RpHAnimNodeInfo *frameInfo = hierarchy->pNodeInfo;
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;
            RwV4d           *constants;

            rwMatrixInitialize(&inverseLtm, 0);
            rwMatrixInitialize(&tempMatrix, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            constants = shaderConstants;
            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[bone],
                                 RwFrameGetLTM(frameInfo[bone].pFrame));
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);

                constants += 3;
            }
        }
        else if (hierarchy->flags & rpHANIMHIERARCHYLOCALSPACEMATRICES)
        {
            RwV4d   *constants = shaderConstants;

            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&result, &skinToBone[bone], &matrixArray[bone]);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)&shaderConstants[i * 3], &result);

                constants += 3;
            }
        }
        else
        {
            RwMatrix        inverseLtm;
            RwMatrix        tempMatrix;
            RwV4d           *constants;

            rwMatrixInitialize(&inverseLtm, 0);

            RwMatrixInvert(&inverseLtm, RwFrameGetLTM(RpAtomicGetFrame(atomic)));

            constants = shaderConstants;
            for (i = 0; i < skin->platformData.numBonesUsed; i++)
            {
                RwInt32 bone = skin->platformData.matrixIndexMap[i];

                RwMatrixMultiply(&tempMatrix, &skinToBone[bone], &matrixArray[bone]);
                RwMatrixMultiply(&result, &tempMatrix, &inverseLtm);

                D3DMATRIXFromRwMatrix((D3DMATRIX *)constants, &result);

                constants += 3;
            }
        }
    }
    else
    {
        RwReal  *dst = (RwReal *)shaderConstants;

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

