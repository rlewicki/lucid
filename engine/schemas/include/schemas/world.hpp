﻿#include "scene/actors/actor_enums.hpp"

STRUCT_BEGIN(lucid, FActorEntry, "Description of the actor in the world")
    STRUCT_FIELD(u32, Id, 0, "Id of the actor")	
    STRUCT_FIELD(u32, ParentId, 0, "Id of the parent actor")	
    STRUCT_FIELD(FDString, Name, "", "Name of the actor")	
    STRUCT_STATIC_ARRAY(float, Postion, 3, {0 COMMA 0 COMMA 0 }, "Position of the actor")	
    STRUCT_STATIC_ARRAY(float, Scale, 3, {1 COMMA 1 COMMA 1 }, "Scale of the actor")	
    STRUCT_STATIC_ARRAY(float, Rotation, 4, { 0 COMMA 0 COMMA 0 COMMA 0 }, "Rotation (quat) of the actor")
    STRUCT_FIELD(bool, bVisible, false, "")	    
STRUCT_END()

STRUCT_INHERIT_BEGIN(lucid, FStaticMeshDescription, lucid::FActorEntry, "")
    STRUCT_FIELD(FDString, MeshResourceName, "", "")	
    STRUCT_FIELD(FDString, MaterialName, "", "")
    STRUCT_FIELD(bool, bReverseNormals, false, "")
    STRUCT_FIELD(scene::EStaticMeshType, Type, lucid::scene::EStaticMeshType::STATIONARY, 0, "")
STRUCT_END()

STRUCT_BEGIN(lucid, FSkyboxDescription, "")
    STRUCT_STATIC_ARRAY(lucid::FDString, FacesTextures, 6, { "" COMMA "" COMMA "" COMMA "" COMMA "" COMMA "" }, "Names of texture resources making up the skybox (in order right, left, top, bottom, front, back)")	
STRUCT_END()

STRUCT_BEGIN(lucid, FLightEntry, "")
    STRUCT_FIELD(u32, Id, 0, "Id of the light")	
    STRUCT_FIELD(u32, ParentId, 0, "Parent actor id")	
    STRUCT_STATIC_ARRAY(float, Color, 3, {1 COMMA 1 COMMA 1 }, "")	
    STRUCT_FIELD(u8, Quality, 1, "")	
    STRUCT_FIELD(FDString, Name, "", "Name of the actor")	
    STRUCT_STATIC_ARRAY(float, Postion, 3, {0 COMMA 0 COMMA 0 }, "Position of the actor")	
    STRUCT_STATIC_ARRAY(float, Rotation, 4, { 0 COMMA 0 COMMA 0 COMMA 0 }, "Rotation (quat) of the actor")
    STRUCT_FIELD(bool, bCastsShadow, false, "")	    
STRUCT_END()

STRUCT_INHERIT_BEGIN(lucid, FDirectionalLightEntry, lucid::FLightEntry, "")
    STRUCT_STATIC_ARRAY(float, Direction, 3, {0 COMMA 0 COMMA 1}, "")	
    STRUCT_STATIC_ARRAY(float, LightUp, 3, {0 COMMA 1 COMMA 0}, "")	
STRUCT_END()

STRUCT_INHERIT_BEGIN(lucid, FSpotLightEntry, lucid::FLightEntry, "")
    STRUCT_STATIC_ARRAY(float, Direction, 3, {0 COMMA 0 COMMA 1}, "")	
    STRUCT_STATIC_ARRAY(float, LightUp, 3, {0 COMMA 1 COMMA 0}, "")	
    STRUCT_FIELD(float, Constant, 0, "")	
    STRUCT_FIELD(float, Linear, 0, "")	
    STRUCT_FIELD(float, Quadratic, 0, "")	
    STRUCT_FIELD(float, InnerCutOffRad, 0, "")	
    STRUCT_FIELD(float, OuterCutOffRad, 0, "")	
STRUCT_END()

STRUCT_INHERIT_BEGIN(lucid, FPointLightEntry, lucid::FLightEntry, "")
    STRUCT_FIELD(float, Constant, 0, "")	
    STRUCT_FIELD(float, Linear, 0, "")	
    STRUCT_FIELD(float, Quadratic, 0, "")	
    STRUCT_FIELD(float, NearPlane, 1, "")	
    STRUCT_FIELD(float, FarPlane, 25, "")	
STRUCT_END()

STRUCT_BEGIN(lucid, FWorldDescription, "Listing of all the things in the world")
    STRUCT_DYNAMIC_ARRAY(lucid::FStaticMeshDescription, StaticMeshes, "")
    STRUCT_FIELD(lucid::FSkyboxDescription, Skybox, lucid::FSkyboxDescription{}, "Paths to the skybox actor asset")
    STRUCT_DYNAMIC_ARRAY(lucid::FDirectionalLightEntry, DirectionalLights, "")
    STRUCT_DYNAMIC_ARRAY(lucid::FSpotLightEntry, SpotLights, "")
    STRUCT_DYNAMIC_ARRAY(lucid::FPointLightEntry, PointLights, "")
STRUCT_END()

STRUCT_BEGIN(lucid, FActorDatabaseEntry, "")
    STRUCT_FIELD(UUID,     ActorId, sole::uuid4(), "")
    STRUCT_FIELD(FDString, ActorPath, "", "")
    STRUCT_FIELD(lucid::scene::EActorType, ActorType, lucid::scene::EActorType::UNKNOWN, "")
STRUCT_END()

STRUCT_BEGIN(lucid, FActorDatabase, "")
    STRUCT_DYNAMIC_ARRAY(FActorDatabaseEntry, Entries,  "")
STRUCT_END()
