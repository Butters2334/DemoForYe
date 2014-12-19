//
//  UIView+AutoLayout.h
//  v2.0.0
//  https://github.com/smileyborg/UIView-AutoLayout
//
//  Copyright (c) 2012 Richard Turton
//  Copyright (c) 2013 Tyler Fox
//
//  2014-12-10 添加中文注释(谷歌直译,后续再详细翻译)
//             该分类可以代码实现AutoLayout
//
//  This code is distributed under the terms and conditions of the MIT license.
//  此代码是在MIT许可的条款和条件分布。
//
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to
//  deal in the Software without restriction, including without limitation the
//  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
//  sell copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  特此授权，免费的，任何人获取一份副本本软件和相关文档文件（“软件”），要处理软件不受任何限制，
//  包括但不限于有权使用，复制，修改，合并，发布，分发，再许可和/或销售软件的副本，并允许个人向
//  谁软件是布置这样做，符合以下条件：
//
//  The above copyright notice and this permission notice shall be included in
//  all copies or substantial portions of the Software.
//  上述版权声明和本许可声明应包括在所有副本或实质性部分的软件。
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
//  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//  IN THE SOFTWARE.
//  软件提供“AS IS”，不附带任何明示或默示的担保，包括但不限于适销性，适用于某一特定用途和不侵权。
//  在任何情况下，作者或版权所有者对任何索赔，损坏或其他责任，无论是因执行合同，侵权还是其他原因，
//  FROM，OUT或IN连接与软件或使用或其他交易在软件中。
//

#import <UIKit/UIKit.h>

//#pragma mark ALAttributes
#pragma mark 属性

typedef NS_ENUM(NSInteger, ALEdge) {
    ALEdgeLeft = NSLayoutAttributeLeft,             // the left edge of the view//左对齐
    ALEdgeRight = NSLayoutAttributeRight,           // the right edge of the view//右对齐
    ALEdgeTop = NSLayoutAttributeTop,               // the top edge of the view//上边对齐
    ALEdgeBottom = NSLayoutAttributeBottom,         // the bottom edge of the view//下对齐
    ALEdgeLeading = NSLayoutAttributeLeading,       // the leading edge of the view (left edge for left-to-right languages like English, right edge for right-to-left languages like Arabic)//englist从左到右,阿拉伯从右到左
    ALEdgeTrailing = NSLayoutAttributeTrailing      // the trailing edge of the view (right edge for left-to-right languages like English, left edge for right-to-left languages like Arabic)//englist从右到左,阿拉伯从左到右
};

typedef NS_ENUM(NSInteger, ALDimension) {
    ALDimensionWidth = NSLayoutAttributeWidth,      // the width of the view//从一个视图获取宽度
    ALDimensionHeight = NSLayoutAttributeHeight     // the height of the view//从一个视图获取高度
};

typedef NS_ENUM(NSInteger, ALAxis) {
    ALAxisVertical = NSLayoutAttributeCenterX,      // a vertical line through the center of the view//center_X对齐
    ALAxisHorizontal = NSLayoutAttributeCenterY,    // a horizontal line through the center of the view//center_Y对齐
    ALAxisBaseline = NSLayoutAttributeBaseline      // a horizontal line at the text baseline (not applicable to all views)//一个水平线的文本基线（并不适用于所有的意见）//不知道是什么意思
};

typedef void(^ALConstraintsBlock)(void);    // a block of method calls to the UIView+AutoLayout category API//一个普通的回调方法,


//#pragma mark - UIView+AutoLayout
#pragma mark 初始化
/**
 代码自动化布局
    A category on UIView that provides a simple yet powerful interface for creating Auto Layout constraints.//UIView的子类，提供了一个简单而强大的界面，用于创建自动布局的限制。
 */
@interface UIView (AutoLayout)


//#pragma mark Factory & Initializer Methods

/** 
    创建一个不允许autoresizing的view,用于autolayout约束(类方法)
        Creates and returns a new view that does not convert the autoresizing mask into constraints.
 */
