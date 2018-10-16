import subprocess
from PIL import Image, ImageDraw, ImageFont

teams = []

with open("teams") as f:
    for l in f:
        if l.rfind(";") != -1:
            l = l.strip()
            teams.append((l[:l.rfind(";")], l[l.rfind(";") + 1:]))

font_path = "./OpenSans-Regular.ttf"
icpc = Image.open("icpc.jpeg").convert('RGBA')
bottom_h = icpc.size[1]
font = ImageFont.truetype("OpenSans-Regular.ttf", int(bottom_h * 0.3))

# If the largest team name doesn't fit the photo, reduce 0.18 to 0.15 or less until it fits.
font_small = ImageFont.truetype("OpenSans-Regular.ttf", int(bottom_h * 0.18))

for name, photo_path in teams:
    base = Image.open("input_photos/" + photo_path).convert('RGBA')

    dest = "output_photos/" + name + ".png"
    txt = Image.new('RGBA', (base.size[0], base.size[1] + int(icpc.size[1])), (255,255,255,0))
    txt.paste(base, (0, 0))
    d = ImageDraw.Draw(txt)

    d.rectangle(((0, txt.size[1] - bottom_h), (txt.size[0], txt.size[1])), fill="#0f2027")
    if len(name) <= 17:
        d.text((txt.size[0] * 0.3, txt.size[1] - bottom_h * 0.75), name, font=font, fill=(255,255,255,255))
    else:
        d.text((txt.size[0] * 0.3, txt.size[1] - bottom_h * 0.75), name, font=font_small, fill=(255,255,255,255))

    txt.paste(icpc, (0, txt.size[1] - icpc.size[1]))

    txt.save(dest)

    subprocess.call(["convert", dest, "-sampling-factor", "100:80:0", "-strip", "-quality", "8", "-interlace", "JPEG", "-colorspace", "RGB", dest[:-3] + "jpg"])

    print("Saved", dest)
