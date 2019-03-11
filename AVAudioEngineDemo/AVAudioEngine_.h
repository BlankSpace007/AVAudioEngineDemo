// 错误的枚举
typedef NS_ENUM(OSStatus, AVAudioEngineManualRenderingError) {
    AVAudioEngineManualRenderingErrorInvalidMode = -80800,
    AVAudioEngineManualRenderingErrorInitialized = -80801,
    AVAudioEngineManualRenderingErrorNotRunning  = -80802
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 手动模式的状态
typedef NS_ENUM(NSInteger, AVAudioEngineManualRenderingStatus) {
    AVAudioEngineManualRenderingStatusError = -1,
    AVAudioEngineManualRenderingStatusSuccess = 0,
    AVAudioEngineManualRenderingStatusInsufficientDataFromInputNode = 1,
    AVAudioEngineManualRenderingStatusCannotDoInCurrentContext = 2
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 手动模式可选的2种模式
typedef NS_ENUM(NSInteger, AVAudioEngineManualRenderingMode) {
    AVAudioEngineManualRenderingModeOffline = 0,
    AVAudioEngineManualRenderingModeRealtime = 1
} API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


// 手动渲染的block
typedef AVAudioEngineManualRenderingStatus (^AVAudioEngineManualRenderingBlock)(AVAudioFrameCount numberOfFrames, AudioBufferList *outBuffer, OSStatus * __nullable outError) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioEngine : NSObject {
@private
    void *_impl;
}
// 初始化
- (instancetype)init;
// 让enginer拥有node的所有权
- (void)attachNode:(AVAudioNode *)node;
// 分离以前连接到engine的node。
- (void)detachNode:(AVAudioNode *)node;
// 链接node1和node2节点，并且从node1的bus1总线连接到node2的bus2总线
// 由于每个节点的输入总线和输出总线的个数是不唯一的，bus在这里标记了t总线
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 fromBus:(AVAudioNodeBus)bus1 toBus:(AVAudioNodeBus)bus2 format:(AVAudioFormat * __nullable)format;
// 这个方法作用和上个一样，只是没有传bus参数
// 这个方法适用于单线路的engine
- (void)connect:(AVAudioNode *)node1 to:(AVAudioNode *)node2 format:(AVAudioFormat * __nullable)format;
// 这个方法就厉害了，是一个节点sourceNode链接多个节点destNodes
//sourceBus指的是源节点sourceNode的输出总线
- (void)connect:(AVAudioNode *)sourceNode toConnectionPoints:(NSArray<AVAudioConnectionPoint *> *)destNodes fromBus:(AVAudioNodeBus)sourceBus format:(AVAudioFormat * __nullable)format API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));
// 这个方法和上面的方法相反，是断开node名为bus的输出节点
- (void)disconnectNodeInput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

// 这个方法是断开node节点的所有输出链接
// 如果n个节点nodes（输入节点）同时与node（输出节点）相连，那么你想同时断开他们的链接，那么这个方法比较合适
- (void)disconnectNodeInput:(AVAudioNode *)node;

// 是断开node名为bus的输入节点
- (void)disconnectNodeOutput:(AVAudioNode *)node bus:(AVAudioNodeBus)bus;

// 这个方法是断开node节点的所有输入链接
// 如果一个节点node（输入节点）同时与n个节点nodes（输出节点）相连，那么你想同时断开他们的链接，那么这个方法比较合适
- (void)disconnectNodeOutput:(AVAudioNode *)node;
// 此方法预先分配引擎启动所需的许多资源。它可以用来启动更有响应性。
- (void)prepare;

// engine 开始发动，返回YES，为成功，返回NO，为失败，失败可得到outError
- (BOOL)startAndReturnError:(NSError **)outError;

// engine 暂停，暂停引擎不会释放prepare分配的资源。通过再次调用start来恢复引擎。
- (void)pause;

// 重置所有节点
- (void)reset;

// engine 停止，停止引擎将释放prepare分配的资源。
- (void)stop;

// 通过node和输入bus获得AVAudioConnectionPoint
- (AVAudioConnectionPoint * __nullable)inputConnectionPointForNode:(AVAudioNode *)node inputBus:(AVAudioNodeBus)bus API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