+ (instancetype)newAutoLayoutView;

/**
 创建一个不允许autoresizing的view,用于autolayout约束
    Initializes and returns a new view that does not convert the autoresizing mask into constraints.
 */
- (instancetype)initForAutoLayout;


//#pragma mark Set Constraint Priority
#pragma mark 约束优先(根据约束优先级)
/**
 设置有特殊优先级的约束条件,执行代码块
    Sets the constraint priority to the given value for all constraints created using the UIView+AutoLayout category API within the given constraints block.
    NOTE: This method will have no effect (and will NOT set the priority) on constraints created or added using the SDK directly within the block! 
 */
+ (void)autoSetPriority:(UILayoutPriority)priority forConstraints:(ALConstraintsBlock)block;


//#pragma mark Remove Constraints
#pragma mark 移除约束条件
/** 
    移除约束条件
        Removes the given constraint from the view it has been added to.
 */
+ (void)autoRemoveConstraint:(NSLayoutConstraint *)constraint;

/** 
    批量移除约束条件
        Removes the given constraints from the views they have been added to.
 */
+ (void)autoRemoveConstraints:(NSArray *)constraints;

/** 
    移除视图的所有约束
    警告：该函数不能用于大规模约束优化的去除;使用这种方法后，你可能会遇到重大的性能问题。
    注：该函数会保留隐含的约束，如内在的内容大小的限制，您通常不希望删除 。
 
    Removes all explicit constraints that affect the view.
    WARNING: Apple's constraint solver is not optimized for large-scale constraint removal; you may encounter major performance issues after using this method.
    NOTE: This method preserves implicit constraints, such as intrinsic content size constraints, which you usually do not want to remove.
 */
- (void)autoRemoveConstraintsAffectingView;

/** 
    移除视图的所有约束(可选择是否移除隐含的约束)
    警告：该函数不能用于大规模约束优化的去除;使用这种方法后，你可能会遇到重大的性能问题。
    注：隐式约束是自动生成的低优先级的限制，你通常不希望删除这些。(多次提示不应该移除隐含约束,可能确实很重要)
 
    Removes all constraints that affect the view, optionally including implicit constraints.
    WARNING: Apple's constraint solver is not optimized for large-scale constraint removal; you may encounter major performance issues after using this method.
    NOTE: Implicit constraints are auto-generated lower priority constraints, and you usually do not want to remove these.
 */
- (void)autoRemoveConstraintsAffectingViewIncludingImplicitConstraints:(BOOL)shouldRemoveImplicitConstraints;

/** 
    移除视图及子视图的所有约束(这里标明了Recursively递归,不单单是当前视图的子视图,还包括所有的下级视图,该函数慎用)
    警告：该函数不能用于大规模约束优化的去除;使用这种方法后，你可能会遇到重大的性能问题。
    注：该函数会保留隐含的约束，如内在的内容大小的限制，您通常不希望删除 。
 
    Recursively removes all explicit constraints that affect the view and its subviews.
    WARNING: Apple's constraint solver is not optimized for large-scale constraint removal; you may encounter major performance issues after using this method.
    NOTE: This method preserves implicit constraints, such as intrinsic content size constraints, which you usually do not want to remove.
 */
- (void)autoRemoveConstraintsAffectingViewAndSubviews;

/**
    移除视图及子视图的所有约束(可选择是否移除隐含的约束)(所有的子视图,递归向下)
    警告：该函数不能用于大规模约束优化的去除;使用这种方法后，你可能会遇到重大的性能问题。
    注：隐式约束是自动生成的低优先级的限制，你通常不希望删除这些。(多次提示不应该移除隐含约束,可能确实很重要)
 
    Recursively removes all constraints from the view and its subviews, optionally including implicit constraints.
    WARNING: Apple's constraint solver is not optimized for large-scale constraint removal; you may encounter major performance issues after using this method.
    NOTE: Implicit constraints are auto-generated lower priority constraints, and you usually do not want to remove these.
 */
