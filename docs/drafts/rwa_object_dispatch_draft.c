// match: _Behavior_DispatchCallback @ 0x0023F8B0
RwaObjHandle *
Behavior_DispatchCallback(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data)
{
    rwaParamFunc   *setter = &handle->objInterface->setters[index];

    return setter->func(handle->obj, setter->param, data) ? handle : NULL;
}

// match: _sub_23F8E0 @ 0x0023F8E0
RwaObjHandle *
sub_23F8E0(RwaObjHandle *handle, RwUInt32 index, RwInt32 type, void *data)
{
    rwaParamFunc   *getter = &handle->objInterface->getters[index];

    return getter->func(handle->obj, getter->param, data) ? handle : NULL;
}

