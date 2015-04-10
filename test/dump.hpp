std::string create_model(){
using namespace constrained_based_networks;
auto pool = Pool::getInstance();
new DataService("Dev::Sensors::KVH::DSP3000");
new DataService("Syskit::ComBus");
new DataService("Syskit::Device");
new DataService("Dev::Actuators::Lights");
new DataService("Dev::Bus::CAN::ClientSrv");
new DataService("Dev::Bus::CAN::ClientOutSrv");
new DataService("Dev::Bus::CAN::ClientInSrv");
new DataService("Dev::Bus::CAN::BusSrv");
new DataService("Dev::Actuators::Dynamixel");
new DataService("Dev::Bus::CAN::BusOutSrv");
new DataService("Dev::Actuators::PTU");
new DataService("Dev::Sensors::TimestamperDev");
new DataService("Dev::Sensors::Cameras::USB");
new DataService("Dev::Sensors::Cameras::Prosilica");
new DataService("Dev::Bus::CAN::BusInSrv");
new DataService("Dev::Sensors::Cameras::Firewire");
new DataService("Dev::Sensors::XsensAHRS");
new DataService("Dev::Bus::CAN::BusBaseSrv");
new DataService("WallServoing::WallOrientationSrv");
new DataService("Dev::Bus::CAN");
new DataService("Dev::Sensors::Hokuyo");
new DataService("Dev::Sensors::GPS");
new DataService("Base::PointcloudProviderSrv");
new DataService("Base::SonarScanProviderSrv");
new DataService("Base::LaserRangeFinderSrv");
new DataService("Base::WorldZRollPitchYawSrv");
new DataService("Base::WorldXYVelocityControllerSrv");
new DataService("Base::WorldYPositionXVelocityControllerSrv");
new DataService("Base::WorldXYZPositionControllerSrv");
new DataService("Base::WorldXYPositionControllerSrv");
new DataService("Base::WorldXYZRollPitchYawControllerSrv");
new DataService("Base::WorldXYZRollPitchYawControlledSystemSrv");
new DataService("Base::GroundDistanceSrv");
new DataService("Base::DVLSrv");
new DataService("Base::VelocitySrv");
new DataService("Base::PoseDeltaSrv");
new DataService("Base::RelativePoseSrv");
new DataService("Base::GlobalPoseSrv");
new DataService("Base::TransformationSrv");
new DataService("Base::PoseSrv");
new DataService("Base::OrientationWithZSrv");
new DataService("Base::AUVRelativeMotionControlledSystemSrv");
new DataService("Base::AUVRelativeMotionControllerSrv");
new DataService("Base::AUVRelativeMotionCommandConsumerSrv");
new DataService("Base::DistanceImageProviderSrv");
new DataService("Base::StereoPairProviderSrv");
new DataService("Base::ImageProviderSrv");
new DataService("Base::CalibratedIMUSensorsSrv");
new DataService("Base::CompensatedIMUSensorsSrv");
new DataService("Base::IMUSensorsSrv");
new DataService("Base::ImageConsumerSrv");
new DataService("Base::ZProviderSrv");
new DataService("Base::MapSrv");
new DataService("Dev::Profiling");
new DataService("Base::RawCommandControlledSystemSrv");
new DataService("Base::OrientationSrv");
new DataService("Base::OrientationToCorrectSrv");
new DataService("Base::PositionSrv");
new DataService("Auv::StructuredLightPairSrv");
new DataService("Base::RotationSrv");
new DataService("Auv::SoundSourceDirectionSrv");
new DataService("Auv::ModemConnectionSrv");
new DataService("Dev::Echosounder");
new DataService("Base::TimestampInputSrv");
new DataService("Base::AUVMotionControlledSystemSrv");
new DataService("Dev::Micron");
new DataService("Base::AUVMotionControllerSrv");
new DataService("Base::AUVMotionCommandConsumerSrv");
new DataService("Base::TimestamperSrv");
new DataService("Dev::Controldev::Mouse3D");
new DataService("Dev::Controldev::Joystick");
new DataService("Base::RawCommandControllerSrv");
new DataService("Localization::HoughSrv");
new DataService("Base::JointsControlledSystemSrv");
new DataService("Base::RawCommandCommandConsumerSrv");
new DataService("Base::JointsControllerSrv");
new DataService("Base::JointsCommandSrv");
new DataService("Base::JointsStatusSrv");
new DataService("Base::JointsCommandConsumerSrv");
new DataService("Base::ControlledSystemSrv");
new DataService("Base::ControllerSrv");
new DataService("Dev::Sensors::Modem");
new DataService("Dev::ASVModem");
new DataService("Dev::Sensors::Hbridge");
new DataService("Dev::Actuators::Hbridge");
new DataService("Dev::SystemStatus");
new DataService("Dev::Sensors::Battery");
new DataService("Dev::Sensors::DepthReaderAvalon");
new DataService("Dev::Sensors::BlueView");
{
auto t = new Task("Syskit::ROS::Node");
(void)t;
}
{
auto t = new Task("FogKvh::Dsp3000Task");
(void)t;
t->addFullfillment("Dev::Sensors::KVH::DSP3000");
t->addFullfillment("Base::RotationSrv");


}
{
auto t = new Task("AvalonControl::MotionFeedbackTask");
(void)t;
}
{
auto t = new Task("AvalonControl::TrajectoryFollower");
(void)t;
t->addFullfillment("Base::AUVRelativeMotionControllerSrv");
t->addFullfillment("Base::ControllerSrv");

t->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");

}
{
auto t = new Task("Lights::Lights");
(void)t;
t->addFullfillment("Dev::Actuators::Lights");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");


}
{
auto t = new Task("AvalonControl::RelFakeWriter");
(void)t;
t->addFullfillment("Base::AUVRelativeMotionControllerSrv");
t->addFullfillment("Base::ControllerSrv");

}
{
auto t = new Task("AvalonControl::FakeWriter");
(void)t;
t->addFullfillment("Base::AUVMotionControllerSrv");
t->addFullfillment("Base::ControllerSrv");

}
{
auto t = new Task("LineScanner::Task");
(void)t;
}
{
auto t = new Task("Syskit::RubyTaskContext");
(void)t;
}
{
auto t = new Task("AvalonControl::MotionControlTask");
(void)t;
t->addFullfillment("Base::AUVMotionControlledSystemSrv");
t->addFullfillment("Base::AUVMotionCommandConsumerSrv");
t->addFullfillment("Base::ControlledSystemSrv");

t->addFullfillment("Base::JointsControllerSrv");
t->addFullfillment("Base::ControllerSrv");

}
{
auto t = new Task("AvalonControl::PositionControlTask");
(void)t;
t->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
t->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
t->addFullfillment("Base::ControlledSystemSrv");

t->addFullfillment("Base::AUVMotionControllerSrv");
t->addFullfillment("Base::ControllerSrv");

}
{
auto t = new Task("AuvRelPosController::Task");
(void)t;
t->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
t->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
t->addFullfillment("Base::ControlledSystemSrv");

t->addFullfillment("Base::AUVMotionControllerSrv");
t->addFullfillment("Base::ControllerSrv");

}
{
auto t = new Task("ImagePreprocessing::HSVSegmentationAndBlur");
(void)t;
}
{
auto t = new Task("Canbus::InterfaceTask");
(void)t;
}
{
auto t = new Task("CameraProsilica::Task");
(void)t;
t->addFullfillment("Dev::Sensors::Cameras::Prosilica");
t->addFullfillment("Base::ImageProviderSrv");


}
{
auto t = new Task("RTT::TaskContext");
(void)t;
}
{
auto t = new Task("UwParticleLocalization::FastFusion");
(void)t;
}
{
auto t = new Task("WallServoing::DualSonarServoing");
(void)t;
}
{
auto t = new Task("ImagePreprocessing::MonoTask");
(void)t;
}
{
auto t = new Task("ImagePreprocessing::DepthImage2Pointcloud");
(void)t;
}
{
auto t = new Task("ImagePreprocessing::BaseTask");
(void)t;
}
{
auto t = new Task("WallOrientationCorrection::OrientationInMap");
(void)t;
}
{
auto t = new Task("WallOrientationCorrection::Task");
(void)t;
}
{
auto t = new Task("RawControlCommandConverter::Position");
(void)t;
}
{
auto t = new Task("RawControlCommandConverter::Movement");
(void)t;
}
{
auto t = new Task("AuvControl::OptimalHeadingController");
(void)t;
}
{
auto t = new Task("AuvControl::MotionCommand2DConverter");
(void)t;
}
{
auto t = new Task("AuvControl::ConstantCommandGroundFollower");
(void)t;
}
{
auto t = new Task("GpsHelper::GPSFaker");
(void)t;
}
{
auto t = new Task("AuvControl::ConstantCommand");
(void)t;
t->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");

}
{
auto t = new Task("Buoy::Survey");
(void)t;
}
{
auto t = new Task("SonarTritech::Micron");
(void)t;
t->addFullfillment("Dev::Micron");
t->addFullfillment("Base::GroundDistanceSrv");
t->addFullfillment("Base::SonarScanProviderSrv");


}
{
auto t = new Task("Buoy::Detector");
(void)t;
}
{
auto t = new Task("AuvControl::AlignedToBody");
(void)t;
}
{
auto t = new Task("Canbus::Task");
(void)t;
t->addFullfillment("Dev::Bus::CAN");
t->addFullfillment("Syskit::ComBus");


t->addFullfillment("Dev::Bus::CAN::BusInSrv");
t->addFullfillment("Dev::Bus::CAN::BusBaseSrv");

}
{
auto t = new Task("UwParticleLocalization::MotionModel");
(void)t;
}
{
auto t = new Task("OrientationEstimator::IKF");
(void)t;
}
{
auto t = new Task("AuvControl::WaypointNavigator");
(void)t;
}
{
auto t = new Task("OffshorePipelineDetector::Task");
(void)t;
}
{
auto t = new Task("AuvControl::ConstantCommandGroundAvoidance");
(void)t;
}
{
auto t = new Task("Transformer::Task");
(void)t;
}
{
auto t = new Task("OffshorePipelineDetector::SonarDetector");
(void)t;
}
{
auto t = new Task("GpsHelper::WaypointNavigation");
(void)t;
}
{
auto t = new Task("Controldev::Remote");
(void)t;
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");

t->addFullfillment("Dev::Controldev::Joystick");
t->addFullfillment("Base::RawCommandControllerSrv");
t->addFullfillment("Base::ControllerSrv");


}
{
auto t = new Task("Logger::Logger");
(void)t;
}
{
auto t = new Task("WallServoing::SingleSonarServoing");
(void)t;
}
{
auto t = new Task("Controldev::GenericRawToMotion2D");
(void)t;
}
{
auto t = new Task("SonarWallHough::Task");
(void)t;
}
{
auto t = new Task("Controldev::RawWheelToMotion2D");
(void)t;
}
{
auto t = new Task("SonarFeatureEstimator::Task");
(void)t;
}
{
auto t = new Task("GpsHelper::MapToGPS");
(void)t;
}
{
auto t = new Task("Controldev::RawJoystickToMotion2D");
(void)t;
}
{
auto t = new Task("AuvControl::BasePIDController");
(void)t;
}
{
auto t = new Task("PoseEstimation::VehiclePoseEstimator");
(void)t;
}
{
auto t = new Task("Controldev::SliderboxTask");
(void)t;
}
{
auto t = new Task("PoseEstimation::UWPoseEstimator");
(void)t;
}
{
auto t = new Task("Controldev::SteeringWheelTask");
(void)t;
}
{
auto t = new Task("SonarTritech::Profiling");
(void)t;
}
{
auto t = new Task("AuvControl::AccelerationController");
(void)t;
}
{
auto t = new Task("Controldev::JoystickTask");
(void)t;
t->addFullfillment("Dev::Controldev::Joystick");
t->addFullfillment("Base::RawCommandControllerSrv");
t->addFullfillment("Base::ControllerSrv");


}
{
auto t = new Task("Controldev::GenericTask");
(void)t;
}
{
auto t = new Task("PoseEstimation::BaseTask");
(void)t;
}
{
auto t = new Task("Controldev::Mouse3DTask");
(void)t;
t->addFullfillment("Dev::Controldev::Mouse3D");
t->addFullfillment("Base::RawCommandControllerSrv");
t->addFullfillment("Base::ControllerSrv");


}
{
auto t = new Task("AuvControl::Base");
(void)t;
}
{
auto t = new Task("Buoy::ServoingOnWall");
(void)t;
}
{
auto t = new Task("Controldev::JoyPadTask");
(void)t;
}
{
auto t = new Task("AuvHelper::DepthAndOrientationFusion");
(void)t;
}
{
auto t = new Task("SonarTritech::Echosounder");
(void)t;
t->addFullfillment("Dev::Echosounder");
t->addFullfillment("Base::GroundDistanceSrv");


}
{
auto t = new Task("OrientationEstimator::UKFEstimator");
(void)t;
}
{
auto t = new Task("AuvControl::WorldToAligned");
(void)t;
}
{
auto t = new Task("UwParticleLocalization::OrientationCorrection");
(void)t;
}
{
auto t = new Task("OrientationEstimator::IKFEstimator");
(void)t;
}
{
auto t = new Task("Buoy::Detector2");
(void)t;
}
{
auto t = new Task("OrientationEstimator::BaseEstimator");
(void)t;
}
{
auto t = new Task("XsensImu::Task");
(void)t;
t->addFullfillment("Dev::Sensors::XsensAHRS");
t->addFullfillment("Base::CalibratedIMUSensorsSrv");
t->addFullfillment("Base::IMUSensorsSrv");
t->addFullfillment("Base::OrientationSrv");


t->addFullfillment("Base::TimestampInputSrv");

}
{
auto t = new Task("WallServoing::SonarServoing");
(void)t;
}
{
auto t = new Task("CameraBase::Task");
(void)t;
}
{
auto t = new Task("UwParticleLocalization::Task");
(void)t;
}
{
auto t = new Task("AuvControl::PIDController");
(void)t;
}
{
auto t = new Task("SonarFeatureDetector::Task");
(void)t;
}
{
auto t = new Task("WallServoing::WallServoing");
(void)t;
}
{
auto t = new Task("WallServoing::WallDetector");
(void)t;
}
{
auto t = new Task("ImagePreprocessing::StereoTask");
(void)t;
}
{
auto t = new Task("LowLevelDriver::LowLevelTask");
(void)t;
}
{
auto t = new Task("FrameDemultiplexer::Task");
(void)t;
}
{
auto t = new Task("ModemCan::Task");
(void)t;
t->addFullfillment("Dev::Sensors::Modem");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");


}
{
auto t = new Task("Modemdriver::ModemCanbus");
(void)t;
t->addFullfillment("Dev::ASVModem");
t->addFullfillment("Dev::Bus::CAN::ClientOutSrv");


}
{
auto t = new Task("Modemdriver::ModemSerial");
(void)t;
}
{
auto t = new Task("Modemdriver::Modem");
(void)t;
}
{
auto t = new Task("CameraUnicap::CameraTask");
(void)t;
}
{
auto t = new Task("AuvWaypointNavigator::Task");
(void)t;
}
{
auto t = new Task("VideoStreamerVlc::Streamer");
(void)t;
t->addFullfillment("Base::ImageConsumerSrv");

t->addFullfillment("Base::ImageConsumerSrv");

t->addFullfillment("Base::ImageConsumerSrv");

}
{
auto t = new Task("VideoStreamerVlc::Capturer");
(void)t;
}
{
auto t = new Task("Sysmon::Task");
(void)t;
t->addFullfillment("Dev::SystemStatus");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");


}
{
auto t = new Task("VideoStreamerVlc::Streamer{1}");
(void)t;
t->addFullfillment("Base::ImageConsumerSrv");

t->addFullfillment("Base::ImageConsumerSrv");

t->addFullfillment("Base::ImageConsumerSrv");

}
{
auto t = new Task("PipelineInspection::ColorFilter");
(void)t;
}
{
auto t = new Task("RearSonarDistanceEstimator::Task");
(void)t;
}
{
auto t = new Task("PipelineInspection::Inspection");
(void)t;
}
{
auto t = new Task("PipelineInspection::LaserSimulation");
(void)t;
}
{
auto t = new Task("Hbridge::CommandWriter");
(void)t;
t->addFullfillment("Dev::Actuators::Hbridge");


t->addFullfillment("Dev::Bus::CAN::ClientSrv");
t->addFullfillment("Dev::Bus::CAN::ClientOutSrv");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");

t->addFullfillment("Base::JointsStatusSrv");

}
{
auto t = new Task("BatteryWatcher::Task");
(void)t;
t->addFullfillment("Dev::Sensors::Battery");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");


}
{
auto t = new Task("DepthReader::Task");
(void)t;
t->addFullfillment("Dev::Sensors::DepthReaderAvalon");
t->addFullfillment("Dev::Bus::CAN::ClientOutSrv");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");
t->addFullfillment("Base::ZProviderSrv");


}
{
auto t = new Task("Taskmon::Task");
(void)t;
}
{
auto t = new Task("StructureServoing::Task");
(void)t;
}
{
auto t = new Task("StructureServoing::Alignment");
(void)t;
}
{
auto t = new Task("HsvMosaicing::Task");
(void)t;
}
{
auto t = new Task("Dynamixel::Task");
(void)t;
t->addFullfillment("Dev::Actuators::Dynamixel");


t->addFullfillment("Base::TransformationSrv");

}
{
auto t = new Task("Hbridge::SensorReader");
(void)t;
t->addFullfillment("Dev::Sensors::Hbridge");


t->addFullfillment("Base::JointsStatusSrv");

t->addFullfillment("Dev::Bus::CAN::ClientSrv");
t->addFullfillment("Dev::Bus::CAN::ClientOutSrv");
t->addFullfillment("Dev::Bus::CAN::ClientInSrv");

}
{
auto t = new Task("Gps::BaseTask");
(void)t;
t->addFullfillment("Dev::Sensors::GPS");
t->addFullfillment("Base::PositionSrv");


}
{
auto t = new Task("Gps::GPSDTask");
(void)t;
t->addFullfillment("Dev::Sensors::GPS");
t->addFullfillment("Base::PositionSrv");


}
{
auto t = new Task("Gps::MB500Task");
(void)t;
t->addFullfillment("Dev::Sensors::GPS");
t->addFullfillment("Base::PositionSrv");


}
{
auto t = new Task("Interfaces::IMU");
(void)t;
}
{
auto t = new Task("Interfaces::LaserRangeFinder");
(void)t;
}
{
auto t = new Task("Interfaces::ActuatorSensorReader");
(void)t;
}
{
auto t = new Task("Interfaces::ActuatorCommandWriter");
(void)t;
}
{
auto t = new Task("Interfaces::Servo");
(void)t;
}
{
auto t = new Task("SonarStructureServoing::Task");
(void)t;
}
{
auto t = new Task("StructuredLight::Calibration");
(void)t;
}
{
auto t = new Task("StructuredLight::Task");
(void)t;
}
{
auto t = new Task("SonarBlueview::Task");
(void)t;
t->addFullfillment("Dev::Sensors::BlueView");
t->addFullfillment("Base::ImageProviderSrv");


}
{
auto t = new Task("StructureReconstruction::Task");
(void)t;
}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::TrajectoryMove");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"foo");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::TrajectoryMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::DetectorCmp<Base::AUVRelativeMotionControllerSrv>");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Buoy::Detector"),"detector");
c->addFullfillment("Buoy::DetectorCmp");