- (void)autoRemoveConstraintsAffectingViewAndSubviewsIncludingImplicitConstraints:(BOOL)shouldRemoveImplicitConstraints;


//#pragma mark Center in Superview
#pragma mark 与父级界面中心对齐
/** 
    约束条件-与父级视图中心对齐(垂直+水平)
    Centers the view in its superview.
 */
- (NSArray *)autoCenterInSuperview;

/** 
    约束条件-与父级视图根据axis条件对齐
    ALAxis:centerX对齐,centerY对齐,Baseline对齐
    Aligns the view to the same axis of its superview.
 */
- (NSLayoutConstraint *)autoAlignAxisToSuperviewAxis:(ALAxis)axis;


//#pragma mark Pin Edges to Superview
#pragma mark 与父级界面边缘对齐(可以设置间距)

/** 
    约束条件-设置有一定间距的边缘对齐
    Pins the given edge of the view to the same edge of the superview with an inset.
 */
- (NSLayoutConstraint *)autoPinEdgeToSuperviewEdge:(ALEdge)edge withInset:(CGFloat)inset;

/** 
    约束条件-设置有一定间距的边缘对齐,可以设置对齐标准(大于,等于,小于)
    Pins the given edge of the view to the same edge of the superview with an inset as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoPinEdgeToSuperviewEdge:(ALEdge)edge withInset:(CGFloat)inset relation:(NSLayoutRelation)relation;

/** 
    根据insets设置四个方向的对齐参数
    Pins the edges of the view to the edges of its superview with the given edge insets.
 */
- (NSArray *)autoPinEdgesToSuperviewEdgesWithInsets:(UIEdgeInsets)insets;

/** 
    根据insets设置四个方向的对齐参数,但是不设置edge对应的方向(即将除了edge之外的三个对齐参数都设置成insets中对应的值)
    Pins 3 of the 4 edges of the view to the edges of its superview with the given edge insets, excluding one edge. 
 */
- (NSArray *)autoPinEdgesToSuperviewEdgesWithInsets:(UIEdgeInsets)insets excludingEdge:(ALEdge)edge;


//#pragma mark Pin Edges
#pragma mark 间距约束-相对视图
/** 
    生成边缘对齐约束条件,获取peerView的toEdge的条件
    Pins an edge of the view to a given edge of another view.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView;

/**
    生成边缘对齐约束条件,获取peerView的toEdge的条件,但是间距值在原先的基础上偏移offset
    Pins an edge of the view to a given edge of another view with an offset.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/** 
    生成边缘对齐约束条件,获取peerView的toEdge的条件,但是间距值在原先的基础上偏移offset,对比条件为relation
    Pins an edge of the view to a given edge of another view with an offset as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoPinEdge:(ALEdge)edge toEdge:(ALEdge)toEdge ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;


//#pragma mark Align Axes
#pragma mark 设置水平对齐约束-相对视图
/** 
    生成一个水平对齐约束条件,从peerView获取条件
    Aligns an axis of the view to the same axis of another view.
 */
- (NSLayoutConstraint *)autoAlignAxis:(ALAxis)axis toSameAxisOfView:(UIView *)peerView;

/** 
    生成一个水平对齐约束条件,获取peerView的条件,但是间距值在原先的基础上偏移offset
    Aligns an axis of the view to the same axis of another view with an offset.
 */
- (NSLayoutConstraint *)autoAlignAxis:(ALAxis)axis toSameAxisOfView:(UIView *)peerView withOffset:(CGFloat)offset;


