# HCCR-GoogLeNet

========

This project is about HCCR-GoogLeNet CNN architecture definition and directional feature extraction. For more information, please see the paper: "Zhuoyao Zhong, Lianwen Jin, Zecheng Xie, High Performance Offline Handwritten Chinese Character Recognition Using GoogLeNet and Directional Feature Maps, ICDAR 2015”, http://arxiv.org/abs/1505.04925.

========

#Details

We present a new deep leaning model, HCCR-GoogLeNet, for the recognition of handwritten Chinese character. HCCR-GoogLeNet uses four Inception modules to construct an efficient deep network. The HCCR-GoogLeNet is designed very deeply yet slim, with total 19 layers (counting for all convolutional layers, pooling layers, fully connect layers and softmax output layer). We employ directional feature extraction domain knowledge, such as the Gabor feature and gradient feature, to enhance the performance of HCCR-GoogLeNet. Experiments on the ICDAR 2013 offline HCCR competition dataset show that our best single HCCR-GoogLeNet is superior to all previous best single and ensemble CNN models in terms of both accuracy and storage performance. The proposed single and ensemble HCCR-GoogLeNet models achieve new state of the art recognition accuracy of 96.35% and 96.74%, respectively, outperforming previous best result with significant gap.

========

#Citation 

If you use this code, please cite our paper: 
Bibtex format: 
@inproceedings{HCCR-GoogLeNet, 
		title = {High Performance Offline Handwritten Chinese Character Recognition Using GoogLeNet and Feature Maps}, 
		author = {Zhuoyao Zhong, Lianwen Jin, Zecheng Xie}, 
		booktitle = {International Conference on Document Analysis and Recognition ({ICDAR})}}, 
		year = {2015} 
}
