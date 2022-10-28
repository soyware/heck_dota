const char g_MenuXML[] = R"del(
<root>
	<styles>
		<include src="s2r://panorama/styles/dotastyles.vcss_c" />
		<include src="s2r://panorama/styles/popups/popups_shared.vcss_c" />
		<include src="s2r://panorama/styles/battle_pass/current_battle_pass.vcss_c" />
		<include src="s2r://panorama/styles/popups/popup_settings.vcss_c" />
	</styles>
	
	<script>
		function changeActiveTab(nTab) {
			var panels = [ "MovesTabContent", "VisualsTabContent", "MiscTabContent" ];
			for (var i = 0; i < panels.length; ++i) {
				var panel = $("#" + panels[i]);
				if (i != nTab)
					panel.AddClass("HideSection");
				else
					panel.RemoveClass("HideSection");
			}
		}

		function particleMaphackToggled() {
			var section = $("#ParticleMaphackSection");
			var childCount = section.GetChildCount();
			var status = section.GetChild(2).checked;
			
			section.GetChild(3).enabled = status;
		}
	</script>

	<Popup class="PopupPanel Hidden" 
		style="width: 500px;
			height: 650px;
			box-shadow: #00000099 0px 0px 8px 0px;
			border: 2px solid #32383677;
			flow-children: none;
			padding: 0;"
		popupbackground="blur" oncancel="UIPopupButtonClicked()">
		
		<Panel id="SettingsNavBar">
			<Button id="DOTACloseSettingsButton" class="ControlIconButton" onactivate="UIPopupButtonClicked()" />
			<RadioButton id="MovesTabButton" class="SettingsNavBarButton" group="SettingsTopMenu" onactivate="changeActiveTab(0)">
				<Label text="MOVES" />
			</RadioButton>
			<Label class="SettingsTabSeparator" text="/" />
			<RadioButton id="VisualsTabButton" class="SettingsNavBarButton" group="SettingsTopMenu" onactivate="changeActiveTab(1)">
				<Label text="VISUALS" />
			</RadioButton>
			<Label class="SettingsTabSeparator" text="/" />
			<RadioButton id="MiscTabButton" class="SettingsNavBarButton" group="SettingsTopMenu" onactivate="changeActiveTab(2)">
				<Label text="MISC" />
			</RadioButton>
		</Panel>
		
		<Panel id="MovesTabContent" class="SettingsSecondaryPanel">
			<Panel class="SettingsColumnContainer FullHeight">
				<Panel class="SettingsColumn" style="width: 100%;">
					<Panel class="SettingsSection">
						<DOTASettingsEnum convar="heck_autorune" text="Auto-rune">
							<RadioButton text="Off" value="0" class="EnumButton" group="group_autorune" />
							<RadioButton text="Bounty" value="1" class="EnumButton" group="group_autorune" />
							<RadioButton text="Any" value="2" class="EnumButton" group="group_autorune" />
						</DOTASettingsEnum>

						<DOTASettingsCheckbox convar="heck_autostun" text="Auto-stun" />
					</Panel>
				</Panel>
			</Panel>
		</Panel>

		<Panel id="VisualsTabContent" class="SettingsSecondaryPanel HideSection">
			<Panel class="SettingsColumnContainer FullHeight">
				<Panel class="SettingsColumn" style="width: 100%;">
					<Panel class="SettingsSection">
						<DOTASettingsCheckbox convar="heck_show_illusions" text="Show illusions" />
						<DOTASettingsCheckbox convar="heck_show_charge" text="Show Spirit Breaker's charge" />
						<DOTASettingsCheckbox convar="heck_show_spell_dmg" text="Show nuker spell damage" />
						<DOTASettingsCheckbox convar="heck_show_gem" text="Show gem" />
						<DOTASettingsCheckbox convar="heck_show_visibility" text="Show visibility" />
						<DOTASettingsCheckbox convar="heck_predict_courier" text="Predict courier location" />
						<DOTASettingsCheckbox convar="heck_no_fow" text="No Fog of War" />
					</Panel>
				</Panel>
			</Panel>
		</Panel>
		
		<Panel id="MiscTabContent" class="SettingsSecondaryPanel HideSection">
			<Panel class="SettingsColumnContainer FullHeight">
				<Panel class="SettingsColumn" style="width: 100%;">
					<Panel class="SettingsSection">
						<Panel id="ParticleMaphackSection" class="SettingsSection">
							<Label text="Particle maphack" class="SectionHeader" />
							<Panel class="SectionHeaderLineNoMargin" />
							<DOTASettingsCheckbox convar="heck_particle_maphack_enable" text="Enable" onactivate="particleMaphackToggled()" onload="particleMaphackToggled()" />
							<DOTASettingsSlider convar="heck_particle_maphack_size" min="500" max="1500" text="Icon size" />
						</Panel>

						<Panel class="TopBottomFlow" style="margin-bottom: 16px; width: 100%;">
							<Label text="Weather:" />
							<DOTASettingsEnumDropDown id="WeatherDropDown" convar="heck_weather" style="width: 100%;">
								<Label id="default" value="0" text="Default" />
								<Label id="snow" value="1" text="Snow" />
								<Label id="rain" value="2" text="Rain" />
								<Label id="spring" value="3" text="Spring" />
								<Label id="pestilence" value="4" text="Pestilence" />
								<Label id="harvest" value="5" text="Harvest" />
								<Label id="sirocco" value="6" text="Sirocco" />
								<Label id="moonbeam" value="7" text="Moonbeam" />
								<Label id="ash" value="8" text="Ash" />
								<Label id="aurora" value="9" text="Aurora" />
							</DOTASettingsEnumDropDown>
						</Panel>
						
						<DOTASettingsSlider convar="heck_camera_distance" min="1200" max="5000" text="Camera distance" />
						<DOTASettingsSlider convar="heck_range_display" min="0" max="2000" text="Range display" />
						
						<DOTASettingsCheckbox convar="heck_crash_friendslist" text="Crash friends-list" />
						<Panel class="LeftRightFlow" style="margin-bottom: 16px; width: 100%;">
							<TextEntry id="RPTextEntry" placeholder="OR set custom status" maxchars="256" oninputsubmit="DOTASearchTextSubmitted()" style="horizontal-align: left;" />
							<Button class="ButtonBevel" style="
								background-image: url('s2r://panorama/images/control_icons/check_gradient_png.vtex');
								background-repeat: no-repeat;
								background-size: 70%;
								background-position: center;
								min-width: 36px;
								min-height: 36px;
								horizontal-align: right;" onactivate="DOTASearchTextSubmitted()" />
						</Panel>
						
						<!-- <DOTASettingsCheckbox convar="heck_autominigame" text="Auto-minigame (pause)" /> -->

						<Panel class="LeftRightFlow" style="width: 100%; margin-top: 32px;">
							<Button class="ButtonBevel" onactivate="DOTAApplyResolutionChoice()" style="horizontal-align: left;">
								<Label text="Save settings" />
							</Button>
							<Button class="ButtonBevel" onactivate="DOTADisconnectClicked()" style="horizontal-align: right;">
								<Label text="Uninject" />
							</Button>
						</Panel>
					</Panel>
				</Panel>
			</Panel>
		</Panel>
	</Popup>
</root>
)del";