c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::ControllerSrv");


}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::DetectorCmp<Base::ControllerSrv>");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Buoy::Detector"),"detector");
c->addFullfillment("Buoy::DetectorCmp");









c->addFullfillment("Base::ControllerSrv");


}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::JoystickCommandCmp");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"rawCommand");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("RawControlCommandConverter::Movement"),"rawCommandConverter");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addFullfillment("AuvControl::JoystickCommandCmp");
c->addFullfillment("Base::AUVMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");
c->addFullfillment("Base::WorldXYVelocityControllerSrv");




c->addFullfillment("Base::AUVMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::WorldXYVelocityControllerSrv");








}
{
auto c = new Composition("PoseAuv::PoseEstimatorBlindCmp");
c->addChild(pool->getComponent("PoseEstimation::UWPoseEstimator"),"pose_estimator");
c->addChild(pool->getComponent("Base::OrientationSrv"),"ori");
c->addChild(pool->getComponent("Base::VelocitySrv"),"model");
c->addChild(pool->getComponent("Base::ZProviderSrv"),"depth");
c->addFullfillment("PoseAuv::PoseEstimatorBlindCmp");
c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");




c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");

c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::ZProviderSrv");

c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::PositionSrv");








}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimplePosMove");
c->addChild(pool->getComponent("AvalonControl::RelFakeWriter"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("AuvControl::SimplePosMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AuvRelPosController::Task), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AuvRelPosController::Task), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Localization::SonarFeatureDetectorCmp");
c->addChild(pool->getComponent("SonarFeatureDetector::Task"),"sonar_detector");
c->addFullfillment("Localization::SonarFeatureDetectorCmp");
c->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");




c->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Localization::FixMapHack");
c->addChild(pool->getComponent("SonarFeatureDetector::Task"),"sonar_detector");
c->addFullfillment("Localization::FixMapHack");









}
{
auto c = new Composition("Buoy::DetectorNewCmp");
c->addChild(pool->getComponent("Buoy::Detector"),"main");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"front_camera");
c->addFullfillment("Buoy::DetectorNewCmp");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("PoseAuv::IKFOrientationEstimatorCmp");
c->addChild(pool->getComponent("OrientationEstimator::BaseEstimator"),"estimator");
c->addChild(pool->getComponent("WallOrientationCorrection::OrientationInMap"),"ori_in_map");
c->addChild(pool->getComponent("XsensImu::Task"),"imu");
c->addChild(pool->getComponent("FogKvh::Dsp3000Task"),"fog");
c->addFullfillment("PoseAuv::IKFOrientationEstimatorCmp");
c->addFullfillment("Base::OrientationToCorrectSrv");
c->addFullfillment("Base::OrientationSrv");




c->addFullfillment("Base::OrientationToCorrectSrv");

c->addFullfillment("Base::OrientationSrv");








}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("ConsWA");
c->addChild(pool->getComponent("AuvControl::ConstantCommand"),"controller_v");
c->addFullfillment("ConsWA");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AvalonControl::MotionControlTask), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AvalonControl::MotionControlTask), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Localization::HoughDetector");
c->addChild(pool->getComponent("SonarWallHough::Task"),"main");
c->addChild(pool->getComponent("Base::SonarScanProviderSrv"),"sonar");
c->addChild(pool->getComponent("Base::OrientationSrv"),"ori");
c->addFullfillment("Localization::HoughDetector");
c->addFullfillment("Localization::HoughSrv");