// 通过node和输入bus获得AVAudioConnectionPoint，1对1或者1对多
- (NSArray<AVAudioConnectionPoint *> *)outputConnectionPointsForNode:(AVAudioNode *)node outputBus:(AVAudioNodeBus)bus API_AVAILABLE(macos(10.11), ios(9.0), watchos(2.0), tvos(9.0));

#if AVAUDIOENGINE_HAVE_MUSICPLAYER  播放音乐
// 播放音乐时，可以预加载musicSequence
@property (nonatomic, nullable) MusicSequence musicSequence;
#endif

// 输出节点
@property (readonly, nonatomic) AVAudioOutputNode *outputNode;

// 输入节点
@property (readonly, nonatomic) AVAudioInputNode *inputNode  API_AVAILABLE(macos(10.10), ios(8.0), watchos(4.0), tvos(11.0));


// 主混合节点
@property (readonly, nonatomic) AVAudioMixerNode *mainMixerNode;

// engine 是否正在运行
@property (readonly, nonatomic, getter=isRunning) BOOL running;

//
@property (nonatomic, getter=isAutoShutdownEnabled) BOOL autoShutdownEnabled API_AVAILABLE(macos(10.13), ios(11.0), tvos(11.0)) API_UNAVAILABLE(watchos);

#pragma mark -
#pragma mark Manual Rendering Mode  手动模式

//设置手动模式，可定义模式和参数，返回YES成功，返回NO失败
- (BOOL)enableManualRenderingMode:(AVAudioEngineManualRenderingMode)mode format:(AVAudioFormat *)pcmFormat maximumFrameCount:(AVAudioFrameCount)maximumFrameCount error:(NSError **)outError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 关闭手动模式
- (void)disableManualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


- (AVAudioEngineManualRenderingStatus)renderOffline:(AVAudioFrameCount)numberOfFrames toBuffer:(AVAudioPCMBuffer *)buffer error:(NSError **)outError API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0)) __attribute__((swift_error(nonnull_error)));


@property (readonly, nonatomic) AVAudioEngineManualRenderingBlock manualRenderingBlock API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 判断是否是手动模式
@property (readonly, nonatomic) BOOL isInManualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 手动模式（只读）
@property (readonly, nonatomic) AVAudioEngineManualRenderingMode manualRenderingMode API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 手动格式（只读）
@property (readonly, nonatomic) AVAudioFormat *manualRenderingFormat API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 手动帧数（只读）
@property (readonly, nonatomic) AVAudioFrameCount manualRenderingMaximumFrameCount API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

// 帧位置
@property (readonly, nonatomic) AVAudioFramePosition manualRenderingSampleTime API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));

#if AVAUDIOENGINE_HAVE_AUAUDIOUNIT
// 链接AVAudioUnitMIDIInstrument相关
- (void)connectMIDI:(AVAudioNode *)sourceNode to:(AVAudioNode *)destinationNode format:(AVAudioFormat * __nullable)format block:(AUMIDIOutputEventBlock __nullable)tapBlock API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// 链接AVAudioUnitMIDIInstrument相关
- (void)connectMIDI:(AVAudioNode *)sourceNode toNodes:(NSArray<AVAudioNode *> *)destinationNodes format:(AVAudioFormat * __nullable)format block:(AUMIDIOutputEventBlock __nullable)tapBlock API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// 断开AVAudioUnitMIDIInstrument相关
- (void)disconnectMIDI:(AVAudioNode *)sourceNode from:(AVAudioNode *)destinationNode API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// 断开AVAudioUnitMIDIInstrument相关
- (void)disconnectMIDI:(AVAudioNode *)sourceNode fromNodes:(NSArray<AVAudioNode *> *)destinationNodes API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// 断开AVAudioUnitMIDIInstrument相关
- (void)disconnectMIDIInput:(AVAudioNode *)node API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

// 断开AVAudioUnitMIDIInstrument相关
- (void)disconnectMIDIOutput:(AVAudioNode *)node API_AVAILABLE(macos(10.14), ios(12.0), watchos(5.0), tvos(12.0));

#endif // AVAUDIOENGINE_HAVE_AUAUDIOUNIT

@end // AVAudioEngine


AVF_EXPORT
NSString *const AVAudioEngineConfigurationChangeNotification API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0));

NS_ASSUME_NONNULL_END
