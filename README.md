# Smart Waste Segregator

A browser-based waste classification tool. It uses an image model trained with [Teachable Machine](https://teachablemachine.withgoogle.com/) to look at an item through your webcam and tell you which category of waste it belongs to. No install and no backend: everything runs in the browser using TensorFlow.js.

## How it works

1. You train an image classification model in Teachable Machine (one class per waste category) and export it as a TensorFlow.js model.
2. You open `webcam.html` and upload the three exported model files.
3. The page starts your webcam and shows live predictions for each class.
4. Click **Evaluate**. For 5 seconds the page averages the model's predictions, then shows a popup with the winning class and its average match percentage.

Averaging over a few seconds makes the final answer more stable than a single frame.

## Repository structure

```
smart-waste-segregator/
├── Model/          # Exported Teachable Machine model files
├── arduino ver/    # Arduino version of the project
├── upload.html     # Page for classifying from uploaded images
├── webcam.html     # Live webcam classification page
└── LICENSE         # Apache-2.0
```

## Getting started

### Requirements

- A modern browser (Chrome, Edge, Firefox, Safari)
- A webcam
- Internet access on first load (TensorFlow.js and the Teachable Machine library are loaded from the jsDelivr CDN)

### Run it

Browsers only allow camera access on `localhost` or HTTPS, so serve the folder locally instead of opening the file directly:

```bash
git clone https://github.com/mukundzoom2-dev/smart-waste-segregator.git
cd smart-waste-segregator
python3 -m http.server 8000
```

Then open `
<img width="1600" height="1082" alt="arduino_uno_wiring" src="https://github.com/user-attachments/assets/5858ed8c-35c7-4558-b369-f0776fe05bf3" />
http://localhost:8000/webcam.html`.

### Use it

1. Click **Choose Files** and select all three model files at once:
   - `model.json`
   - `metadata.json`
   - `weights.bin`

   Keep the original file names. `model.json` references `weights.bin` by name, and the page will show an error if the names don't match.
2. Once all three show a green check, click **Start** and allow camera access.
3. Hold an item in front of the camera and watch the live class probabilities.
4. Click **Evaluate** and keep the item steady for 5 seconds.
5. Read the result in the popup. Click **Evaluate again** to test another item, or **Stop** to release the camera.

## Training your own model

1. Go to [Teachable Machine](https://teachablemachine.withgoogle.com/) and create a new **Image Project** (Standard image model).
2. Create one class per waste category (for example: Plastic, Paper, Metal, Organic) and add plenty of varied sample images of each.
3. Train the model, then choose **Export Model** → **TensorFlow.js** → **Download**.
4. Unzip the download. You will get `model.json`, `metadata.json` and `weights.bin`, which you upload in the page.

## Configuration

These values are at the top of the script in `webcam.html`:

| Setting | Default | Description |
| --- | --- | --- |
| `UPDATE_INTERVAL_MS` | `500` | How often the model runs on the webcam frame (ms) |
| `EVAL_DURATION_MS` | `5000` | How long the Evaluate step collects predictions (ms) |

## Built with

- [TensorFlow.js](https://www.tensorflow.org/js) 1.3.1
- [@teachablemachine/image](https://github.com/googlecreativelab/teachablemachine-community) 0.8
- Plain HTML, CSS and JavaScript

## Hardware (Arduino version)

<!-- TODO: The arduino ver/ folder wasn't visible when this README was drafted. Fill this in: -->

- **Board:** Arduino UNO
- **Components:** servo motors, breadboard, bins
- **Wiring:** [add a diagram or pin table]
- **How it connects to the classifier:** [e.g. serial messages from the browser, standalone sketch]

## Tips for better accuracy

- Train with images taken in the same lighting and background you'll use at runtime.
- Include several angles and examples per class, and add a "nothing / background" class.
- Keep the item centred and fill most of the frame.

## Contributing

Issues and pull requests are welcome. For larger changes, please open an issue first to discuss what you'd like to change.

## License

Distributed under the Apache License 2.0. See [`LICENSE`](LICENSE) for details.
