# Image Model Tester

A browser-based tool for trying out image models trained with [Teachable Machine](https://teachablemachine.withgoogle.com/). Upload your model, point your webcam at an item (or pick a picture), and it tells you which class the item belongs to.

No backend is needed: the classification runs in the browser using TensorFlow.js.

## How it works

1. You train an image classification model in Teachable Machine (one class per category) and export it as a TensorFlow.js model.
2. You open `webcam.html` and upload the three exported model files.
3. The page starts your webcam and shows live predictions for each class.
4. Click **Evaluate**. For 5 seconds the page averages the model's predictions, then shows a popup with the winning class and its average match percentage.

Averaging over a few seconds makes the final answer more stable than a single frame.

It works with **any Teachable Machine image model**, with any number of classes. The included example model (`Model/`) has two classes: **Recyclable Waste** and **Non-Recyclable Waste**.

## Repository structure

```
smart-waste-segregator/
├── Model/          # Exported Teachable Machine model files (example)
├── upload.html     # Classify from an uploaded picture
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

Then open `http://localhost:8000/webcam.html`.

### Use it

1. Click **Choose Files** and select all three model files at once (they are in the `Model/` folder):
   - `model.json`
   - `metadata.json`
   - `weights.bin`

   Keep the original file names. `model.json` references `weights.bin` by name, and the page will show an error if the names don't match.
2. Once all three show a green check, click **Start** and allow camera access.
3. Hold an item in front of the camera and watch the live class probabilities.
4. Click **Evaluate** and keep the item steady for 5 seconds.
5. Read the result in the popup. Click **Evaluate again** to test another item, or **Stop** to release the camera.

### Classify a single picture

`upload.html` works like the webcam page. Choose the same three model files, then pick a picture and it shows the prediction for each class. The libraries still load from the internet, but the model comes from your own files.

## Training your own model

1. Go to [Teachable Machine](https://teachablemachine.withgoogle.com/) and create a new **Image Project** (Standard image model).
2. Create one class per category and add plenty of varied sample images of each.
3. Train the model, then choose **Export Model** → **TensorFlow.js** → **Download**.
4. Unzip the download. You will get `model.json`, `metadata.json` and `weights.bin`, which you upload in the page.

## Configuration

These values are at the top of the script in `webcam.html`:

| Setting | Default | Description |
| --- | --- | --- |
| `UPDATE_INTERVAL_MS` | `500` | How often the model runs on the webcam frame (ms) |
| `EVAL_DURATION_MS` | `5000` | How long the Evaluate step collects predictions (ms) |

## Tips for better accuracy

- Train with images taken in the same lighting and background you'll use at runtime.
- Include several angles and examples per class, and add a "nothing / background" class.
- Keep the item centred and fill most of the frame.

## Built with

- [TensorFlow.js](https://www.tensorflow.org/js) 1.3.1
- [@teachablemachine/image](https://github.com/googlecreativelab/teachablemachine-community) 0.8
- Plain HTML, CSS and JavaScript

## Contributing

Issues and pull requests are welcome. For larger changes, please open an issue first to discuss what you'd like to change.

## License

Distributed under the Apache License 2.0. See [`LICENSE`](LICENSE) for details.
