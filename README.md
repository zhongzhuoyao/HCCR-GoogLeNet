### High Performance Offline Handwritten Chinese Character Recognition Using GoogLeNet and Feature Maps

by Zhuoyao Zhong, Lianwen Jin, Zecheng Xie, South China University of Technology (SCUT), Published in ICDAR 2015.

### Details of our paper

* We designed a deep, powerful but with less parameters convolutional neural network, nemaly HCCR-GoogLeNet, for offline handwritten Chinese character recognition
* We were the first to propose to incorporate directional features (e.g., Gabor, HoG and gradient feature) as domain knowledge into deep convolutional neural network to boost performance on offline HCCR
* Our single HCCR-GoogLeNet was superior to all previous best single and ensemble CNN models in terms of both accuracy and storage performance on the ICDAR 2013 offline HCCR competition dataset. Our ensemble HCCR-GoogLeNet models achieved a better recognition result of 96.74%.

### Introduction of this repository
This repository is the source codes on our paper, inculding the prototxt file of HCCR-GoogLeNet CNN architecture definition for caffe framework and codes for directional feature extraction. For more information, please refer to our paper: http://arxiv.org/abs/1505.04925.

### Citing HCCR-GoogLeNet

If our codes are useful for your work, please cite our paper:
```
@inproceedings{HCCR-GoogLeNet, 
		title = {High Performance Offline Handwritten Chinese Character Recognition Using GoogLeNet and Feature Maps}, 
		author = {Zhuoyao Zhong, Lianwen Jin, Zecheng Xie}, 
		booktitle = {International Conference on Document Analysis and Recognition ({ICDAR})}}, 
		year = {2015} 
}
```
