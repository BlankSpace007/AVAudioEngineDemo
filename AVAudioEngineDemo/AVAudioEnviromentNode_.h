typedef NS_ENUM(NSInteger, AVAudioEnvironmentDistanceAttenuationModel) {
    AVAudioEnvironmentDistanceAttenuationModelExponential   = 1,
    AVAudioEnvironmentDistanceAttenuationModelInverse       = 2,
    AVAudioEnvironmentDistanceAttenuationModelLinear        = 3
} NS_ENUM_AVAILABLE(10_10, 8_0);



OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEnvironmentDistanceAttenuationParameters : NSObject {

@property (nonatomic) AVAudioEnvironmentDistanceAttenuationModel distanceAttenuationModel;


@property (nonatomic) float referenceDistance;

@property (nonatomic) float maximumDistance;

@property (nonatomic) float rolloffFactor;

@end




OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEnvironmentReverbParameters : NSObject {



@property (nonatomic) BOOL enable;


@property (nonatomic) float level;

@property (nonatomic, readonly) AVAudioUnitEQFilterParameters *filterParameters;

- (void)loadFactoryReverbPreset:(AVAudioUnitReverbPreset)preset;

@end



OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), tvos(9.0)) API_UNAVAILABLE(watchos)
@interface AVAudioEnvironmentNode : AVAudioNode <AVAudioMixing>

- (instancetype)init NS_DESIGNATED_INITIALIZER;
//输出音量
@property (nonatomic) float outputVolume;

//下一个有效的总线
@property (nonatomic, readonly) AVAudioNodeBus nextAvailableInputBus;

// 设置听者在3d环境中的位置，坐标以米为单位，默认位置是（0，0，0）
@property (nonatomic) AVAudio3DPoint listenerPosition;

//听者在环境中的方向，改变listenerVectorOrientation将导致相应的listenerAngularOrientation更改。默认方向是侦听器直接沿着负Z轴查看。
@property (nonatomic) AVAudio3DVectorOrientation listenerVectorOrientation;


@property (nonatomic) AVAudio3DAngularOrientation listenerAngularOrientation;


@property (nonatomic, readonly) AVAudioEnvironmentDistanceAttenuationParameters *distanceAttenuationParameters;

@property (nonatomic, readonly) AVAudioEnvironmentReverbParameters *reverbParameters;


@property (nonatomic, readonly) NSArray<NSNumber *> *applicableRenderingAlgorithms;

@end


