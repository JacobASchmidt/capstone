import deeplake

import tensorflow as tf
import numpy as np
from sklearn.model_selection import train_test_split

from tensorflow.keras.utils import to_categorical
from skimage.transform import resize

ds = deeplake.load("hub://activeloop/gtsrb-train")

dataloader = ds.tensorflow()

num_classes = 43
images = np.array([resize(el["images"].numpy(), (32, 32)) for el in dataloader])
labels = np.array([el["labels"] for el in dataloader])
labels = to_categorical(labels, num_classes = num_classes)

print(images.shape)
print(labels.shape)
   
train_images, test_images, train_labels, test_labels = train_test_split(images, labels, test_size=0.2)

model = tf.keras.Sequential([
    tf.keras.layers.Conv2D(32, (3, 3), activation='relu', input_shape=train_images.shape[1:]),
    tf.keras.layers.MaxPooling2D((2, 2)),
    tf.keras.layers.Conv2D(64, (3, 3), activation='relu'),
    tf.keras.layers.MaxPooling2D((2, 2)),
    tf.keras.layers.Conv2D(64, (3, 3), activation='relu'),
    tf.keras.layers.Flatten(),
    tf.keras.layers.Dense(64, activation='relu'),
    tf.keras.layers.Dense(num_classes)
])

model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

model.fit(train_images, train_labels, epochs=10, batch_size=32, validation_data=(test_images, test_labels))
