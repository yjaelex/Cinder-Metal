//
//  RendererMetalImpl.h
//  MetalCube
//
//  Created by William Lindmeier on 10/11/15.
//
//

#pragma once

#include <Metal/Metal.h>
#include "RendererMetal.h"
#include "CommandBuffer.h"
#import <QuartzCore/CAMetalLayer.h>

@interface RendererMetalImpl : NSObject
{
    BOOL mLayerSizeDidUpdate;
    cinder::app::RendererMetal  *mRenderer;
#if defined( CINDER_MAC )
    NSView  *mCinderView;
#elif defined( CINDER_COCOA_TOUCH )
    UIView  *mCinderView;
#endif
}

@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;
@property (nonatomic, strong) id <MTLLibrary> library;
@property (nonatomic, strong) CAMetalLayer *metalLayer;
@property (nonatomic, strong) id <CAMetalDrawable> currentDrawable; // Set by RenderBuffer, when the command buffer is committed

+ (instancetype)sharedRenderer;
#if defined( CINDER_MAC )
- (instancetype)initWithFrame:(CGRect)frame
                   cinderView:(NSView *)cinderView
                     renderer:(cinder::app::RendererMetal *)renderer
                      options:(cinder::app::RendererMetal::Options &)options;
#elif defined( CINDER_COCOA_TOUCH )
- (instancetype)initWithFrame:(CGRect)frame
                   cinderView:(UIView *)cinderView
                     renderer:(cinder::app::RendererMetal *)renderer
                      options:(cinder::app::RendererMetal::Options &)options;
#endif
- (void)setFrameSize:(CGSize)newSize;

- (void)startDraw;
- (void)finishDraw;
- (dispatch_semaphore_t)inflightSemaphore;

@end