//#pragma mark Match Dimensions
#pragma mark 设置尺寸约束-相对视图
/** 
    生成一个尺寸约束,从peerView中获取
    Matches a dimension of the view to a given dimension of another view. 
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView;

/** 
    生成一个尺寸约束,从peerView中获取,并进行offset的偏移
    Matches a dimension of the view to a given dimension of another view with an offset.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/** 
    生成一个尺寸约束,从peerView中获取,但是间距值在原先的基础上偏移offset,对比条件为relation
    Matches a dimension of the view to a given dimension of another view with an offset as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;

/** 
    生成一个尺寸约束,约束值为peerView的尺寸约束值*multiplier
    Matches a dimension of the view to a multiple of a given dimension of another view.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier;

/** 
    生成一个尺寸约束,约束值为peerView的尺寸约束值*multiplier,对比条件为relation
    Matches a dimension of the view to a multiple of a given dimension of another view as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoMatchDimension:(ALDimension)dimension toDimension:(ALDimension)toDimension ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier relation:(NSLayoutRelation)relation;


//#pragma mark Set Dimensions
#pragma mark 设置尺寸约束-绝对值
/** 
    设置宽高两个约束条件
    Sets the view to a specific size.
 */
- (NSArray *)autoSetDimensionsToSize:(CGSize)size;

/** 
    设置宽高约束-设置具体约束值
    Sets the given dimension of the view to a specific size.
 */
- (NSLayoutConstraint *)autoSetDimension:(ALDimension)dimension toSize:(CGFloat)size;

/** 
    设置宽高约束-设置具体约束值,设置对比方式
    Sets the given dimension of the view to a specific size as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoSetDimension:(ALDimension)dimension toSize:(CGFloat)size relation:(NSLayoutRelation)relation;


#pragma mark Set Content Compression Resistance & Hugging

/** 
    未知
    Sets the priority of content compression resistance for an axis.
    NOTE: This method must only be called from within the block passed into the method +[UIView autoSetPriority:forConstraints:] 
 */
- (void)autoSetContentCompressionResistancePriorityForAxis:(ALAxis)axis;

/** 
    未知
    Sets the priority of content hugging for an axis.
    NOTE: This method must only be called from within the block passed into the method +[UIView autoSetPriority:forConstraints:] 
 */
- (void)autoSetContentHuggingPriorityForAxis:(ALAxis)axis;


//#pragma mark Constrain Any Attributes
#pragma mark 约束转换(从其他view获取约束值)
/** 
    设置任意约束(attribute)的约束值为peerView的toAttribute约束值
        (理论上这类函数是为了使用其他view的其他约束值来做相对约束;如果是为了设置其他view的约束值,可以使用其他简单一点的函数)
    Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view. 
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView;

/** 
    设置任意约束(attribute)的约束值为peerView的toAttribute约束值,但是间距值在原先的基础上偏移offset
        (理论上这类函数是为了使用其他view的其他约束值来做相对约束;如果是为了设置其他view的约束值,可以使用其他简单一点的函数)
    Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with an offset.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withOffset:(CGFloat)offset;

/**
    设置任意约束(attribute)的约束值为peerView的toAttribute约束值,但是间距值在原先的基础上偏移offset,对比条件为relation
    (理论上这类函数是为了使用其他view的其他约束值来做相对约束;如果是为了设置其他view的约束值,可以使用其他简单一点的函数)
    Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with an offset as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withOffset:(CGFloat)offset relation:(NSLayoutRelation)relation;

/** 
    设置任意约束(attribute)的约束值为peerView的toAttribute约束值,约束值为peerView的尺寸约束值*multiplier
    (理论上这类函数是为了使用其他view的其他约束值来做相对约束;如果是为了设置其他view的约束值,可以使用其他简单一点的函数)
    Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with a multiplier.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier;

/** 
    设置任意约束(attribute)的约束值为peerView的toAttribute约束值,约束值为peerView的尺寸约束值*multiplier,对比条件为relation
    (理论上这类函数是为了使用其他view的其他约束值来做相对约束;如果是为了设置其他view的约束值,可以使用其他简单一点的函数)
    Constrains an attribute (any ALEdge, ALAxis, or ALDimension) of the view to a given attribute of another view with a multiplier as a maximum or minimum.
 */
- (NSLayoutConstraint *)autoConstrainAttribute:(NSInteger)attribute toAttribute:(NSInteger)toAttribute ofView:(UIView *)peerView withMultiplier:(CGFloat)multiplier relation:(NSLayoutRelation)relation;


