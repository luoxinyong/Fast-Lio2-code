#include <iostream>
#include <math.h>
using namespace std; 

#include <Eigen/Core>
#include "sophus/so3.h"
#include "sophus/se3.h"

int main( int argc, char** argv )
{
    Eigen::Vector3d fai1(0.01,0.02,-0.03);  // 旋转小量==就是李代数
    Eigen::Vector3d fai2(1.1,-1.2,1.3);

    // --------- 开始你的代码	---------------//
    // 获取两个旋转量的指数映射
    Sophus::SO3 fai1_1 = Sophus::SO3::exp(fai1.transpose());//指数映射完就是旋转矩阵
    Sophus::SO3 fai2_2 = Sophus::SO3::exp(fai2.transpose());
    double theta = fai2.transpose().norm();//旋转向量求模长就是角度
    Eigen::Vector3d fai = fai2.transpose()/theta;//旋转向量除以向量就是单位长度了
    Eigen::Matrix3d jl_inv;
    theta = theta/2;
    //BCH近似，用百度到的tan（pi/2-x）代替cot（）
    jl_inv = theta*tan(M_PI/2-theta)*Eigen::Matrix3d::Identity()+(1-theta*tan(M_PI/2-theta))*fai*fai.transpose()-theta*Sophus::SO3::hat(fai);

    std::cout << "jl_inv:" << jl_inv << std::endl<< std::endl;

    Eigen::Matrix3d RA;
    Sophus::SO3 f1f2 = fai1_1*fai2_2;
    RA = f1f2.matrix();
    std::cout << "sophus:" << RA << std::endl<< std::endl;

    Eigen::Matrix3d RB;
    Sophus::SO3 RB_1 =  Sophus::SO3::exp(jl_inv*fai1+fai2);
    RB = RB_1.matrix();
    std::cout << "bch:" << RB << std::endl<< std::endl;

    
    Eigen::Matrix3d RC;
    RC = Sophus::SO3::exp(fai1+fai2).matrix();
    std::cout << "wrong:" << RC << std::endl<< std::endl;

    // --------- 结束你的代码	---------------//
    return 0;
}


