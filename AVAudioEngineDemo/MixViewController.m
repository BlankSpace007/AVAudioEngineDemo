//
//  MixViewController.m
//  AVAudioEngineDemo
//
//  Created by 李希朋 on 2019/3/11.
//  Copyright © 2019 李希朋. All rights reserved.
//

#import "MixViewController.h"
#import <AVFoundation/AVFoundation.h>
@interface MixViewController ()
@property(nonatomic, strong)AVAudioFile* file;
@property(nonatomic, strong)AVAudioEngine* engine;
@property(nonatomic, strong)AVAudioPlayerNode* player;
@property(nonatomic, strong)AVAudioEnvironmentNode* enviroment;
@property(nonatomic, strong)AVAudioUnitReverb* reverb;
@property(nonatomic, strong)AVAudioUnitEQ* eq;
@end

@implementation MixViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
//    [self initSession];
    UIButton* start = [UIButton buttonWithType:UIButtonTypeCustom];
    start.frame = CGRectMake(0, 0, 100, 100);
    [start setBackgroundColor:[UIColor blackColor]];
    [start addTarget:self action:@selector(startAction) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:start];
    
    _engine = [[AVAudioEngine alloc]init];
    self.view.backgroundColor = [UIColor whiteColor];
    
    _player = [[AVAudioPlayerNode alloc]init];
    _player.pan = 1;
//    self.player.renderingAlgorithm = AVAudio3DMixingRenderingAlgorithmHRTF;
//    self.player.obstruction = -10.0;
//    self.player.occlusion = -15.0;
//    self.player.position = AVAudioMake3DPoint(-2.0, 0.0, 115.0);
    AVAudioFormat *stereoFormat = [[AVAudioFormat alloc] initStandardFormatWithSampleRate:44100 channels:2];
    AVAudioUnitTimePitch* pitch = [[AVAudioUnitTimePitch alloc]init];
    pitch.rate = 1;
    pitch.pitch = 1000;
    [self.engine attachNode:self.enviroment];
    [self.engine attachNode:_player];
    [self.engine attachNode:self.reverb];
    [self.engine attachNode:self.eq];
    [self.engine attachNode:pitch];
//    [self.engine connect:_player to:self.engine.mainMixerNode format:[self.file processingFormat]];
//    [self.engine connect:self.enviroment to:self.engine.mainMixerNode format:stereoFormat];
    AVAudioConnectionPoint* p1 = [[AVAudioConnectionPoint alloc]initWithNode:self.eq bus:0];
    AVAudioConnectionPoint* p2 = [[AVAudioConnectionPoint alloc]initWithNode:self.reverb bus:0];
//    AVAudioConnectionPoint* p3 = [[AVAudioConnectionPoint alloc]initWithNode:pitch bus:0];
    [self.engine connect:self.player toConnectionPoints:@[p1,p2] fromBus:0 format:stereoFormat];
    [self.engine connect:self.eq to:self.engine.mainMixerNode fromBus:0 toBus:0 format:stereoFormat];
    [self.engine connect:self.reverb to:self.engine.mainMixerNode fromBus:0 toBus:0 format:stereoFormat];
    [self.engine connect:self.player to:pitch fromBus:1 toBus:1 format:stereoFormat];
    [self.engine connect:pitch to:self.engine.mainMixerNode fromBus:0 toBus:1 format:stereoFormat];
    
    
//    [self.engine connect:self.eq to:self.enviroment fromBus:0 toBus:0 format:stereoFormat];

}


-(AVAudioUnitReverb*)reverb {
    if (!_reverb) {
        _reverb = [[AVAudioUnitReverb alloc]init];
        [_reverb loadFactoryPreset:AVAudioUnitReverbPresetMediumHall];
        _reverb.wetDryMix = 100;
    }
    return _reverb;
}

-(AVAudioUnitEQ*)eq {
    if (!_eq) {
        _eq = [[AVAudioUnitEQ alloc]initWithNumberOfBands:1];
        
    }
    return _eq;
}

-(AVAudioEnvironmentNode*)enviroment {
    if (!_enviroment) {
        _enviroment = [[AVAudioEnvironmentNode alloc]init];
//        _enviroment.listenerPosition = AVAudioMake3DPoint(-50, 50, 10);
//        _enviroment.listenerAngularOrientation = AVAudioMake3DAngularOrientation(90, 0, 0);
//
//        AVAudioEnvironmentDistanceAttenuationParameters *dap =
//        _enviroment.distanceAttenuationParameters;
//        dap.distanceAttenuationModel = AVAudioEnvironmentDistanceAttenuationModelInverse;
//        dap.referenceDistance = 5.0;
//        dap.maximumDistance = 100.0;
//        dap.rolloffFactor = 1.0;
    }
    return _enviroment;
}

-(void)startAction {
    if(!_player.isPlaying) {
        NSError* error;
        [self.engine startAndReturnError:&error];
        if (error) {
            NSLog(@"error = %@",error.localizedDescription);
        }
        [self.player scheduleFile:self.file atTime:nil completionHandler:nil];
        [self.player play];
    }
}

//-(AVAudioEngine*)engine {
//    if (!_engine) {
//        _engine = [[AVAudioEngine alloc]init];
//    }
//    return _engine;
//}

-(AVAudioFile*)file {
    if (!_file) {
        
        NSError* error;
        NSString* file = [[NSBundle mainBundle]pathForResource:@"林俊杰 - 她说_1" ofType:@"mp3"];
//        AVAudioFormat* format = [[AVAudioFormat alloc]initStandardFormatWithSampleRate:44100 channels:1];
        _file = [[AVAudioFile alloc]initForReading:[NSURL fileURLWithPath:file]  error:&error];
        NSLog(@"fileFormat = %@",_file.fileFormat);
        NSLog(@"length = %lld",_file.length);
    }
    return _file;
}

@end
