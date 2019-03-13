//
//  PlayerViewController.m
//  AVAudioEngineDemo
//
//  Created by drore on 2019/3/13.
//  Copyright © 2019 李希朋. All rights reserved.
//

#import "PlayerViewController.h"
#import <AVFoundation/AVFoundation.h>
@interface PlayerViewController ()

@property(nonatomic, strong)AVAudioEngine* engine;

@property(nonatomic, strong)AVAudioPlayerNode* player;

@property(nonatomic, strong)AVAudioFile* file;

@property (weak, nonatomic) IBOutlet UIButton *playButton;
@property (weak, nonatomic) IBOutlet UIButton *stopButton;
@property (weak, nonatomic) IBOutlet UILabel *lengthLabel;
@property (weak, nonatomic) IBOutlet UISlider *slider;

@end

@implementation PlayerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    [self.engine attachNode:self.player];
    [self.engine connect:self.player to:self.engine.outputNode format:[self.player outputFormatForBus:0]];
    NSError* error;
    BOOL isSuccess = [self.engine startAndReturnError:&error];
    if (error) {
        NSLog(@"error = %@",error.localizedDescription);
        return;
    }
    if (!isSuccess) {
        return;
    }
//    NSLog(@"file == %@",self.file.fileFormat);
//    NSLog(@"file == %@",self.file.processingFormat);
//    NSLog(@"file == %lld",self.file.length);
//    NSLog(@"file == %lld",self.file.framePosition);
    int second = self.file.length/self.file.processingFormat.sampleRate;

    _lengthLabel.text = [NSString stringWithFormat:@"%d:%d",second/60,second%60];
    

}
- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    NSLog(@"1111111");
}

#pragma mark - getter
-(AVAudioPlayerNode*)player {
    if (!_player) {
        _player = [[AVAudioPlayerNode alloc]init];
        
    }
    return _player;
}

-(AVAudioFile*)file {
    if (!_file) {
        NSString* file = [[NSBundle mainBundle]pathForResource:@"周杰伦-告白气球" ofType:@"mp3"];
        NSError* error;
        _file = [[AVAudioFile alloc]initForReading:[NSURL URLWithString:file] commonFormat:AVAudioPCMFormatInt16 interleaved:YES error:&error];
        
    }
    return _file;
}

-(AVAudioEngine*)engine {
    if (!_engine) {
        _engine = [[AVAudioEngine alloc]init];
        _engine.autoShutdownEnabled = YES;
        
    }
    return _engine;
}


#pragma mark - action
- (IBAction)stopAction:(id)sender {
    if (!self.player.isPlaying) {
        self.stopButton.enabled = false;
    } else {
        [self.player stop];
        self.playButton.selected = NO;
    }
}
- (IBAction)playAction:(id)sender {
    if (!self.player.isPlaying) {
//   除非SampleTime无效，否则就不要用hosTime
//        uint64_t hosTime = [AVAudioTime hostTimeForSeconds:2000];
//        AVAudioTime* time = [[AVAudioTime alloc]initWithHostTime:hosTime];
//        AVAudioTime* time = [[AVAudioTime alloc]initWithSampleTime:132300 atRate:44100];

//        [self.player scheduleFile:self.file atTime:time completionCallbackType:AVAudioPlayerNodeCompletionDataRendered completionHandler:^(AVAudioPlayerNodeCompletionCallbackType callbackType) {
//            NSLog(@"%lld",self.file.framePosition);
//        }];
        
        [self.player scheduleFile:self.file atTime:nil completionHandler:^{
            
        }];
        [self.player play];
    } else {
        self.stopButton.enabled = YES;
        [self.player pause];
    }
    self.playButton.selected = !self.playButton.selected;
}
- (IBAction)sliderChangeAction:(id)sender {
    
}

- (IBAction)sliderAction:(id)sender {
    UISlider* slider = sender;
    [self.player stop];
    NSLog(@"2222==%f",slider.value);
    AVAudioFrameCount startFrame = self.file.length* slider.value;
    AVAudioFrameCount remainingFrame = self.file.length*(1-slider.value);
    [self.player scheduleSegment:self.file startingFrame:startFrame frameCount:remainingFrame atTime:nil completionHandler:^{
        
    }];
    [self.player play];
}


@end
