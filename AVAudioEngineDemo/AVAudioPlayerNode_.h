
typedef NS_OPTIONS(NSUInteger, AVAudioPlayerNodeBufferOptions) {
    AVAudioPlayerNodeBufferLoops            = 1UL << 0,        // 0x01
    AVAudioPlayerNodeBufferInterrupts        = 1UL << 1,        // 0x02
    AVAudioPlayerNodeBufferInterruptsAtLoop    = 1UL << 2        // 0x04
};


typedef NS_ENUM(NSInteger, AVAudioPlayerNodeCompletionCallbackType) {
    AVAudioPlayerNodeCompletionDataConsumed        = 0,
    AVAudioPlayerNodeCompletionDataRendered        = 1,
    AVAudioPlayerNodeCompletionDataPlayedBack    = 2,
};


typedef void (^AVAudioPlayerNodeCompletionHandler)(AVAudioPlayerNodeCompletionCallbackType callbackType) API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


OS_EXPORT API_AVAILABLE(macos(10.10), ios(8.0), watchos(2.0), tvos(9.0))
@interface AVAudioPlayerNode : AVAudioNode <AVAudioMixing>
//初始化
- (instancetype)init NS_DESIGNATED_INITIALIZER;


- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;


- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer atTime:(AVAudioTime * __nullable)when options:(AVAudioPlayerNodeBufferOptions)options completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;


- (void)scheduleBuffer:(AVAudioPCMBuffer *)buffer atTime:(AVAudioTime * __nullable)when options:(AVAudioPlayerNodeBufferOptions)options
completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


- (void)scheduleFile:(AVAudioFile *)file atTime:(AVAudioTime * __nullable)when completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;


- (void)scheduleFile:(AVAudioFile *)file atTime:(AVAudioTime * __nullable)when completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


- (void)scheduleSegment:(AVAudioFile *)file startingFrame:(AVAudioFramePosition)startFrame frameCount:(AVAudioFrameCount)numberFrames atTime:(AVAudioTime * __nullable)when completionHandler:(AVAudioNodeCompletionHandler __nullable)completionHandler;


- (void)scheduleSegment:(AVAudioFile *)file startingFrame:(AVAudioFramePosition)startFrame frameCount:(AVAudioFrameCount)numberFrames atTime:(AVAudioTime * __nullable)when
 completionCallbackType:(AVAudioPlayerNodeCompletionCallbackType)callbackType completionHandler:(AVAudioPlayerNodeCompletionHandler __nullable)completionHandler API_AVAILABLE(macos(10.13), ios(11.0), watchos(4.0), tvos(11.0));


- (void)stop;


- (void)prepareWithFrameCount:(AVAudioFrameCount)frameCount;


- (void)play;


- (void)playAtTime:(AVAudioTime * __nullable)when;


- (void)pause;


- (AVAudioTime * __nullable)nodeTimeForPlayerTime:(AVAudioTime *)playerTime;


- (AVAudioTime * __nullable)playerTimeForNodeTime:(AVAudioTime *)nodeTime;


@property(nonatomic, readonly, getter=isPlaying) BOOL playing;


@end

NS_ASSUME_NONNULL_END