//#pragma mark Pin to Layout Guides
#pragma mark 基于vc的约束
/** 
    设置与vc的top间隔为10
    Pins the top edge of the view to the top layout guide of the given view controller with an inset.
 */
- (NSLayoutConstraint *)autoPinToTopLayoutGuideOfViewController:(UIViewController *)viewController withInset:(CGFloat)inset;

/** 
    设置与vc的bottom间隔为10
    Pins the bottom edge of the view to the bottom layout guide of the given view controller with an inset.
 */
- (NSLayoutConstraint *)autoPinToBottomLayoutGuideOfViewController:(UIViewController *)viewController withInset:(CGFloat)inset;

@end


//#pragma mark - NSArray+AutoLayout
#pragma mark 批量为view添加约束条件,数组中必须有至少两个view

/**
 A category on NSArray that provides a simple yet powerful interface for applying constraints to groups of views.
 */
@interface NSArray (AutoLayout)


//#pragma mark Constrain Multiple Views

/** 
    批量为view设置边距约束为上一个view的约束值(第一个不设置)
    Aligns views in this array to one another along a given edge.
 */
- (NSArray *)autoAlignViewsToEdge:(ALEdge)edge;

/** 
    批量为view设置对齐约束为上一个view的约束值(第一个不设置)
    Aligns views in this array to one another along a given axis.
 */
- (NSArray *)autoAlignViewsToAxis:(ALAxis)axis;

/**
    批量为view设置尺寸约束为上一个view的约束值(第一个不设置)
    Matches a given dimension of all the views in this array.
 */
- (NSArray *)autoMatchViewsDimension:(ALDimension)dimension;

/** 
    批量为view设置尺寸约束
    Sets the given dimension of all the views in this array to a given size.
 */
- (NSArray *)autoSetViewsDimension:(ALDimension)dimension toSize:(CGFloat)size;


//#pragma mark Distribute Multiple Views
#pragma mark 多视图设置(根据第一个或最后一个view的约束来渲染其他view)

/** 
   批量设置约束
 *  @param axis      水平对齐方式
 *  @param spacing   间隔
 *  @param alignment 对齐参照(暂时这么理解)
    Distributes the views in this array equally along the selected axis in their superview. Views will be the same size (variable) in the dimension along the axis and will have spacing (fixed) between them.
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSpacing:(CGFloat)spacing alignment:(NSLayoutFormatOptions)alignment;

/** 
 批量设置约束
 *  @param axis      水平对齐方式
 *  @param spacing   间隔
 *  @param shouldSpaceInsets   是否需要边缘间隔
 *  @param alignment 对齐参照(暂时这么理解)
    Distributes the views in this array equally along the selected axis in their superview. Views will be the same size (variable) in the dimension along the axis and will have spacing (fixed) between them, with optional insets from the first and last views to their superview.
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSpacing:(CGFloat)spacing insetSpacing:(BOOL)shouldSpaceInsets alignment:(NSLayoutFormatOptions)alignment;

/** 
    Distributes the views in this array equally along the selected axis in their superview. Views will be the same size (fixed) in the dimension along the axis and will have spacing (variable) between them. 
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSize:(CGFloat)size alignment:(NSLayoutFormatOptions)alignment;

/** 
    Distributes the views in this array equally along the selected axis in their superview. Views will be the same size (fixed) in the dimension along the axis and will have spacing (variable) between them, with optional insets from the first and last views to their superview. 
 */
- (NSArray *)autoDistributeViewsAlongAxis:(ALAxis)axis withFixedSize:(CGFloat)size insetSpacing:(BOOL)shouldSpaceInsets alignment:(NSLayoutFormatOptions)alignment;

@end


#pragma mark - NSLayoutConstraint+AutoLayout

/**
 A category on NSLayoutConstraint that allows constraints to be easily removed.
 */
@interface NSLayoutConstraint (AutoLayout)

/** Adds the constraint to the appropriate view. */
- (void)autoInstall;

/** Removes the constraint from the view it has been added to. */
- (void)autoRemove;

@end
