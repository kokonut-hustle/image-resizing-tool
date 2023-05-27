## Image Resizing Tool
### Dependencies
<a href="https://github.com/nothings/stb">stb_image</a> for loading and writing images.

### Datasets
https://www.kaggle.com/datasets/shreyapmaher/fruits-dataset-images

### Performance Test

| Version                     | Original BI | SIMD BI |
| :--                         | :--:        | :--:    |
| 2x width, 2x height         | 85.82s      | 78.07s  |
| 2x width, 3x height         | 126.61s     | 114.65s |
| (1/2)x width, (1/2)x height | 11.12s      | 10.60s  |
| (1/3)x width, (1/2)x height | 9.50s       | 9.12s   |

### To Do
- Implement other algorithms
- GUI
