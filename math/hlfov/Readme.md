# HL的图像裁剪比例

![示例图](/hlfov/image/1280X1280.PNG)

假设原始图像为4:3长宽比，α为图像旋转的角度；
β = arctan（4/3）= 53.13
则图像旋转53.13°以内时，从画面中裁剪出相同长宽比，且无暗角的内接矩形的尺寸计算：
(a'^2 + b'^2)^0.5 = a / (cos(β-α))    
(a'^2 + (a'*4/3)'^2)^0.5 = a / (cos(53.13-α))
a'/a = 1/(1.67*cos(53.13-α)) 

假设画面的最大旋转为20°时，画面的裁剪比例为：0.715