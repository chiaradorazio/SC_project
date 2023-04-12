## Multivariate Analysis on MonteCarlo data sample

In physics **data analysis**, we have usually two main categories of events (i.e. two different datasets): **signal** *events* that concern the physics we want to examine and **background** *events* that have similar properties to the ones we are looking for.
**Event selection** is a technique that loops on all events and decides whether to accept or to reject each of them, according to specific criteria. At the end of the selection, we will have a sample of **candidates**, ideally made up of signal events.

This repository explores **multivariate analysis** for *events selection*, based on simulated data obtained by the a Monte Carlo program in order to discriminate statistically events caused by primary gammas (signal) from the images of hadronic showers initiated by cosmic rays in the upper atmosphere (background).

The goal of events selection is to test strategies for filtering events on separated signal and background datasets and then apply the best one on the unique dataset obtained by experiment.

## MVA
A way to improve the capability of event selection is to apply a linear or, even better, a non linear correlation between the discriminating variables (**multivariate analysis**). Some of these methods were successfully developed in the last decades thanks to improvement of computing performances and the most used in HEP analysis are the *Neural Network* and the *Boost Decision Trees* methods. As before, events are filtered according to a combination of variable values. The difference is that the cuts are no more chosen manually but by algorithms specific of the chosen method.

### Physical characteristics
Relevant Information:

The data are MC generated to simulate registration of high energy gamma particles in a ground-based atmospheric Cherenkov gamma telescope using the imaging technique. The Cherenkov gamma telescope observes high energy gamma rays by utilizing of the radiation emitted by charged particles produced inside the electromagnetic showers initiated by the gammas, and developing in the atmosphere. This Cherenkov radiation (of visible to UV wavelengths) leak into the atmosphere and is recorded in the detector, allowing reconstruction of the shower parameters. The available information consists of pulses left by the incoming Cherenkov photons on the photo-multiplier tubes, arranged in a plane, the camera. Depending on the energy of the primary gamma, a total of few hundreds to some 10000 Cherenkov photons are collected in patterns, allowing to discriminate statistically those caused by primary gammas (signal) from the images of hadronic showers initiated by cosmic rays in the upper atmosphere (background).

Number of Events: 19020

Number of Attributes: 11 (including the class)

Attribute information:
1. **fLength**: major axis of ellipse [mm]  
2. **fWidth**: minor axis of ellipse [mm]  
3. **fSize**:  10-log of sum of content of all pixels [in #phot]  
4. **fConc**: ratio of sum of two highest pixels over fSize [ratio]  
5. **fConc1**:  ratio of highest pixel over fSize [ratio]  
6. **fAsym**:  distance from highest pixel to center, projected onto major axis [mm]  
7. **fM3Long**:  3rd root of third moment along major axis [mm]  
8. **fM3Trans**: 3rd root of third moment along minor axis [mm]  
9. **fAlpha**: angle of major axis with vector to origin [deg]  
10. **fDist**: distance from origin to center of ellipse [mm]  
11. **class**: g,h (gamma (signal), hadron (background))  

g = gamma (signal): 12332  
h = hadron (background): 6688


### Repository
The repository contains:
- tmva_train_SC.C  
It is a C++ function based on TMVA, a toolkit of ROOT which provides a ROOT-integrated machine learning environment. Once the datasets are opened, it trains and tests the methods and stamps the ROC curve in order to study the efficiency. 

A more detailed description is inside the file.

### Installation
To get this git repository please type on your bash:
```
git clone https://github.com/chiaradorazio/SC_project.git
```

### Version
The program was tested with the version of ROOT Version: 6.26/06, the version of g++ (GCC) 11.3.0.  
[TMVA](https://root.cern/manual/tmva/) environment is required.
Please check if you have TMVA, type on your bash:
```
root-config --has-tmva
```


## Usage

When installed, the program can be run from command line.
Write in you shell:

```
root
.L tmva_train_SC.C
```

The program will automatically read 'signal.txt' and 'background.txt'.

```
tmva_train()
```

## Results
In the program the following method were tested:  

1.Boosted Decision Trees (Adaptive Boost)  

2.Multi-Layer Perceptron (Neural Network)  

3.Linear Discriminant Analysis (Fisher discriminant)  

4.Cut optimisation (binary splits)  

As output result are produced *TTMVAOutputCV.root* file and **dataset** folder.

Inside **dataset** / weights folder the user can find the coefficients of the method tested and the weights.

For comparison of different classifiers look at the **ROC curve**.



