from PIL import Image
from PIL import ImageDraw
from PIL import ImageFont
import csv

def print_team_sign(number, team_name):
    img = Image.new('RGB', (1280, 600), (255, 255, 255))

    size = width, height = img.size
    draw = ImageDraw.Draw(img,'RGBA')

    # font sizes
    font_big = ImageFont.truetype("/usr/share/fonts/TTF/FreeMono.ttf", 85)
    font_small = ImageFont.truetype("/usr/share/fonts/TTF/FreeMono.ttf", 25)
    font_bold = ImageFont.truetype("/usr/share/fonts/TTF/FreeMonoBold.ttf", 60)

    # text describing team number
    team_number = "Team " + str(number)
    team_width, team_height = draw.textsize(team_number, font=font_big)
    team1_top_left = (20, 20)
    team2_top_left = (width - team_width - 43, height - team_height - 131)

    draw.text(team1_top_left, team_number, (0, 0, 0, 0), font=font_big)
    draw.text(team2_top_left, team_number, (0, 0, 0, 0), font=font_big)

    # text describing contest
    contest = "2017 South America/South Finals"
    contest_width, contest_height = draw.textsize(contest, font=font_small)
    draw.text(((width - contest_width) / 2, team2_top_left[1] + team_height + 50), contest, (0, 0, 0, 0), font=font_small)

    # decorative lines
    line_width = 7
    draw = ImageDraw.Draw(img)

    a_right = (team1_top_left[0] + team_width + 20, 60)
    a_left  = (team1_top_left[0] + team_height, 110)
    b       = (img.width - 90, a_right[1])
    c       = (a_left[0], img.height - 150)
    d_left  = (team2_top_left[0] - 20, c[1])
    d_right = (b[0], team2_top_left[1] - 10)

    draw.line(a_right + (b[0] + 3, b[1]),  fill=256, width=line_width) # A - B
    draw.line(b       + d_right,           fill=256, width=line_width) # B - D
    draw.line(a_left  + (c[0], c[1] + 3),  fill=256, width=line_width) # A - C
    draw.line(c       + d_left,            fill=256, width=line_width) # C - D

    # team name
    text_width, text_height = draw.textsize(team_name, font=font_bold)
    draw.text(((width - text_width) / 2, (d_right[1] - text_height) / 2 + a_right[1]), team_name, fill="black", font=font_bold)

    img.save('team' + str(number) + '.jpg')

def main():
    with open('teams.txt') as f:
        teams = f.readlines()
    teams = [x.strip() for x in teams] 
    team_number = 1
    for t in teams:
        print(t)
        print_team_sign(team_number, t)
        team_number = team_number + 1
    
main()

# after creating jpgs, run the following command to create printable PDF
# montage *.jpg -tile 1x3 -geometry 1000 assembly.pdf
