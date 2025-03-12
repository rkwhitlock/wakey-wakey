import cv2
import mediapipe as mp
import numpy as np
import matplotlib.pyplot as plt

# Load the image
image = cv2.imread("image.jpg")
image_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

# Initialize MediaPipe Pose model
mp_pose = mp.solutions.pose
mp_drawing = mp.solutions.drawing_utils
pose = mp_pose.Pose(static_image_mode=True, min_detection_confidence=0.5)

results = pose.process(image_rgb)

if results.pose_landmarks:
    mp_drawing.draw_landmarks(image, results.pose_landmarks, mp_pose.POSE_CONNECTIONS)

    landmarks = results.pose_landmarks.landmark

    LEFT_WRIST = mp_pose.PoseLandmark.LEFT_WRIST
    RIGHT_WRIST = mp_pose.PoseLandmark.RIGHT_WRIST
    LEFT_SHOULDER = mp_pose.PoseLandmark.LEFT_SHOULDER
    RIGHT_SHOULDER = mp_pose.PoseLandmark.RIGHT_SHOULDER

    left_wrist_y = landmarks[LEFT_WRIST].y
    right_wrist_y = landmarks[RIGHT_WRIST].y
    left_shoulder_y = landmarks[LEFT_SHOULDER].y
    right_shoulder_y = landmarks[RIGHT_SHOULDER].y

    if left_wrist_y < left_shoulder_y and right_wrist_y < right_shoulder_y:
        print(1)

print(0)
