//
//  ViewController.m
//  DemoForYe
//
//  Created by Ancc on 14/12/19.
//  Copyright (c) 2014年 Ancc. All rights reserved.
//

#import "ViewController.h"
#import "UIView+AutoLayout.h"

@interface ViewController ()<UIScrollViewDelegate>
@property (nonatomic,strong)UIScrollView *rootScrollView;
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    //主视图
    UIScrollView *scrollView    =   [[UIScrollView alloc]initWithFrame:self.view.frame];
    scrollView.backgroundColor  =   [UIColor whiteColor];
    scrollView.delegate=self;
    [self.view addSubview:self.rootScrollView=scrollView];
    
    //定义一些参数
    NSInteger v_count           =   10;
    NSMutableArray *subViews    =   [NSMutableArray new];
    CGFloat subViewWidth        =   scrollView.frame.size.width/6.5;
    CGFloat subViewHeight       =   scrollView.frame.size.height;
    scrollView.contentSize      =   CGSizeMake(MAX(subViewWidth * v_count, scrollView.frame.size.width+1), 1);
    //获取十个随机数
    while (subViews.count < v_count)
    {
        UIButton *subView = [[UIButton alloc]initWithFrame:CGRectMake(subViews.count*subViewWidth, 0, subViewWidth, subViewHeight)];
        [subView addTarget:self action:@selector(buttonEvent:) forControlEvents:UIControlEventTouchUpInside];
        [scrollView addSubview:subView];
        //给子界面增加约束
        {
            //            [subView autoSetDimensionsToSize:CGSizeMake(subViewWidth, subViewHeight)];
            //            if(subViews.lastObject)
            //            {
            //                NSLog(@"%d",[subViews.lastObject tag]);
            //                [subView autoPinEdge:ALEdgeLeft toEdge:ALEdgeRight ofView:subViews.lastObject];
            //            }else{
            //                [subView autoPinEdgeToSuperviewEdge:ALEdgeLeft withInset:0];
            //            }
            //            [subView autoPinEdgeToSuperviewEdge:ALEdgeTop withInset:0];
            //            [subView autoPinEdgeToSuperviewEdge:ALEdgeBottom withInset:0];
            //            subView.tag=subViews.count;
            [subViews addObject:subView];
        }
        //一定比例的进度条
        {
            UIView *progressView        =   [[UIView alloc]init];
            progressView.backgroundColor=   [[UIColor blueColor]colorWithAlphaComponent:arc4random_uniform(10)*.1+.1];//增加背景色值/不为0
            progressView.userInteractionEnabled=NO;
            [subView addSubview:progressView];
            //进度条view增加约束
            {
                CGFloat value             =   arc4random_uniform(10)*.1+.1;
                [progressView autoPinEdgeToSuperviewEdge:ALEdgeBottom withInset:0];
                [progressView autoPinEdgeToSuperviewEdge:ALEdgeLeft withInset:0];
                [progressView autoMatchDimension:ALDimensionWidth toDimension:ALDimensionWidth ofView:progressView.superview];
                [progressView autoMatchDimension:ALDimensionHeight toDimension:ALDimensionHeight ofView:progressView.superview withMultiplier:value];
            }
        }
        
    }
    
}
-(void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    NSLog(@"%@",NSStringFromCGPoint(scrollView.contentOffset));
}
/**
 *  @author Anccccccc, 14-12-19 10:12:19
 *
 *  核心滑动距离计算,上面的其他代码都不重要
 *
 *  @param but 当前触发了点击事件的button
 */
-(void)buttonEvent:(UIButton *)but
{
    NSLog(@"%@",NSStringFromSelector(_cmd));
    //计算but在滑动视图上的位置,虽然在这个demo里面but是滑动视图的直接子视图,但实际情况要负责的多;使用相对位置获取,在比较复杂的界面中也能很好的容错
    CGRect rect     =   [but convertRect:CGRectZero toView:self.rootScrollView];
    //计算当前滑动视图的位置
    CGPoint p       =   CGPointMake(rect.origin.x-self.rootScrollView.frame.size.width/2.+but.frame.size.width/2., 0);
    __weak typeof(ViewController) *bself = self;
    [UIView animateWithDuration:.35 animations:^{
        bself.rootScrollView.contentOffset = p;
    }];
}
@end


