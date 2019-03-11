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
@end

@implementation MixViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.view.backgroundColor = [UIColor whiteColor];
    
    AVAudioPlayerNode* player = [[AVAudioPlayerNode alloc]init];
    [player scheduleFile:self.file atTime:nil completionHandler:nil];

    [self.engine  attachNode:player];
    [self.engine connect:player to:self.engine.mainMixerNode format:self.file.fileFormat];
    NSError* error;
    [self.engine startAndReturnError:&error];
    if (error) {
        NSLog(@"error = %@",error.localizedDescription);
    }
    


}

-(AVAudioEngine*)engine {
    if (!_engine) {
        _engine = [[AVAudioEngine alloc]init];
    }
    return _engine;
}

-(AVAudioFile*)file {
    if (!_file) {
        NSError* error;
        NSString* file = [[NSBundle mainBundle]pathForResource:@"雨宮天 - Skyreach" ofType:@"mp3"];
        _file = [[AVAudioFile alloc]initForReading:[NSURL fileURLWithPath:file] error:&error];
        
    }
    return _file;
}

@end