c->addFullfillment("Localization::HoughSrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Localization::DeadReckoning");
c->addChild(pool->getComponent("UwParticleLocalization::MotionModel"),"main");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"ori");
c->addChild(pool->getComponent("Base::JointsStatusSrv"),"hb");
c->addFullfillment("Localization::DeadReckoning");
c->addFullfillment("Base::VelocitySrv");




c->addFullfillment("Base::VelocitySrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Detector");
c->addChild(pool->getComponent("WallServoing::SingleSonarServoing"),"detector");
c->addChild(pool->getComponent("SonarTritech::Micron"),"sonar");
c->addChild(pool->getComponent("SonarFeatureEstimator::Task"),"sonar_estimator");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addFullfillment("Wall::Detector");
c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");




c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::ControllerSrv");








}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower");
c->addChild(pool->getComponent("Wall::Detector"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::DetectorNew");
c->addChild(pool->getComponent("WallServoing::SingleSonarServoing"),"detector");
c->addChild(pool->getComponent("SonarTritech::Micron"),"sonar");
c->addChild(pool->getComponent("SonarFeatureEstimator::Task"),"sonar_estimator");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addFullfillment("Wall::DetectorNew");
c->addFullfillment("WallServoing::WallOrientationSrv");
c->addFullfillment("Base::WorldXYPositionControllerSrv");




c->addFullfillment("WallServoing::WallOrientationSrv");

c->addFullfillment("Base::WorldXYPositionControllerSrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("GPSHelper::GPSWaypointsCmp");
c->addChild(pool->getComponent("GpsHelper::WaypointNavigation"),"main");
c->addChild(pool->getComponent("Base::PositionSrv"),"gps");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("GPSHelper::GPSWaypointsCmp");
c->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");




c->addFullfillment("Base::WorldXYZRollPitchYawControllerSrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Localization::ParticleDetector");
c->addChild(pool->getComponent("UwParticleLocalization::Task"),"main");
c->addChild(pool->getComponent("Base::SonarScanProviderSrv"),"sonar");
c->addChild(pool->getComponent("SonarFeatureEstimator::Task"),"sonar_estimator");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"ori");
c->addChild(pool->getComponent("Base::JointsStatusSrv"),"hb");
c->addFullfillment("Localization::ParticleDetector");
c->addFullfillment("Base::VelocitySrv");
c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");
c->addFullfillment("Base::MapSrv");




c->addFullfillment("Base::VelocitySrv");

c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");

c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::ZProviderSrv");

c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::PositionSrv");

c->addFullfillment("Base::MapSrv");








}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::DetectorCmp2");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Buoy::Detector2"),"detector");
c->addFullfillment("Buoy::DetectorCmp2");









}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Base::ControlLoop");
c->addChild(pool->getComponent("Base::ControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimpleMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvControl::SimpleMove");
c->addChild(pool->getComponent("AvalonControl::FakeWriter"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"reading");
c->addFullfillment("AuvControl::SimpleMove");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::DetectorCmp");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Buoy::Detector"),"detector");
c->addFullfillment("Buoy::DetectorCmp");









}
{
auto c = new Composition("PoseAuv::PoseEstimatorCmp");
c->addChild(pool->getComponent("PoseEstimation::UWPoseEstimator"),"pose_estimator");
c->addChild(pool->getComponent("Base::OrientationSrv"),"ori");
c->addChild(pool->getComponent("Base::VelocitySrv"),"model");
c->addChild(pool->getComponent("Base::ZProviderSrv"),"depth");
c->addFullfillment("PoseAuv::PoseEstimatorCmp");
c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");




c->addFullfillment("Base::PoseSrv");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");
c->addFullfillment("Base::PositionSrv");

c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::ZProviderSrv");

c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::PositionSrv");








}
{
// auto c2 = new Composition("AuvControl::DepthFusionCmp");
auto c = new Composition("AuvControl::DepthFusionCmp");
#if 1 
c->addChild(pool->getComponent("Base::ZProviderSrv"),"z");
c->addChild(pool->getComponent("Base::OrientationSrv"),"ori");
c->addChild(pool->getComponent("AuvHelper::DepthAndOrientationFusion"),"task");
c->addFullfillment("AuvControl::DepthFusionCmp");
c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");




c->addFullfillment("Base::OrientationWithZSrv");
c->addFullfillment("Base::ZProviderSrv");
c->addFullfillment("Base::OrientationSrv");

c->addFullfillment("Base::ZProviderSrv");

c->addFullfillment("Base::OrientationSrv");








#endif
}
{
auto c = new Composition("LowLevel::Cmp");
c->addChild(pool->getComponent("LowLevelDriver::LowLevelTask"),"ll");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"z");
c->addFullfillment("LowLevel::Cmp");









}
{
auto c = new Composition("Base::ControlLoop/[controller.is_a?(AvalonControl::PositionControlTask), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addFullfillment("Base::ControlLoop/[controller.is_a?(AvalonControl::PositionControlTask), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Modem::ModemCmp");
c->addChild(pool->getComponent("Dev::ASVModem"),"main");
c->addFullfillment("Modem::ModemCmp");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Wall::Detector"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Hbridge::ControlSystem");
c->addChild(pool->getComponent("Dev::Actuators::Hbridge"),"sensors");
c->addChild(pool->getComponent("Dev::Actuators::Hbridge"),"command");
c->addFullfillment("Hbridge::ControlSystem");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");




c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");








}
{
auto c = new Composition("Pipeline::Detector_new");
c->addChild(pool->getComponent("OffshorePipelineDetector::Task"),"offshorePipelineDetector");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addFullfillment("Pipeline::Detector_new");
c->addFullfillment("Base::WorldXYPositionControllerSrv");




c->addFullfillment("Base::WorldXYPositionControllerSrv");








}
{
auto c = new Composition("Pipeline::Detector");
c->addChild(pool->getComponent("OffshorePipelineDetector::Task"),"offshorePipelineDetector");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addFullfillment("Pipeline::Detector");
c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");




c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::ControllerSrv");








}
{
auto c = new Composition("Pipeline::Follower");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Pipeline::Follower/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Pipeline::Detector"),"controller_local");
c->addFullfillment("Pipeline::Follower/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Pipeline::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("AuvCont::BuoyWallCmp");
c->addChild(pool->getComponent("Base::WorldXYZPositionControllerSrv"),"main");
c->addChild(pool->getComponent("Base::WorldXYZPositionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addFullfillment("AuvCont::BuoyWallCmp");
c->addFullfillment("AuvCont::WorldXYZPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("AuvCont::WorldXYZPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("bottom_camera_cmp");
c->addChild(pool->getComponent("VideoStreamerVlc::Streamer"),"vlc");
c->addChild(pool->getComponent("Dev::Sensors::Cameras::Prosilica"),"camera");
c->addFullfillment("bottom_camera_cmp");









}
{
auto c = new Composition("front_camera_cmp");
c->addChild(pool->getComponent("VideoStreamerVlc::Streamer"),"vlc");
c->addChild(pool->getComponent("Dev::Sensors::Cameras::Prosilica"),"camera");
c->addFullfillment("front_camera_cmp");









}
{
auto c = new Composition("blueview_cmp");
c->addChild(pool->getComponent("VideoStreamerVlc::Streamer"),"vlc");
c->addChild(pool->getComponent("Dev::Sensors::BlueView"),"camera");
c->addFullfillment("blueview_cmp");









}
{
auto c = new Composition("AuvCont::WorldXYZPositionCmp");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("Base::WorldXYZPositionControllerSrv"),"controller");
c->addFullfillment("AuvCont::WorldXYZPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("Structure::Alignment");
c->addChild(pool->getComponent("StructureServoing::Alignment"),"detector");
c->addChild(pool->getComponent("HsvMosaicing::Task"),"mosaic");
c->addChild(pool->getComponent("ImagePreprocessing::HSVSegmentationAndBlur"),"seg");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addFullfillment("Structure::Alignment");
c->addFullfillment("Base::WorldXYVelocityControllerSrv");




c->addFullfillment("Base::WorldXYVelocityControllerSrv");








}
{
auto c = new Composition("AuvCont::ConstantCommandGroundAvoidanceCmp");
c->addChild(pool->getComponent("AuvControl::ConstantCommandGroundAvoidance"),"main");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"altimeter");
c->addChild(pool->getComponent("Base::ZProviderSrv"),"depth");
c->addFullfillment("AuvCont::ConstantCommandGroundAvoidanceCmp");









}
{
auto c = new Composition("Structure::Detector");
c->addChild(pool->getComponent("StructureServoing::Task"),"detector");
c->addChild(pool->getComponent("HsvMosaicing::Task"),"mosaic");
c->addChild(pool->getComponent("ImagePreprocessing::HSVSegmentationAndBlur"),"seg");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"camera");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"ori");
c->addFullfillment("Structure::Detector");
c->addFullfillment("Base::WorldXYVelocityControllerSrv");




c->addFullfillment("Base::WorldXYVelocityControllerSrv");








}
{
auto c = new Composition("Structure::SonarStructureServoingComp");
c->addChild(pool->getComponent("SonarStructureServoing::Task"),"detector");
c->addChild(pool->getComponent("Base::SonarScanProviderSrv"),"sonar");
c->addChild(pool->getComponent("SonarFeatureEstimator::Task"),"sonar_estimator");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose_blind");
c->addFullfillment("Structure::SonarStructureServoingComp");
c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");
c->addFullfillment("Base::WorldXYPositionControllerSrv");




c->addFullfillment("Base::AUVRelativeMotionControllerSrv");
c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::ControllerSrv");

c->addFullfillment("Base::WorldXYPositionControllerSrv");








}
{
auto c = new Composition("Structure::StructureReconstructionComp");
c->addChild(pool->getComponent("StructureReconstruction::Task"),"image_saver");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"front_camera");
c->addChild(pool->getComponent("Base::ImageProviderSrv"),"bottom_camera");
c->addFullfillment("Structure::StructureReconstructionComp");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::AUVRelativeMotionControllerSrv), controlled_system.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::ControllerNewCmp");
c->addChild(pool->getComponent("Buoy::ServoingOnWall"),"main");
c->addChild(pool->getComponent("WallServoing::WallOrientationSrv"),"wall");
c->addChild(pool->getComponent("Base::OrientationSrv"),"pose");
c->addChild(pool->getComponent("Buoy::DetectorNewCmp"),"detector");
c->addFullfillment("Buoy::ControllerNewCmp");
c->addFullfillment("Base::WorldXYZPositionControllerSrv");




c->addFullfillment("Base::WorldXYZPositionControllerSrv");








}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("PoseAuv::InitialOrientationEstimatorCmp");
c->addChild(pool->getComponent("WallOrientationCorrection::Task"),"wall_estimation");
c->addChild(pool->getComponent("OrientationEstimator::BaseEstimator"),"estimator");
c->addChild(pool->getComponent("XsensImu::Task"),"imu");
c->addChild(pool->getComponent("FogKvh::Dsp3000Task"),"fog");
c->addChild(pool->getComponent("Base::SonarScanProviderSrv"),"sonar");
c->addChild(pool->getComponent("SonarFeatureEstimator::Task"),"sonar_estimator");
c->addChild(pool->getComponent("PoseAuv::IKFOrientationEstimatorCmp"),"slave");
c->addFullfillment("PoseAuv::InitialOrientationEstimatorCmp");









}
{
auto c = new Composition("ConstantWorldXYVelocityCommand");
c->addChild(pool->getComponent("AuvControl::ConstantCommand"),"controller_w");
c->addChild(pool->getComponent("ConsWA"),"controller_v");
c->addFullfillment("ConstantWorldXYVelocityCommand");
c->addFullfillment("Base::WorldXYVelocityControllerSrv");




c->addFullfillment("Base::WorldXYVelocityControllerSrv");








}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::MotionControlTask"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"pose");
c->addChild(pool->getComponent("Base::GroundDistanceSrv"),"dist");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(AvalonControl::MotionControlTask)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(AuvRelPosController::Task)]");
c->addChild(pool->getComponent("AuvRelPosController::Task"),"controller");
c->addChild(pool->getComponent("Base::OrientationWithZSrv"),"orientation_with_z");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(AuvRelPosController::Task)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addChild(pool->getComponent("AvalonControl::PositionControlTask"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(AvalonControl::PositionControlTask)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::RawCommandControllerSrv), controlled_system.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::RawCommandControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::RawCommandControlledSystemSrv)]");
c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::RawCommandControlledSystemSrv");
c->addFullfillment("Base::RawCommandCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::RawCommandCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVRelativeMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::AUVRelativeMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVRelativeMotionControlledSystemSrv");
c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVRelativeMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::AUVMotionControllerSrv), controlled_system.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::AUVMotionControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::AUVMotionControlledSystemSrv)]");
c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::AUVMotionControlledSystemSrv");
c->addFullfillment("Base::AUVMotionCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::AUVMotionCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Wall::Follower/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Wall::Detector"),"controller_local");
c->addFullfillment("Wall::Follower/[controller.is_a?(Base::JointsControllerSrv), controlled_system.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Wall::Follower");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp/[controller.is_a?(Base::JointsControlledSystemSrv)]");
c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::JointsControlledSystemSrv");
c->addFullfillment("Base::JointsStatusSrv");
c->addFullfillment("Base::JointsCommandConsumerSrv");
c->addFullfillment("Base::ControlledSystemSrv");

