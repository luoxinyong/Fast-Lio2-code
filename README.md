[Fast-Lio2-挑战赛代码.md](https://github.com/luoxinyong/Fast-Lio2-code/files/11919117/Fast-Lio2-.md)
# Fast-Lio2-code
包含有Fast-LIO2挑战赛的每一章代码
## 一、怎么样把代码通过git上传到Github仓库

参考博客：使用 git 命令行上传项目到 GitHub（以 R 包为例）创建仓库上传

## 二、第二次作业 用Sophus和Eigen库验证BCH公式
参考SLAM14讲推导公式：主要是左乘小量的Jr_inv推导
## 三、第四次作业

### （1）实现雷达数据的预处理 直通+体素滤波形式
不需要将时间戳单独处理，PCL库的fromROSmsg和toROSmsg都会将时间戳作为点云信息一同转换
### （2）利用IMU数据进行预积分操作，估计机器人位姿
丢弃第一帧数据，只保留其时间戳stamp方便后续数据计算dt进行处理
##四、第五次作业
跑通了avia和kitti数据集
