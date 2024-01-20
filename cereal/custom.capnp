using Cxx = import "./include/c++.capnp";
$Cxx.namespace("cereal");

@0xb526ba661d550a59;

# custom.capnp: a home for empty structs reserved for custom forks
# These structs are guaranteed to remain reserved and empty in mainline
# cereal, so use these if you want custom events in your fork.

# you can rename the struct, but don't change the identifier
struct FrogPilotCarControl @0x81c2f05a394cf4af {
  alwaysOnLateral @0: Bool;
}

struct FrogPilotDeviceState @0xaedffd8f31e7b55d {
  freeSpace @0 :Int16;
  usedSpace @1 :Int16;
}

enum FrogPilotEvents @0xf35cc4560bbf6ec2 {
  frogSteerSaturated @0;
  greenLight @1;
  pedalInterceptorNoBrake @2;
  torqueNNLoad @3;
}

struct FrogPilotLateralPlan @0xda96579883444c35 {
  laneWidthLeft @0 :Float32;
  laneWidthRight @1 :Float32;
}

struct FrogPilotLongitudinalPlan @0x80ae746ee2596b11 {
  adjustedCruise @0: Float32;
  conditionalExperimental @1 :Bool;
  desiredFollowDistance @2 :Int16;
  distances @3 :List(Float32);
  redLight @4 :Bool;
  safeObstacleDistance @5 :Int16;
  safeObstacleDistanceStock @6 :Int16;
  slcOverridden @7 :Bool;
  slcOverriddenSpeed @8 :Float32;
  slcSpeedLimit @9 :Float32;
  slcSpeedLimitOffset @10 :Float32;
  stoppedEquivalenceFactor @11 :Int16;
}

struct FrogPilotNavigation @0xa5cd762cd951a455 {
  navigationConditionMet @0 :Bool;
}

struct CustomReserved6 @0xf98d843bfd7004a3 {
}

struct CustomReserved7 @0xb86e6369214c01c8 {
}

struct CustomReserved8 @0xf416ec09499d9d19 {
}

struct CustomReserved9 @0xa1680744031fdb2d {
}