c->addFullfillment("Base::JointsStatusSrv");

c->addFullfillment("Base::JointsCommandConsumerSrv");

c->addFullfillment("Base::ControlledSystemSrv");


c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::FollowerCmp");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller");
c->addChild(pool->getComponent("Base::ControlledSystemSrv"),"controlled_system");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"controller_local");
c->addFullfillment("Buoy::FollowerCmp");
c->addFullfillment("Base::ControlLoop");



c->addFullfillment("Base::ControlLoop");









}
{
auto c = new Composition("Buoy::DoubleBuoyCmp");
c->addChild(pool->getComponent("Base::MapSrv"),"main");
c->addChild(pool->getComponent("Buoy::DetectorCmp"),"orange");
c->addChild(pool->getComponent("Buoy::DetectorCmp2"),"white");
c->addFullfillment("Buoy::DoubleBuoyCmp");









}
{
auto c = new Composition("AuvCont::StructureCmp");
c->addChild(pool->getComponent("Base::WorldXYVelocityControllerSrv"),"main");
c->addChild(pool->getComponent("Base::WorldXYVelocityControllerSrv"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addFullfillment("AuvCont::StructureCmp");
c->addFullfillment("AuvCont::WorldXYVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("AuvCont::WorldXYVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("AuvCont::MoveCmp");
c->addChild(pool->getComponent("ConstantWorldXYVelocityCommand"),"command");
c->addChild(pool->getComponent("ConstantWorldXYVelocityCommand"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addFullfillment("AuvCont::MoveCmp");
c->addFullfillment("AuvCont::WorldXYVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("AuvCont::WorldXYVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("AuvCont::PositionMoveCmp");
c->addChild(pool->getComponent("AuvControl::ConstantCommand"),"command");
c->addChild(pool->getComponent("AuvControl::ConstantCommand"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addFullfillment("AuvCont::PositionMoveCmp");
c->addFullfillment("AuvCont::WorldPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");
c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");




c->addFullfillment("AuvCont::WorldPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");
c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");




c->addFullfillment("Base::JointsCommandSrv");

c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");








}
{
auto c = new Composition("AuvCont::Trajectory");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"main");
c->addChild(pool->getComponent("AvalonControl::TrajectoryFollower"),"controller");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addFullfillment("AuvCont::Trajectory");
c->addFullfillment("AuvCont::WorldPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");
c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");




c->addFullfillment("AuvCont::WorldPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");
c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");




c->addFullfillment("Base::JointsCommandSrv");

c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");








}
{
auto c = new Composition("AuvCont::WorldYPositionXVelocityCmp");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("Base::WorldYPositionXVelocityControllerSrv"),"controller");
c->addFullfillment("AuvCont::WorldYPositionXVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("AuvCont::WorldXYPositionCmp");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("Base::WorldXYPositionControllerSrv"),"controller");
c->addFullfillment("AuvCont::WorldXYPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("AuvCont::WorldXYVelocityCmp");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("Base::WorldXYVelocityControllerSrv"),"controller");
c->addFullfillment("AuvCont::WorldXYVelocityCmp");
c->addFullfillment("Base::JointsCommandSrv");




c->addFullfillment("Base::JointsCommandSrv");








}
{
auto c = new Composition("AuvCont::WorldPositionCmp");
c->addChild(pool->getComponent("Base::JointsControlledSystemSrv"),"joint");
c->addChild(pool->getComponent("Base::PoseSrv"),"pose");
c->addChild(pool->getComponent("AuvCont::ConstantCommandGroundAvoidanceCmp"),"avoid");
c->addChild(pool->getComponent("AuvControl::WorldToAligned"),"world_to_aligned");
c->addChild(pool->getComponent("AuvControl::OptimalHeadingController"),"optimal_heading_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_position_controller");
c->addChild(pool->getComponent("AuvControl::PIDController"),"aligned_velocity_controller");
c->addChild(pool->getComponent("AuvControl::AlignedToBody"),"aligned_to_body");
c->addChild(pool->getComponent("AuvControl::AccelerationController"),"acceleration_controller");
c->addChild(pool->getComponent("Base::WorldXYZRollPitchYawControllerSrv"),"controller");
c->addFullfillment("AuvCont::WorldPositionCmp");
c->addFullfillment("Base::JointsCommandSrv");
c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");




c->addFullfillment("Base::JointsCommandSrv");

c->addFullfillment("Base::WorldXYZRollPitchYawControlledSystemSrv");








}
return "";
}
